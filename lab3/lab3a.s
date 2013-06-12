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
OUTPUT		DC.B "The sum is %s",CR,LF,NULL

	ORG $2000

MAIN:

	LDX #0
	LDD #$1111
	STD INT_A,X
	LDD #$1111
	INX
	INX
	STD INT_A,X
	DEX
	DEX
	LDD #$2222
	STD INT_B,X
	LDD #$2222
	INX
	INX
	STD INT_B,X

	JSR ADD32
	LDX #0
	LDY INT_A,X
	INX
	INX
	LDD INT_A,X
	RTS

ADD32:

	LDX INT_A
	LDY INT_B
		
	LDD 2,X
	ADDD 2,Y
	BCS CARRY1
	STD 2,X	

	LDD 0,X
	ADDD 0,Y
	BCS CARRY0
	STD 0,X	
	RTS

CARRY1:

	STD 2,X
	LDD 0,X
	ADDD #1
	RTS

CARRY0:

	STD 0,X
	LDAA #%00000001
	TFR A,CCR
	RTS
