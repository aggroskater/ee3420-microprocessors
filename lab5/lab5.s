; vim: set filetype=asmhc12:

;Cycle counts based off of Clock A or B, Prescale 1 (The raw 24 MHz clock 
;from the HCS12, not scaled down at all). Use concatenated channels since 
;those numbers wont fit in 8 bits. Also, we get added precision by using the 
;concatenated channels.

; row 1
;697 Hz -> (1/697)/(0.00000004167) cycles = 34430.531... cycles
; row 2
; 770 Hz -> (1/770)/(0.00000004167) cycles = 31166.33... cycles
; row 3
; 852 Hz -> (1/852)/(0.00000004167) cycles = 28166.76074... cycles
; row 4
; 941 Hz -> (1/941)/(0.00000004167) cycles = 25502.74193... cycles
; column 1
; 1209 Hz -> (1/1209)/(0.00000004167) cycles = 19849.52866... cycles = 19850
;column 2
; 1336 Hz -> (1/1336)/(0.00000004167) cycles = 17962.63485... cycles
; column 3
; 1477 Hz -> (1/1477)/(0.00000004167) cycles = 16247.85386... cycles = 16248
; column 4
; 1633 Hz -> (1/1633)/(0.00000004167) cycles = 14695.70... cycles = 14696

#INCLUDE ../HC12TOOLS.INC
;#INCLUDE ../KEYPAD_IO.INC
;#INCLUDE ../LCD_IO.INC

	ORG $1000

; buffer holds the last-inputted key-press in its ASCII representation.

BUFFER	DS.B 1

; length holds the duration to hold the tone. At least 40ms. More if
; dip indicates more.

LENGTH	DS.W 1

; ROW_TONES holds the row period for each possible GETC_KEYPAD input.
; These values line up with KEYPAD_OPTS. We can get the duty 
; cycle by a simple bit shift, since the duty cycle is 50% and is just a 
; division of the period by 2.

ROW_TONES	DC.W 25502,34430,34430,34430	; 0 1 2 3
		DC.W 31166,31166,31166,28166	; 4 5 6 7
		DC.W 28166,28166,34430,31166	; 8 9 A B
		DC.W 28166,25502,25502,25502	; C D E F

COL_TONES	DC.W 17962,19850,17962,16248	; 0 1 2 3
		DC.W 19805,17962,16248,19850	; 4 5 6 7
		DC.W 17962,16248,14696,14696	; 8 9 A B
		DC.W 14696,14696,19850,16248	; C D E F

; KEYPAD_OPTS holds all of the possible ASCII values that GETC_KEYPAD can 
; dump to allocator b. These line up with the pairs in the ROW_TONES and 
; COL_TONES arrays.

KEYPAD_OPTS     DC.B $30,$31,$32,$33,$34,$35,$36,$37    ; 0 1 2 3 4 5 6 7
                DC.B $38,$39,$41,$42,$43,$44,$45,$46    ; 8 9 A B C D E F

	ORG $2000

MAIN:

; prep pwm and lcd

	JSR D_PWM
	JSR PREP_PWM
	JSR PREP_LCD

;turn on dip and turn off segs and leds. I don't want any blinkenlights.

	JSR E_DIP
	JSR D_SEG
	JSR D_LED

; read dip to set initial delay

	JSR SET_DELAY

MAINLOOP:

	;turn speakers off, wait 10 ms

	JSR D_PWM
	DELAY_BY_MS #10	

	;poll keypad. GETC_KEYPAD waits until we press a key.

	GETC_KEYPAD	; this routine dumps the ASCII code of the pressed key
			; (0-9,A-F) into allocator B.
	STAB BUFFER	; put into buffer

	;output key to lcd

	PUTC_LCD	; allocator b should still be holding the pressed key.

	;set delay based off dip

	JSR SET_DELAY

	;output appropriate freqs to pwm channels

	LDX #15

FINDKEY:

	CMPB KEYPAD_OPTS,X
	BEQ GOTKEY
	DBNE X,FINDKEY	

	;X now holds the index of the inputted key. We can use this index
	;on the ROW_TONES and COL_TONES arrays.

GOTKEY:

	LDY ROW_TONES,X
	JSR LOAD_PWM_CH5
	LDY COL_TONES,X
	JSR LOAD_PWM_CH7

	;turn on pwm now that everything is set

	JSR E_PWM

	;hold tone for delay length

	DELAY_BY_MS LENGTH

	;repeat

	BRA MAINLOOP

;-------------------------------------------------------------------;
;-------------------------------------------------------------------;

;HELPER ROUTINES BELOW

;-------------------------------------------------------------------;
;-------------------------------------------------------------------;	

LOAD_PWM_CH5:

; maybe we can push the values onto the stack first and just ref them

; set period

	PSHY
	MOVW 0,SP,PWMPER4

; divide by 2 via bit shift

	LSR 0,SP

	MOVW 0,SP,PWMDTY4
	PULY
	RTS

LOAD_PWM_CH7:

	PSHY
	MOVW 0,SP,PWMPER6

; divide by 2 via bit shift

	LSR 0,SP

	MOVW 0,SP,PWMDTY6
	PULY
	RTS

SET_DELAY:

	PSHD			; save original state of A:B
	MOVB PORTH,LENGTH	; put delay into length.
	LDD LENGTH
	TFR A,B			; PORTH is originally in high bit. need to
				; put in low half
	LDAA #0			; and zero out upper half
	CPD #40			; now compare will work
	BLO TOOLOW		; if delay from dip is too low, set to 40
	STD LENGTH		; delay way bigger than 40. store in length.
	PULD			; restore original state of A:B
	RTS

TOOLOW:
	LDD #40
	STD LENGTH		; delay from dip was too low. set to 40.
	PULD			; restore original state of A:B
	RTS

E_PWM:

	BSET PWME,#%11110000    ;ENABLE PWM CHANNEL 4/5,6/7
	RTS

D_PWM:

	BCLR PWME,#%11110000    ;Disable PWM CHANNEL 4/5,6/7
	RTS

PREP_PWM:

;This section sets up PWM to concatenate channels and leave 
;them prepped to be enabled
        BSET PWMCTL,#%11000000 ;concatenate 4 and 5, and 6 and 7
        BSET PWMPOL,#%11110000 ;CHANNEL 4/5, 6/7 ACTIVE HIGH 
        BCLR PWMCLK,#%11110000 ;CHANNEL 4/5, 6/7 CLOCK A
			       ;(0 = A or B ; 1 = SA or SB)                 
        MOVB #$00,PWMPRCLK ;PWM CLOCK A SCALE=1  

	RTS

PREP_LCD:

	LCD_SETUP
	LCD_CURSOR 0,0
	RTS

E_DIP:

	BCLR DDRH,#%11111111	; all of h (dip switches) are input
	RTS

D_LED:

	BCLR DDRJ,#%00000010	; set j1 to output
	BSET PORTJ,#%00000010	; set j1 to output high, disabling leds.
	RTS

D_SEG:

	BSET DDRP,#%00001111	; set p (segs) to input (effectively off).
	RTS
