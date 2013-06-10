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
INCHECK		DC.B "In check subr.",CR,LF,NULL
INFAIL		DC.B "In fail subr.",CR,LF,NULL
INFOUND		DC.B "In found subr.",CR,LF,NULL

	ORG $2000

MAIN:

	LIBRARY_VERSION

	JMP GET_SEED1

PASSED1:

	PUTS_SCI0 #PASS
	ATOI #STR_SEED1,INT_SEED1
	JMP GET_SEED2

PASSED2:

	JSR OUTPUT
	RTS

GET_SEED2:

	PUTS_SCI0 #PROMPT_SEED2
	GETS_SCI0 #STR_SEED2
	LDX #0
	JMP CHECK_SEED2

CHECK_SEED2:

	LDAA STR_SEED2,X
	CMPA #58
	BHI FAIL3
	LDAA STR_SEED2,X
	CMPA #47
	BLO FAIL3
	INX
	CPX #10
	BEQ FAIL3
	JMP CHECK_SEED2

FAIL3:

	LDAA #NULL
	CMPA STR_SEED2,X
	BEQ FOUND_TERMINATOR2

FAIL4:

	PRINTF_DBUG12 #BAD, #STR_SEED2
	JMP GET_SEED2	

FOUND_TERMINATOR2:

	CPX #0
	BNE DIFFCHECK		; not empty string. check not equal to seed1.
	JMP FAIL4		; empty string. try again.

DIFFCHECK:

	ATOI #STR_SEED2,INT_SEED2
	LDY INT_SEED2
	CMPY INT_SEED1
	BEQ FAIL4
	JMP PASSED2

GET_SEED1:

	PUTS_SCI0 #PROMPT_SEED1
	GETS_SCI0 #STR_SEED1

	LDX #0
	JMP CHECK_SEED1

CHECK_SEED1:

;	PUTS_SCI0 #INCHECK
;	LDAA #58
;	CMPA STR_SEED1,X
	LDAA STR_SEED1,X
	CMPA #58
	BHI FAIL1		; char too big. failed.
;	LDAA #47
;	CMPA STR_SEED1,X
	LDAA STR_SEED1,X
	CMPA #47
	BLO FAIL1		; char too small. either invalid or null.
	INX
	CPX #10
	BEQ FAIL1		; never found null-terminator. input too large.
	JMP CHECK_SEED1
	
FAIL1:

;	PUTS_SCI0 #INFAIL
	LDAA #NULL
	CMPA STR_SEED1,X
	BEQ FOUND_TERMINATOR1	; found terminator. not an invalid char.
FAIL2:
;	PUTS_SCI0 #PROMPT_FAIL
	PRINTF_DBUG12 #BAD, #STR_SEED1
	LDAB STR_SEED1,X
	JMP GET_SEED1

FOUND_TERMINATOR1:

;	PUTS_SCI0 #INFOUND
	CPX #0			; check for no-input
	LBNE PASSED1		; found null terminator. wasn't first char. 
	JMP FAIL2		; It WAS first char. user didn't input anything.

OUTPUT:

;	PUTS_SCI0 #PASS
	PUTS_SCI0 #STR_SEED1
	PUTS_SCI0 #NEWLINE
	LDY #10
	JSR LOOP
	RTS

LOOP:

	PUTS_SCI0 #STR_SEED2	
	PUTS_SCI0 #NEWLINE

	CLC				; set V to zero.
	LDD INT_SEED2
	ADDD INT_SEED1	
	BCS ESCAPE
	LDX INT_SEED2
	STX INT_SEED1
	STD INT_SEED2

	ITOA INT_SEED2,#STR_SEED2
	BRA LOOP
ESCAPE:
	RTS

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
