; vim: set filetype=asmhc12:

#INCLUDE ../HC12TOOLS.INC

	ORG $1000

MINIMUM		DS.W 1
MAXIMUM		DS.W 1
INCREMENT	DS.W 1
STR_BUFFER	DS.B 40
INT_BUFFER	DS.W 1

PROMPT_SETUP	DC.B "Please indicate which action you desire:",CR,LF
		DC.B "1.) Change minimum duty cycle",CR,LF
		DC.B "2.) Change maximum duty cycle",CR,LF
		DC.B "3.) Change step increment",CR,LF
		DC.B "4.) Select rotation",CR,LF
		DC.B "5.) Quit",CR,LF
		DC.B CR,LF
		DC.B ">"
		DC.B NULL

PROMPT_MIN	DC.B "Input minimum duty cycle, no less than 36, no",CR,LF
		DC.B "greater than 84.",CR,LF
		DC.B CR,LF
		DC.B ">"
		DC.B NULL

PROMPT_MAX	DC.B "Input maximum duty cycle, no greater than 84, no",CR,LF   
                DC.B "less than 36.",CR,LF
                DC.B CR,LF
                DC.B ">"
                DC.B NULL

PROMPT_STEP	DC.B "Input step, between 1 and 4.",CR,LF
		DC.B CR,LF
		DC.B ">"
		DC.B NULL

PROMPT_ROT	DC.B "Please indicate which action you desire:",CR,LF
                DC.B "1.) Full rotation CW",CR,LF
                DC.B "2.) Full rotation CCW",CR,LF
		DC.B "3.) Step rotation CW",CR,LF
		DC.B "4.) Step rotation CCW",CR,LF
		DC.B "5.) Back to main menu.",CR,LF
                DC.B CR,LF
                DC.B ">"
                DC.B NULL

NEWLINE		DC.B CR,LF,NULL
DENOM		DC.B "/800",NULL
BLANK_LCD_LINE  DC.B "                ",NULL

	ORG $2000

MAIN:

	;set up PWM for 20ms period

	; 50 Hz -> (1/50)/(1/(24000000/(150*2^2))) cycles = 800 cycles
	; so PWMPER=800
	; min duty of 3% -> PWMDTY>=24
	; max duty of 12% -> PWMDTY<=96
	; max increment of 0.5% at a time -> increment no larger than 4

	; UPDATE:

	; Ran into trouble with max duty at 96 and min 24 , sounded like servo
	; was overdriving. According to:

	; http://tlfong01.blogspot.com/2013/03/tower-pro-sg90-micro-servo-refreshing.html

	; the duty range is typically from 900 us to 2100us, so the following 
	; max and min should work better:

	; MIN = 36

	; MAX = 84

	BSET PWME,BIT4	;ENABLE PWM CHANNEL 4 ; PP4 outputs waveform
;	BCLR PWME,BIT4
	BSET PWMPOL,BIT4 ;CHANNEL 4 ACTIVE HIGH
	;BCLR PWMCLK,BIT4 ;CHANNEL 4 CLOCK A (0 = A or B ; 1 = SA or SB)
	BSET PWMCLK,BIT4 ;CHANNEL 4 CLOCK SA	
	MOVB #$02,PWMPRCLK ;PWM CLOCK A SCALE=4
	MOVB #75,PWMSCLA ; SA = A/(2*75) = A / 150
	MOVB #800,PWMPER4 ;PWM CHANNEL 4 PERIOD = 20ms
	MOVB #36,PWMDTY4 ;PWM CHANNEL 4 DUTY CYCLE = 3%

	;set up LCD
	LCD_SETUP
	LCD_CURSOR 0,0

	;set initial values
	LDD #36
	STD MINIMUM
	LDD #84
	STD MAXIMUM
	LDD #4
	STD INCREMENT
	LDD #0

	JSR DISPLAY_LCD

