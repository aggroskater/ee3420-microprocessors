; vim: set filetype=asmhc12:

#INCLUDE ../HC12TOOLS.INC

;export symbols

;	XDEF Entry
;	ABSENTRY Entry

;RTI vector location when Dbug-12 is present

	ORG $1000

COUNTER	DS.W 1
PROMPT	DC.B "LOL INTERRUPTS.",CR,LF,NULL
DBUG	DC.B "LOL DEBUG.",CR,LF,NULL

	ORG $2000

MAIN:

	;put proper address in vector table
	LDD #0
	STD COUNTER
	LDD #ISR_ROUTINE
	STD UserRTI		;location of RTI vector when DBug-12 is active.

	;RTI setup
	MOVB #%10000000,CRGINT	;enables RTIs
	MOVB #%00010000,RTICTL	;sets prescaler to 2^10
				;results in interrupt every 0.000128 seconds.
				; (OSCCLK is 8MHz)
				; ergo, 1/(8MHz/(1*2^10)) = 0.000128 seconds. 
	PUTS_SCI0 #DBUG
	CLI			;enable interrupts globally
	PUTS_SCI0 #DBUG

LOOP:	BRA LOOP	;do this forEVAH
			;the idea is that we should be printing out PROMPT
			;to SCI0 every 10000*0.000128 seconds or every
			; 1.28 seconds.

ISR_ROUTINE:

	LDD #8000
	CPD COUNTER
	BEQ ECHO
	LDD COUNTER
	ADDD #1
	STD COUNTER
;	PUTS_SCI0 #DBUG
	MOVB #%10000000,CRGFLG	;acknowledge that interrupt has executed.	
	RTI

ECHO:

	LDD #0
	STD COUNTER
	PUTS_SCI0 #PROMPT
	MOVB #%10000000,CRGFLG	;acknowledge that interrupt has executed.
	RTI

