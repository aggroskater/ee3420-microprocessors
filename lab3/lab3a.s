; vim: set filetype=asmhc12:

; 1. You are to write a subroutine named ADD32 which should operate as follows:
; * The 16-bit value in register X is to be treated as the address of the 32-bit
; “destination” number. The 16-bit value in register Y is to be treated as the
; address of the 32-bit “source” number.
; * The operation performed should be “destination = destination + source”.
; * The subroutine should only change the 32-bit data at the “destination” address
; and should leave the 32-bit data at the “source” address unchanged.
; * Upon return from the subroutine, all registers should be returned to their
; original values with the following exception. The C, Z, N, and V flags in
; the CCR should be set or cleared as appropriate for an addition instruction.
; * Follow the pattern used by ADDD where possible.

#INCLUDE ../HC12TOOLS.INC

	ORG $1000

INT_A		DS.W 2		; int a 
INT_B		DS.W 2		; int b
INT_SP		DS.W 1		; stack pointer address
STR_SP		DS.B 10		; stack pointer address as string.
INT_CCR		DS.B 2
STR_CCR		DS.B 10
NEWLINE		DC.B CR,LF,NULL ; newline.
OUTPUT1		DC.B "In ADD32",CR,LF,NULL
CAR1		DC.B "In Carry 1",CR,LF,NULL
CAR0		DC.B "In Carry 0",CR,LF,NULL
NEGSET		DC.B "IN NEG SET",CR,LF,NULL
NEGCLEAR	DC.B "IN NEG CLEAR",CR,LF,NULL
ZEROHIGH	DC.B "IN ZERO HIGH",CR,LF,NULL
ZEROLOW		DC.B "IN ZERO LOW",CR,LF,NULL
ZEROSET		DC.B "IN ZERO SET",CR,LF,NULL
ZEROCLEAR	DC.B "IN ZERO CLEAR",CR,LF,NULL
DEBUG1		DC.B "MADE IT OUT OF NBIT CHECKS",CR,LF,NULL
DEBUG2		DC.B "ABOUT TO RTS FROM NEG_BIT_CLEAR",CR,LF,NULL
NEXT0LABEL	DC.B "Hit next0.",CR,LF,NULL
VCLEAR		DC.B "Overflow not found. Clearing V.",CR,LF,NULL
VSET		DC.B "Overflow found. Setting V.",CR,LF,NULL
CHECKV		DC.B "Original operands were same sign. Checking overflow.",CR,LF,NULL
FINISHEDOUT	DC.B "Overflow and Carry checks complete.",CR,LF,NULL

	ORG $2000

MAIN:

	LDX #0
	LDD #$FFFF
	STD INT_A,X
	LDD #$FFFF
	INX
	INX
	STD INT_A,X
	DEX
	DEX
	LDD #$0000
	STD INT_B,X
	LDD #$0001
	INX
	INX
	STD INT_B,X

	JSR ADD32
	; carry appropriately set at this point

	; check neg

	BRSET INT_A,#%10000000,N_BIT_SET
R_N_BIT_SET:
	BRCLR INT_A,#%10000000,N_BIT_CLEAR
R_N_BIT_CLEAR:

	; neg appropriately set

	; check zero

;	PUTS_SCI0 #DEBUG1

	JSR Z_BIT_CHECK_HIGH
R_Z_BIT_CHECK:
	; zero appropriately set

	; check overflow

	RTS

N_BIT_SET:

;	PUTS_SCI0 #NEGSET
;	LDAA #0
	TFR CCR,A
	PSHA
	BSET 0,SP,#%00001000
	PULA
	TFR A,CCR
;	RTS
	JMP R_N_BIT_SET

N_BIT_CLEAR:

;	PUTS_SCI0 #NEGCLEAR
;	LDAA #0
	TFR CCR,A
	PSHA
	BCLR 0,SP,#%00001000
	PULA
	TFR A,CCR
;	PUTS_SCI0 #DEBUG2
;	RTS
	JMP R_N_BIT_CLEAR

