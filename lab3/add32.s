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

	JSR ADD32	; carries out actual addition routine

	BRSET INT_A,#%10000000,N_BIT_SET	; check if MSB of sum is set.

R_N_BIT_SET:

	BRCLR INT_A,#%10000000,N_BIT_CLEAR	; check if MSB of sum is clear.

R_N_BIT_CLEAR:

	JSR Z_BIT_CHECK_HIGH	; check to see if sum is zero.

R_Z_BIT_CHECK:

	RTS			; Subroutine is finished.

N_BIT_SET:

	TFR CCR,A		; put CCR onto stack so we don't lose state.
	PSHA
	BSET 0,SP,#%00001000	; set N bit.
	PULA
	TFR A,CCR		; restore CCR with Zero bit set.
	JMP R_N_BIT_SET

N_BIT_CLEAR:

	TFR CCR,A		; put CCR onto stack. Don't want to lose state.
	PSHA
	BCLR 0,SP,#%00001000	; clear N bit.
	PULA
	TFR A,CCR		; restore CCR
	JMP R_N_BIT_CLEAR

Z_BIT_CHECK_HIGH:

	TFR CCR,A		; put CCR onto stack.
	PSHA
	LDD 0,X			; compare top half of sum to zero.
	CPD #0
	BEQ Z_BIT_CHECK_LOW	; top half is zero. check bottom.
	CPD #0
	BNE Z_BIT_CLEAR		; top half isn't zero. Clear Z bit.

Z_BIT_CHECK_LOW:

	LDD 2,X			; compare bottom half of sum to zero.
	CPD #0
	BEQ Z_BIT_SET		; bottom half also zero. Set Z bit.
	CPD #0
	BNE Z_BIT_CLEAR		; bottom half not zero. Clear Z bit.

Z_BIT_SET:

	BSET 0,SP,#%00000100	; recall CCR already on stack. Set Z bit.
	PULA
	TFR A,CCR		; restore CCR
	JMP R_Z_BIT_CHECK

Z_BIT_CLEAR:

	BCLR 0,SP,#%00000100	; recall CCR already on stack. Clear Z bit.
	PULA
	TFR A,CCR		; restore CCR
	JMP R_Z_BIT_CHECK

ADD32:

	LDX #INT_A		; Load address of INT_A to X
	LDY #INT_B		; Load address of INT_B to X

	LDAA 0,X		; Load top byte of INT_A to A
	LDAB 0,Y		; Load top byte of INT_B to B
	
	ANDA #%10000000		; Get the MSB for INT_A
	ANDB #%10000000		; Get the MSB for INT_B

	PSHA			; store MSB of INT_A onto stack.
	PSHB			; store MSB of INT_B onto stack.
				; we use these for figuring out V flag later.

	LDD 2,X			; Begin addition routine. Add lower half.
	ADDD 2,Y
	LBCS CARRY1		; If carry was set, need to add 1 to upper half.
	STD 2,X			; carry not set, store lower half result.
NEXT1:
	LDD 0,X			; Add upper half
	ADDD 0,Y
	LBCS CARRY0		; If carry was set, need to set carry bit.
	STD 0,X	
NEXT0:

	TFR CCR,A		; Addition complete. C bit set appropriately.
				; Need to put CCR onto stack and inspect V bit.
	PSHA

	LDAA 2,SP		; XOR MSB of original two numbers. If zero,
				; both were same sign. Need to check for
				; overflow.
	EORA 1,SP		
	PSHA			; push result of EOR onto stack.

	BRCLR 0,SP,#%10000000,CHECK_V	; Original numbers were same sign. Check
					; for overflow
	BRA V_CLEAR			; Original numbers were opposite sign.
					; No overflow possible. Clear V.
	
CHECK_V:

	PULA				; get rid of EOR result. Don't need it.
	LDAA 2,SP			; compare MSB of original with sum.
	EORA 0,X
	PSHA
	BRSET 0,SP,#%10000000,V_SET	; if original and sum are different, 
					; we have overflow. Set V bit.
	BRA V_CLEAR			; No overflow. Clear V bit.

V_CLEAR:

	PULA				; Get rid of EOR result. Don't need it.	
	BCLR 0,SP,#%00000010		; Clear V bit (CCR is on top of stack
					; at this point)
	JMP FINISHED
	

V_SET:

	PULA				; Get rid of EOR result. Don't need it.
	BSET 0,SP,#%00000010		; Set V bit of CCR.
	JMP FINISHED

FINISHED:

	PULA			; this should be the CCR
	TFR A,CCR		; restore CCR

	PULB			; clear MSB info off stack.
	PULB			; clear MSB info off stack.

	RTS			; at this point, SP points to rtn addr.

CARRY1:

	STD 2,X			; store result of lower half addition.
	LDD 0,X			; add one to upper half.
	ADDD #1
	BCS BIGOVERFLOW		; the top half of int_a was FFFF
	STD 0,X			; store upper half
	JMP NEXT1		; proceed to add upper half

BIGOVERFLOW:

	STD 0,X			; store 0000 result into top half of sum.
	TFR CCR,A		; store CCR since it has Carry bit set now.
				; (STD doesn't affect C bit)
	PSHA
	LDD 0,X			; add top half
	ADDD 0,Y
	STD 0,X
	PULA
	TFR A,CCR		; restore CCR
	JMP NEXT0		; proceed to check V flag.

CARRY0:

	STD 0,X			; store top half result in sum.
	TFR CCR,A		; save CCR since C bit is now set.
	PSHA
	BSET 0,SP,#%00000001	; huh. guess I set it forcefully here.
	PULA
	TFR A,CCR
	JMP NEXT0		; now check for V bit.
