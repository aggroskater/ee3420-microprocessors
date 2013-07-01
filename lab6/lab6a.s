; vim: set filetype=asmhc12:

#INCLUDE ../HC12TOOLS.INC

	ORG $1000

STEP_INCREMENT	DC.B 0
STEP_OFFSET	DC.B 0

ROTATION	DS.B 1
STEPTYPE	DS.B 1
DELAY		DS.W 1
DELAY_BUFFER	DS.B 20
COUNTER		DS.W 1

FSS_SEQ	DC.B $00,$01,$02,$03

FSD_SEQ	DC.B $0C,$06,$03,$09

HS_SEQ	DC.B $08,$0C,$04,$06,$02,$03,$01,$09

PROMPT_START	DC.B "Do you wish to update state or quit?",CR,LF
		DC.B "1.) Update state",CR,LF
		DC.B "2.) Quit.",CR,LF
		DC.B CR,LF
		DC.B ">"
		DC.B NULL

PROMPT_ROTATION	DC.B "Please indicate which direction you would like",CR,LF
		DC.B "the motor to turn:",CR,LF
		DC.B "1.) Clockwise",CR,LF
		DC.B "2.) Counter-Clockwise",CR,LF
		DC.B CR,LF
		DC.B ">"
		DC.B NULL

PROMPT_STEPTYPE	DC.B "Please indicate the desired step type:",CR,LF
		DC.B "1.) Full steps single coils",CR,LF
		DC.B "2.) Full steps dual coils",CR,LF
		DC.B "3.) Half steps",CR,LF
		DC.B CR,LF
		DC.B ">"
		DC.B NULL

PROMPT_DELAY	DC.B "Please input the desired delay factor, N,",CR,LF
		DC.B "resulting in N*0.0001 second delay between steps",CR,LF
		DC.B "Must be at least 10 and less than 255.",CR,LF
		DC.B CR,LF
		DC.B ">"
		DC.B NULL
	
NEWLINE		DC.B CR,LF,NULL
	
	ORG $2000

MAIN:

	JSR INITIALIZE
	JSR E_RTI		; initially, we have CW, FSS, 1ms delay
	JSR STEPPER_SETUP	; this is the main loop
	
;----------------------------------------------------------
;-----------------   HELPER ROUTINES   --------------------
;----------------------------------------------------------

INITIALIZE:

	;Turn on LEDs so we can see which coils are firing at any given 
	;moment.
	BSET DDRJ,#%00000010	; set jumper1 to output mode
	BCLR PORTJ,#%00000010	; set jumper1 to output a low signal
	MOVB #%00001111,DDRB	; will output on LEDs 3 through 0.

	;enable PORTP, which is where the motor driver chip gets its input.
	MOVB #%00001111,DDRP	; Set PORTP as output (sends output to driver
				; chip)	
	MOVB #%00001111,PORTP	; Enable PORTP0-PORTP3, which the stepper 
				; motor is wired to.

	;set RTI prescaler and vector
        MOVB #%00010000,RTICTL  ; sets prescaler to 2^10
                                ; results in interrupt every 0.000128 seconds.
                                ; (OSCCLK, which RTI is based off of, is 8MHz)
                                ; ergo, 1/(8MHz/(1*2^10)) = 0.000128 seconds. 
        LDD #ISR_STEPPER_STEP   ; put address of ISR_STEPPER_STEP in D.
        STD UserRTI             ; put that address into RTI vector.	

	;define initial behaviour of motor
	MOVB #1,ROTATION 	; Clockwise rotation
	MOVB #1,STEPTYPE	; Full step single
	MOVW #10,DELAY		; Only move once every millisecond

	RTS

E_RTI:

	MOVB #%10000000,CRGINT	; enables RTI
	CLI			; permits global interrupts
	RTS
	
D_RTI:

	MOVB #%00000000,CRGINT	; disables RTI
	SEI			; disables global interrupts
	RTS

ISR_STEPPER_STEP:

	;crunch delay logic first. do we do anything?

	LDD COUNTER
	DBNE D,ISR_END
	
	;alright. time to move. what direction are we rotating?
	LDAB ROTATION
	CMPB #'1'
	BEQ ISR_ROT_CW
	CMPB #'2'
	BEQ ISR_ROT_CCW

	;time to find out what type of stepping we'll be doing.
ISR_GET_STEP_TYPE:

	LDAB STEPTYPE
	CMPB #'1'
	BEQ ISR_STEP_FSS
	CMPB #'2'
	BEQ ISR_STEP_FSD
	CMPB #'3'
	BEQ ISR_STEP_HS	

ISR_ROT_CW:

	;remember, STEP_INCREMENT is a constant so only MOVB will update it. 
	MOVB #-1,STEP_INCREMENT	
	BRA ISR_GET_STEP_TYPE

