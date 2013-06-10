; vim: set filetype=asmhc12:

; This program has us using some of the macros provided by Dr. Stapleton.

; Instructions:

; a. First, output a prompt to the terminal screen via SCI0 asking the user to
; enter his/her name.  

; b. Next, input a string from the keyboard via SCI0 which is assumed to be the
; user’s name.  

; c. Next, your program should output a message “Hello name, the
; sum of all the ASCII codes in your name is ##.”  For this “name” should be
; replaced with whatever string the user entered after the name prompt.  The
; token “##” should be replaced with a number calculated by adding all of the
; “unsigned char” ASCII codes for the letters entered by the user in their
; name.  

; d. Next, your program should output a scond message on a new line “Your lucky
; number is ##.”  The token “##” should be replaced with a number calculated
; dividing the sum of ASCII codes previously calculated by 20 then adding 1 to
; the remainder of the division.  

#INCLUDE ../HC12TOOLS.INC

	ORG $1000

STR_NAME	DS.B 80		; User's name.
INT_SUM		DS.W 1		; Sum of user's name's ascii codes.
STR_SUM		DS.B 10		; string format of sum
INT_LUCKY	DS.W 1		; lucky number token
STR_LUCKY	DS.B 10		; string format of lucky
NEWLINE		DC.B CR,LF,NULL ; newline.
PROMPT_GETNAME	DC.B "Please input username",CR,LF,NULL 
OUTPUT_NAME	DC.B "Hello %s, the sum of all the ASCII codes in your name is %i.",CR,LF,NULL
OUTPUT_LUCKY	DC.B "Your lucky number is %i.",CR,LF,NULL

	ORG $2000

MAIN:

	LIBRARY_VERSION

	PUTS_SCI0 #PROMPT_GETNAME
	GETS_SCI0 #STR_NAME

	JSR SUMOF

	PRINTF_DBUG12 #OUTPUT_NAME, #STR_NAME, INT_SUM

;	PUTS_SCI0 #NEWLINE
;	ITOA INT_SUM,#STR_SUM
;	PUTS_SCI0 #STR_SUM
;	PUTS_SCI0 #NEWLINE
;	LDD INT_SUM

	JSR LUCKY

	PRINTF_DBUG12 #OUTPUT_LUCKY, INT_LUCKY

;	PUTS_SCI0 #NEWLINE
;	ITOA INT_LUCKY,#STR_LUCKY
;	PUTS_SCI0 #STR_LUCKY
;	PUTS_SCI0 #NEWLINE

	RTS

SUMOF:

	LDX #0
	STX INT_SUM	; Initialize sum to zero
	LDAA #NULL
	CMPA STR_NAME,X	; check that we don't have null terminator right off the bat
	BNE LOOP1
	RTS

LOOP1:

	LDD INT_SUM	; load sum from memory
	ADDB STR_NAME,X ; add the byte to int_sum	
	ADCA #0		; pick up the carry if we hit it	
	STD INT_SUM	; store new sum back into memory
	INX
	LDAA #NULL
	CMPA STR_NAME,X ; is next char null terminator? if so, leave loop.
	BNE LOOP1
	RTS

LUCKY:

	LDY #0
	STY INT_LUCKY	; Initialize lucky to zero
	LDD INT_SUM
	LDX #20
	EDIV
	STD INT_LUCKY
	LDX #1
	INC INT_LUCKY,X
	RTS
