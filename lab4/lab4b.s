; vim: set filetype=asmhc12:

#INCLUDE ../HC12TOOLS.INC
;#INCLUDE ../KEYPAD_IO.INC
;#INCLUDE ../LCD_IO.INC

	ORG $1000

PROMPT	DC.B "Input digit.",NULL
INPUT	DS.B 4

	ORG $2000

MAIN:

	JSR E_SEGS
	LCD_SETUP
	LCD_CURSOR 0,0

	PUTS_SCI0 #PROMPT
	PUTS_LCD #PROMPT 
;	GETC_KEYPAD
;	PUTC_LCD
;	STAB INPUT
	RTS


E_SEGS:

	BCLR DDRP,#%00000001	; Set only rightmost seg to on.
	BSET PORTJ,#%00000010	; turn off led's
	RTS
