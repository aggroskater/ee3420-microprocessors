; vim: set filetype=asmhc12:

; This program has us using some of the macros provided by Dr. Stapleton.

; Instructions:

; Output fibonacci sequence given two seeds by user.
; Check that user provides numbers only, F_1 != F_2 != 0.
; Do not exceed 2^16 for final fibonacci number.

#INCLUDE ../HC12TOOLS.INC
#INCLUDE ../ALU32.INC

	ORG $1000

INT_SEED1	DS.W 1		; seed1
INT_SEED3	DS.W 1
INT_SEED2	DS.W 1		; seed2
INT_SEED4	DS.W 1
STR_SEED1	DS.B 8		;
STR_SEED3	DS.B 8		;
STR_SEED2	DS.B 8		;
STR_SEED4	DS.B 8		;
NEWLINE		DC.B CR,LF,NULL ; newline.
PROMPT_SEED1	DC.B "Please input first seed, less than 2^16.",CR,LF,NULL 
PROMPT_SEED2	DC.B "Please input second seed, less than 2^16.",CR,LF,NULL
PROMPT_FAIL	DC.B "Try again. Input not a number or too big.",CR,LF,NULL
BAD		DC.B "Bad input is %s",CR,LF,NULL
PASS		DC.B "Input valid.",CR,LF,NULL
TOOBIG		DC.B "Next Fibonacci number cannot fit in 32 bits. Exiting.",CR,LF,NULL

	ORG $2000

MAIN:

	LIBRARY_VERSION
	LDD #0
	STD INT_SEED1
	STD INT_SEED2
	STD INT_SEED3
	STD INT_SEED4

	JMP GET_SEED1

PASSED1:

	PUTS_SCI0 #PASS
	ATOI #STR_SEED3,INT_SEED3
	JMP GET_SEED2

PASSED2:

	JSR OUTPUT
	RTS

GET_SEED2:

	PUTS_SCI0 #PROMPT_SEED2
	GETS_SCI0 #STR_SEED4
	LDX #0
	JMP CHECK_SEED2

CHECK_SEED2:

	LDAA STR_SEED4,X
	CMPA #58
	BHI FAIL3
	LDAA STR_SEED4,X
	CMPA #47
	BLO FAIL3
	INX
	CPX #10
	BEQ FAIL3
	JMP CHECK_SEED2

FAIL3:

	LDAA #NULL
	CMPA STR_SEED4,X
	BEQ FOUND_TERMINATOR2

FAIL4:

	PRINTF_DBUG12 #BAD, #STR_SEED4
	JMP GET_SEED2	

FOUND_TERMINATOR2:

	CPX #0
	BNE DIFFCHECK		; not empty string. check not equal to seed1.
	JMP FAIL4		; empty string. try again.

DIFFCHECK:

	ATOI #STR_SEED4,INT_SEED4
	LDY INT_SEED4
	CMPY INT_SEED3
	BEQ FAIL4
	JMP PASSED2

GET_SEED1:

	PUTS_SCI0 #PROMPT_SEED1
	GETS_SCI0 #STR_SEED3

	LDX #0
	JMP CHECK_SEED1

CHECK_SEED1:

;	PUTS_SCI0 #INCHECK
;	LDAA #58
;	CMPA STR_SEED1,X
	LDAA STR_SEED3,X
	CMPA #58
	BHI FAIL1		; char too big. failed.
;	LDAA #47
;	CMPA STR_SEED1,X
	LDAA STR_SEED3,X
	CMPA #47
	BLO FAIL1		; char too small. either invalid or null.
	INX
	CPX #10
	BEQ FAIL1		; never found null-terminator. input too large.
	JMP CHECK_SEED1
	
FAIL1:

;	PUTS_SCI0 #INFAIL
	LDAA #NULL
	CMPA STR_SEED3,X
	BEQ FOUND_TERMINATOR1	; found terminator. not an invalid char.
FAIL2:
;	PUTS_SCI0 #PROMPT_FAIL
	PRINTF_DBUG12 #BAD, #STR_SEED3
	LDAB STR_SEED3,X
	JMP GET_SEED1

FOUND_TERMINATOR1:

;	PUTS_SCI0 #INFOUND
	CPX #0			; check for no-input
	LBNE PASSED1		; found null terminator. wasn't first char. 
	JMP FAIL2		; It WAS first char. user didn't input anything.

OUTPUT:

;	PUTS_SCI0 #PASS
	PUTS_SCI0 #STR_SEED3
	PUTS_SCI0 #NEWLINE
	PUTS_SCI0 #STR_SEED4
	PUTS_SCI0 #NEWLINE
;	LDY #10
	JSR LOOP1
	RTS

LOOP1:

	CLC				; set V to zero.
	LDX #INT_SEED1
	LDY #INT_SEED2

	JSR ADDEM
	BCS ESCAPE1

	ITOA_16_FIXED $1000,#STR_SEED1
	PUTS_SCI0 #STR_SEED1
	ITOA_16_FIXED $1002,#STR_SEED3
	PUTS_SCI0 #STR_SEED3
	PUTS_SCI0 #NEWLINE

	BRA LOOP2

ESCAPE1:

;	PUTS_SCI0 #STR_SEED1
;	PUTS_SCI0 #NEWLINE
	PUTS_SCI0 #TOOBIG
	RTS

LOOP2:

	CLC
	LDX #INT_SEED2
	LDY #INT_SEED1

	JSR ADDEM
	BCS ESCAPE2

	ITOA_16_FIXED $1004,#STR_SEED2
	PUTS_SCI0 #STR_SEED2
	ITOA_16_FIXED $1006,#STR_SEED4
	PUTS_SCI0 #STR_SEED4
	PUTS_SCI0 #NEWLINE

	LBRA LOOP1

ESCAPE2:

;	PUTS_SCI0 #STR_SEED2
;	PUTS_SCI0 #NEWLINE
	PUTS_SCI0 #TOOBIG
	RTS

ADDEM:

	ADD32
	RTS

