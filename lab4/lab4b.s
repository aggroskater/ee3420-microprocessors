; vim: set filetype=asmhc12:

#INCLUDE ../HC12TOOLS.INC
;#INCLUDE ../KEYPAD_IO.INC
;#INCLUDE ../LCD_IO.INC

	ORG $1000

PROMPT	DC.B "Input digit.",NULL
INPUT	DS.B 4
DIGIT_PATTERN 	DC.B $3F,$06,$5B,$4F,$66,$6D,$7D,$07	; 0 1 2 3 4 5 6 7
		DC.B $7F,$6F,$77,$7C,$39,$5E,$79,$71	; 8 9 a b c d e f
KEYPAD_OPTS	DC.B $30,$31,$32,$33,$34,$35,$36,$37	; 0 1 2 3 4 5 6 7
		DC.B $38,$39,$41,$42,$43,$44,$45,$46	; 8 9 A B C D E F

	ORG $2000

MAIN:

	JSR E_SEGS
	LCD_SETUP
	LCD_CURSOR 0,0

	PUTS_SCI0 #PROMPT
	PUTS_LCD #PROMPT 

	LCD_CURSOR 1,0

	LDY #10
LOOPY:

	GETC_KEYPAD
	PUTC_LCD
	STAB INPUT

	LDX #15

SEGFIND:

	CMPB KEYPAD_OPTS,X
	BEQ DISP
	DBNE X,SEGFIND
	
DISP:

	LDAA DIGIT_PATTERN,X
	PSHA
	MOVB 0,SP,PORTB	
	PULA
	DBNE Y,LOOPY
	RTS


E_SEGS:

	;enable leds for now
;	BSET DDRJ,#%00000010
;	BCLR PORTJ,#%00000010

	;enable segs
	BSET DDRB,#%11111111	; set all of port b to output

	BCLR DDRP,#%00001000	; Set P3 to output (rightmost seg)
	BSET DDRP,#%00000111	; set P0,P1,P2 to input (effectively off)
	BCLR PORTP,#%00001000	; set rightmost seg jumper to zero, permitting
				; illumination.
	MOVB #$79,PORTB		; initial state.
	BSET PORTJ,#%00000010	; turn off led's
	RTS
