; vim: set filetype=asmhc12:

; This program has us using some of the macros provided by Dr. Stapleton.

; Instructions:

; Output fibonacci sequence given two seeds by user.
; Check that user provides numbers only, F_1 != F_2 != 0.
; Do not exceed 2^16 for final fibonacci number.

#INCLUDE ../HC12TOOLS.INC

	ORG $1000

INT_SEED1	DS.W 1		; seed1
STR_SEED1	DS.B 10		;
INT_SEED2	DS.W 1		; seed2
STR_SEED2	DS.B 10		;
NEWLINE		DC.B CR,LF,NULL ; newline.
PROMPT_SEED1	DC.B "Please input first seed, less than 2^16.",CR,LF,NULL 
PROMPT_SEED2	DC.B "Please input second seed, less than 2^16.",CR,LF,NULL
PROMPT_FAIL	DC.B "Try again. Input not a number or too big.",CR,LF,NULL
BAD		DC.B "Bad input is %s",CR,LF,NULL
INPUT		DC.B "You entered %s",CR,LF,NULL
PASS		DC.B "Input valid.",CR,LF,NULL

	ORG $2000

MAIN:

	LIBRARY_VERSION

	JSR GET_SEED1

PASSED1:

	PUTS_SCI0 #PASS
	RTS

GET_SEED1:

	PUTS_SCI0 #PROMPT_SEED1
	GETS_SCI0 #STR_SEED1

	JSR CHECK_SEED1

CHECK_SEED1:

	LDX #0
	LDAA #57
	CMPA STR_SEED1,X
	BHI FAIL1		; char too big. failed.
	LDAA #48
	CMPA STR_SEED1,X
	BLO FAIL1		; char too small. either invalid or null.
	INX
	CPX #10
	BEQ FAIL1		; never found null-terminator. input too large.
	JSR CHECK_SEED1
	
FAIL1:

	LDAA #NULL
	CMPA STR_SEED1,X
	BEQ FOUND_TERMINATOR	; found terminator. not an invalid char.
	PUTS_SCI0 #PROMPT_FAIL
	PRINTF_DBUG12 #BAD, #STR_SEED1
	LDAB STR_SEED1,X
	JSR GET_SEED1

FOUND_TERMINATOR:

	CPX #0			; check for no-input
	BNE PASSED1		; found null terminator. wasn't first char. 
	RTS			; It WAS first char. user didn't input anything.


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;	JSR SUMOF

;	PRINTF_DBUG12 #OUTPUT_NAME, #STR_NAME, INT_SUM

;	PUTS_SCI0 #NEWLINE
;	ITOA INT_SUM,#STR_SUM
;	PUTS_SCI0 #STR_SUM
;	PUTS_SCI0 #NEWLINE
;	LDD INT_SUM

;	JSR LUCKY

;	PRINTF_DBUG12 #OUTPUT_LUCKY, INT_LUCKY

;	PUTS_SCI0 #NEWLINE
;	ITOA INT_LUCKY,#STR_LUCKY
;	PUTS_SCI0 #STR_LUCKY
;	PUTS_SCI0 #NEWLINE

;	RTS

;SUMOF:

;	LDX #0
;	STX INT_SUM	; Initialize sum to zero
;	LDAA #NULL
;	CMPA STR_NAME,X	; check that we don't have null terminator right off the bat
;	BNE LOOP1
;	RTS

;LOOP1:

;	LDD INT_SUM
;	ADDB STR_NAME,X	
;	ADCA #0	
;	STD INT_SUM
;	INX
;	LDAA #NULL
;	CMPA STR_NAME,X ; is next char null terminator? if so, leave loop.
;	BNE LOOP1
;	RTS

;LUCKY:

;	LDY #0
;	STY INT_LUCKY	; Initialize lucky to zero
;	LDD INT_SUM
;	LDX #20
;	EDIV
;	STD INT_LUCKY
;	LDX #1
;	INC INT_LUCKY,X
;	RTS