LOOP:

	PUTS_SCI0 #PROMPT_SETUP
	GETC_SCI0
	CMPB #'1'
	BEQ SET_MIN
	CMPB #'2'
	BEQ SET_MAX
	CMPB #'3'
	LBEQ SET_STEP
	CMPB #'4'
	LBEQ PROMPT
	CMPB #'5'
	LBEQ QUIT
	PUTS_SCI0 #NEWLINE
	BRA LOOP

SET_MIN:

	PUTS_SCI0 #NEWLINE
	PUTS_SCI0 #PROMPT_MIN
	GETS_SCI0 #STR_BUFFER
	ATOI #STR_BUFFER,INT_BUFFER
	LDD INT_BUFFER
	CPD #36
	BLO SET_MIN			; min too low
	CPD #84
	BHI SET_MIN			; min too high
	CPD MAXIMUM
	BHI SET_MIN			; min can't exceed max
	STD MINIMUM			; min is valid. store it.
	BRA LOOP			; back to main menu

SET_MAX:

        PUTS_SCI0 #NEWLINE
        PUTS_SCI0 #PROMPT_MAX
        GETS_SCI0 #STR_BUFFER
        ATOI #STR_BUFFER,INT_BUFFER
        LDD INT_BUFFER
        CPD #36
        BLO SET_MAX                     ; max too low
        CPD #84
        BHI SET_MAX                     ; min too high
        CPD MINIMUM
        BLO SET_MAX                     ; max can't be less than min
        STD MAXIMUM                     ; min is valid. store it. 
        LBRA LOOP			; back to main menu

SET_STEP:

        PUTS_SCI0 #NEWLINE
        PUTS_SCI0 #PROMPT_STEP
        GETS_SCI0 #STR_BUFFER
        ATOI #STR_BUFFER,INT_BUFFER
        LDD INT_BUFFER
        CPD #1
        BLO SET_STEP                    ; step is too low
        CPD #4
        BHI SET_STEP			; step is too high
	STD INCREMENT
        LBRA LOOP                        ; back to main menu

PROMPT:

	PUTS_SCI0 #NEWLINE
	PUTS_SCI0 #PROMPT_ROT
	GETC_SCI0
	CMPB #'1'
	BEQ FR_CW
	CMPB #'2'
	BEQ FR_CCW
	CMPB #'3'
	BEQ S_CW
	CMPB #'4'
	BEQ S_CCW
	CMPB #'5'
	LBEQ LOOP			; back to main menu
	PUTS_SCI0 #NEWLINE
	BRA PROMPT			; back to rotation menu

FR_CW:

	LDD MAXIMUM
	PSHD
	MOVB 1,SP,PWMDTY4
	PULD
	JSR DISPLAY_LCD
	BRA PROMPT	

FR_CCW:

	LDD MINIMUM
	PSHD
	MOVB 1,SP,PWMDTY4
	JSR DISPLAY_LCD
	BRA PROMPT

S_CW:

	;max duty is 84. can't exceed this
	LDAB PWMDTY4
	CMPB #95
	BHI PROMPT
	LDD INCREMENT
	PSHD
	LDAA PWMDTY4
	LDAB 1,SP
	ABA		;add dty plus increment 
	STAA PWMDTY4
	PULD
	JSR DISPLAY_LCD
	BRA PROMPT

S_CCW:

        ;max duty is 84. can't exceed this
        LDAB PWMDTY4
        CMPB #25 
        BLO PROMPT   
        LDD INCREMENT
        PSHD
        LDAA PWMDTY4
        LDAB 1,SP 
        SBA             ;add dty minus increment 
        STAA PWMDTY4
        PULD
	JSR DISPLAY_LCD
        LBRA PROMPT

QUIT:

	BCLR PWME,BIT4	;turn off pwm ch 4
	RTS

DISPLAY_LCD:

	LCD_CURSOR 0,0
	PUTS_LCD #BLANK_LCD_LINE
	LCD_CURSOR 0,0

	LDAB PWMDTY4
	CLRA
	STD INT_BUFFER
	ITOA INT_BUFFER,#STR_BUFFER
	PUTS_LCD #STR_BUFFER
	PUTS_LCD #DENOM
	RTS
