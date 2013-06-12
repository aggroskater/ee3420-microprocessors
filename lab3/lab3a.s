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
NEWLINE		DC.B CR,LF,NULL ; newline.
OUTPUT1		DC.B "In ADD32",CR,LF,NULL
CAR1		DC.B "In Carry 1",CR,LF,NULL
CAR0		DC.B "In Carry 0",CR,LF,NULL

	ORG $2000

MAIN:

	LDX #0
	LDD #$FFFF
	STD INT_A,X
	LDD #$0000
	INX
	INX
	STD INT_A,X
	DEX
	DEX
	LDD #$0001
	STD INT_B,X
	LDD #$0000
	INX
	INX
	STD INT_B,X

	JSR ADD32
	RTS

ADD32:

	PUTS_SCI0 #OUTPUT1
	LDX #INT_A
	LDY #INT_B
		
	LDD 2,X
	ADDD 2,Y
	BCS CARRY1
	STD 2,X	
NEXT1:
	LDD 0,X
	ADDD 0,Y
	BCS CARRY0
	STD 0,X	
NEXT0:
	RTS

CARRY1:

	PUTS_SCI0 #CAR1
	STD 2,X
	LDD 0,X
	ADDD #1
	BCS CARRY0
	STD 0,X
	JMP NEXT1

CARRY0:

	PUTS_SCI0 #CAR0
	STD 0,X
	LDAA #%00000001
	TFR A,CCR
	JMP NEXT0