ISR_ROT_CCW:

	;remember, STEP_INCREMENT is a constant so only MOVB will update it.
	MOVB #1,STEP_INCREMENT
	BRA ISR_GET_STEP_TYPE

ISR_STEP_FSS:

	;perform the actual step based off increment
	LDAB STEP_OFFSET
	ADDB STEP_INCREMENT
	ANDB #%00000011		; this lets us go from 0 3 and roll back over.
	STAB STEP_OFFSET	; this will increment from 1 to 3 before
				; rolling back over to zero and repeating.
	TFR B,X		
	LDAA FSS_SEQ,X		; grab the appropriate active pins based on
				; offset and appropriate array (FSS_SEQ in 
				; this case)
	STAA PORTB		; send the byte over PORTB, which is 
				; connected to the H-bridge driver's input 
				; and will spin the motor to the new position.

	;reset delay counter while we're at it
	LDD DELAY
	BRA ISR_END

ISR_STEP_FSD:

        ;perform the actual step based off increment
        LDAB STEP_OFFSET
        ADDB STEP_INCREMENT
        ANDB #%00000011         ; this lets us go from 0 3 and roll back over.
        STAB STEP_OFFSET        ; this will increment from 1 to 3 before
                                ; rolling back over to zero and repeating.
        TFR B,X
        LDAA FSD_SEQ,X          ; grab the appropriate active pins based on
                                ; offset and appropriate array (FSD_SEQ in  
                                ; this case) 
        STAA PORTB              ; send the byte over PORTB, which is 
                                ; connected to the H-bridge driver's input 
                                ; and will spin the motor to the new position.

	;reset delay counter while we're at it
	LDD DELAY
	BRA ISR_END

ISR_STEP_HS:

        ;perform the actual step based off increment
        LDAB STEP_OFFSET
        ADDB STEP_INCREMENT
        ANDB #%00000111         ; this lets us go from 0 7 and roll back over.
        STAB STEP_OFFSET        ; this will increment from 1 to 7 before
                                ; rolling back over to zero and repeating.
        TFR B,X
        LDAA HS_SEQ,X           ; grab the appropriate active pins based on
                                ; offset and appropriate array (HS_SEQ in  
                                ; this case) 
        STAA PORTB              ; send the byte over PORTB, which is 
                                ; connected to the H-bridge driver's input 
                                ; and will spin the motor to the new position.

	;reset delay counter while we're at it
	LDD DELAY
	BRA ISR_END

ISR_END:

	STD COUNTER
	RTI

STEPPER_SETUP:
	
	PUTS_SCI0 #PROMPT_START	; start main program loop
	GETC_SCI0		; grab input from user. gets placed in B.
	CMPB #'1'		; are we continuing?
	BEQ SET_ROT
	CMPB #'2'		; are we quiting?
	LBEQ QUIT
	PUTS_SCI0 #NEWLINE
	BRA STEPPER_SETUP	; bad input. try again.

SET_ROT:

	JSR D_RTI		; disable RTI until state is well-defined.
	PUTS_SCI0 #PROMPT_ROTATION
	GETC_SCI0
	CMPB #'1'		; rotating clockwise?
	BEQ CW
	CMPB #'2'		; rotating counter clockwise?
	LBEQ CCW
	PUTS_SCI0 #NEWLINE
	BRA SET_ROT		; bad input. try again.

SET_STEP:

	PUTS_SCI0 #PROMPT_STEPTYPE
	GETC_SCI0
	CMPB #'1'		; Full step single coil?
	BEQ FSS
	CMPB #'2'		; Full step dual coil?
	BEQ FSD
	CMPB #'3'		; Half step?
	BEQ HS
	PUTS_SCI0 #NEWLINE
	BRA SET_STEP		; bad input

SET_DELAY:

	PUTS_SCI0 #PROMPT_DELAY
	GETS_SCI0 #DELAY_BUFFER
	ATOI #DELAY_BUFFER,DELAY
	LDD DELAY
	CPD #10
	BLO DELAY_RETRY		; input out of range. grab again.
	CPD #255
	BHI DELAY_RETRY		; input out of range. grab again.


	JSR E_RTI		; enable RTI since state is well-defined.	
	LBRA STEPPER_SETUP	; repeat forevah!


QUIT:

	CLR PORTB
	CLR PORTP
	JSR D_RTI
	
	RTS			; quit program

CW:

	MOVB #1,ROTATION
	BRA SET_STEP

CCW:

	MOVB #2,ROTATION
	BRA SET_STEP

FSS:

	MOVB #1,STEPTYPE
	BRA SET_DELAY

FSD:

	MOVB #2,STEPTYPE
	BRA SET_DELAY

HS:

	MOVB #3,STEPTYPE
	BRA SET_DELAY

DELAY_RETRY:

	PUTS_SCI0 #NEWLINE 
	BRA SET_DELAY