Z_BIT_CHECK_HIGH:

;	PUTS_SCI0 #ZEROHIGH
	TFR CCR,A
	PSHA
	LDD 0,X
	CPD #0
	BEQ Z_BIT_CHECK_LOW
	CPD #0
	BNE Z_BIT_CLEAR
;	RTS

Z_BIT_CHECK_LOW:

;	PUTS #ZEROLOW
	LDD 2,X
	CPD #0
	BEQ Z_BIT_SET
	CPD #0
	BNE Z_BIT_CLEAR
;	RTS

Z_BIT_SET:

;	PUTS #ZEROSET
	BSET 0,SP,#%00000100
	PULA
	TFR A,CCR
;	RTS
	JMP R_Z_BIT_CHECK

Z_BIT_CLEAR:

;	PUTS #ZEROCLEAR
	BCLR 0,SP,#%00000100
	PULA
	TFR A,CCR
;	RTS
	JMP R_Z_BIT_CHECK

;V_BIT:



ADD32:

	PUTS_SCI0 #OUTPUT1
	LDX #INT_A
	LDY #INT_B

	LDAA 0,X
	LDAB 0,Y
	
	ANDA #%10000000
	ANDB #%10000000

;	JSR OUTPUTSP

	PSHA
	PSHB

;	JSR OUTPUTSP

	LDD 2,X
	ADDD 2,Y
	LBCS CARRY1
	STD 2,X	
NEXT1:
	LDD 0,X
	ADDD 0,Y
	LBCS CARRY0
	STD 0,X	
NEXT0:
;	PUTS_SCI0 #NEXT0LABEL

;	JSR OUTPUTSP

	TFR CCR,A
	PSHA

;	JSR OUTPUTSP

	LDAA 2,SP
	EORA 1,SP
	PSHA
	BRCLR 0,SP,#%10000000,CHECK_V
	BRA V_CLEAR
	
CHECK_V:
	PUTS_SCI0 #CHECKV
	PULA
	LDAA 2,SP
	EORA 0,X
	PSHA
	BRSET 0,SP,#%10000000,V_SET
	BRA V_CLEAR

V_CLEAR:

	PUTS_SCI0 #VCLEAR
	PULA
	BCLR 0,SP,#%00000010
	JMP FINISHED
	

V_SET:

	PUTS_SCI0 #VSET
	PULA
;	JSR OUTPUTSP
	BSET 0,SP,#%00000010
	JMP FINISHED

FINISHED:

	PUTS_SCI0 #FINISHEDOUT
	PULA			; this should be the CCR
	TFR A,CCR
;	JSR OUTPUTCCR
	PULB			; clear MSB info off stack.
	PULB			; clear MSB info off stack.
				; at this point, SP should point to rtn. addr.
;	JSR OUTPUTSP
;	JSR OUTPUTCCR
	RTS

CARRY1:

	PUTS_SCI0 #CAR1
	STD 2,X
	LDD 0,X
	ADDD #1
	BCS BIGOVERFLOW		; the top half of int_a was FFFF
	STD 0,X
	JMP NEXT1

BIGOVERFLOW:

	STD 0,X
	TFR CCR,A
	PSHA
	LDD #0
	ADDD 0,Y
	STD 0,X
	PULA
	TFR A,CCR
	JMP NEXT0

CARRY0:

	PUTS_SCI0 #CAR0
	STD 0,X
;	LDAA #0
	TFR CCR,A
	PSHA
	BSET 0,SP,#%00000001
	PULA
	TFR A,CCR
	JMP NEXT0

OUTPUTSP:

	STS INT_SP
	ITOA_16_FIXED INT_SP,#STR_SP
	PUTS_SCI0 #STR_SP
	PUTS_SCI0 #NEWLINE
	RTS

OUTPUTCCR:

	TFR CCR,D
	STD INT_CCR
	ITOA_16_FIXED INT_CCR,#STR_CCR
	PUTS_SCI0 #STR_CCR
	PUTS_SCI0 #NEWLINE
	RTS	
