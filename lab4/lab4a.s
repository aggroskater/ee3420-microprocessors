; vim: set filetype=asmhc12:

#INCLUDE ../HC12TOOLS.INC
;#INCLUDE ../KEYPAD_IO.INC
;#INCLUDE ../LCD_IO.INC

	ORG $1000

COUNTER	DS.B 1

	ORG $2000

MAIN:

	JSR E_DIP
	JSR E_LED
	JSR D_SEG

	BSET DDRB,#%11111111	; set port b to output
	MOVB #0,COUNTER		; initialize counter
	LDY #25

LOOPY:

	MOVB COUNTER,PORTB	; show the counter value on the leds
	JSR E_LED		; enable leds
	LDAA COUNTER		;
	ADDA PORTH		; add dip to counter
	STAA COUNTER		;

	DELAY_BY_MS #1500	; display counter on leds for 1.5s.
	JSR D_LED		; disable leds
	DELAY_BY_MS #500	; wait for half a second and repeat the loop.
	DBNE Y,LOOPY
	
	RTS

E_DIP:

	BCLR DDRH,#%11111111	; set h (dip switches) to input
	RTS

E_LED:

	BSET DDRJ,#%00000010	; set j1 to output
	BCLR PORTJ,#%00000010	; set j1 to output 0V, permitting led's to
				; light up
	RTS

D_LED:

	BSET PORTJ,#%00000010	; set j1 to output high, disabling led's
	RTS

D_SEG:

	BSET DDRP,#%00001111	; set p (seg's) to input (effectively off)
	RTS
