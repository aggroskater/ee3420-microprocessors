#IFNDEF LCD_IO	;using definition to prevent duplication of equates
LCD_IO EQU 1
#MSG "LCD_IO.INC REVISION 10/22/2010"
#MSG "COPYRIGHT 2010 WILLIAM STAPLETON"
#MSG "THIS FILE MAY BE FREELY DISTRIBUTED AS LONG AS IT REMAINS UNCHANGED AND FULLY CREDITED."

#INCLUDE ASCII.INC
#INCLUDE SYSTEM_SELECT.INC
#INCLUDE MC9S12_REGISTERS.INC
#INCLUDE DELAY.INC

;COMMENT OUT THE FOLLOWING LINE TO INCLUDE THE FULL FILE IN THE LISTING
;	NOLIST

;Dragon12/DRAGON12-PLUS definitions
;  This sample program uses 4-bit transfer via port K:
;  PK0 ------- RS ( register select, 0 = register transfer, 1 = data transfer).
;  PK1 ------- Enable ( write pulse )
;  PK2 ------- Data Bit 4 of LCD
;  PK3 ------- Data Bit 5 of LCD
;  PK4 ------- Data Bit 6 of LCD
;  PK5 ------- Data Bit 7 of LCD
;  PK7 ------- R/W (ONLY ON DRAGON12-PLUS AND ONLY IF JUMPER-ENABLED

;LCD_USE_RW EQU 1		;INCLUDE THIS LINE TO TRY TO USE LCD_RW ON DRAGON12PLUS OR SIMILARLY EQUIPPED SYSTEMS
#IFDEF LCD_USE_RW
#MSG "LCD_USE_RW SELECTED ACTIVE. PLEASE MAKE CERTAIN THE LCD R/W LINE IS PHYSICALLY ENABLED."
#ENDIF

#IF SYSTEM_BOARD = DRAGON12
LCD_USE_4BIT EQU 1

LCD_DATA_PORT 	EQU PORTK	;ON DRAGON12-PLUS DEFAULT LCD DATA PORT IS PORT K
LCD_DATA_DDR 	EQU DDRK
LCD_DB7		EQU BIT5
LCD_DB6		EQU BIT4
LCD_DB5		EQU BIT3
LCD_DB4		EQU BIT2
LCD_DATA_MASK 	EQU LCD_DB7+LCD_DB6+LCD_DB5+LCD_DB4

LCD_NYBBLE_OFFSET EQU 2		;4 BIT BUS IS OFFSET 2 PLACES TO LEFT  (LSB IS BIT 2)

LCD_E_PORT	EQU PORTK
LCD_E_DDR	EQU DDRK
LCD_E		EQU BIT1

LCD_RS_PORT	EQU PORTK
LCD_RS_DDR	EQU DDRK
LCD_RS		EQU BIT0

LCD_RW_PORT	EQU NULL
LCD_RW_DDR	EQU NULL
LCD_RW		EQU NULL

#ENDIF	;DRAGON12

#IF SYSTEM_BOARD = DRAGON12PLUS
LCD_USE_4BIT EQU 1		;ON DRAGON12PLUS LCD BUS IS 4 BITS

LCD_DATA_PORT 	EQU PORTK	;ON DRAGON12-PLUS DEFAULT LCD DATA PORT IS PORT K
LCD_DATA_DDR 	EQU DDRK
LCD_DB7		EQU BIT5 
LCD_DB6		EQU BIT4
LCD_DB5		EQU BIT3	
LCD_DB4		EQU BIT2
LCD_DATA_MASK 	EQU LCD_DB7+LCD_DB6+LCD_DB5+LCD_DB4

LCD_NYBBLE_OFFSET EQU 2		;4 BIT BUS IS OFFSET 2 PLACES TO LEFT  (LSB IS BIT 2)

LCD_E_PORT	EQU PORTK
LCD_E_DDR	EQU DDRK
LCD_E		EQU BIT1

LCD_RS_PORT	EQU PORTK
LCD_RS_DDR	EQU DDRK
LCD_RS		EQU BIT0

#IFDEF LCD_USE_RW
LCD_RW_PORT	EQU PORTK	
LCD_RW_DDR	EQU DDRK
LCD_RW		EQU BIT7
#ENDIF
#IFNDEF LCD_USE_RW
LCD_RW_PORT	EQU NULL
LCD_RW_DDR	EQU NULL
LCD_RW		EQU NULL
#ENDIF

#ENDIF	;DRAGON12PLUS

#IF SYSTEM_BOARD = SPIDER12

LCD_USE_4BIT EQU 1

LCD_DATA_PORT 	EQU PORTK	;ON DRAGON12-PLUS DEFAULT LCD DATA PORT IS PORT K
LCD_DATA_DDR 	EQU DDRK
LCD_DB7		EQU BIT5
LCD_DB6		EQU BIT4
LCD_DB5		EQU BIT3
LCD_DB4		EQU BIT2
LCD_DATA_MASK 	EQU LCD_DB7+LCD_DB6+LCD_DB5+LCD_DB4

LCD_NYBBLE_OFFSET EQU 2		;4 BIT BUS IS OFFSET 2 PLACES TO LEFT  (LSB IS BIT 2)

LCD_E_PORT	EQU PORTK
LCD_E_DDR	EQU DDRK
LCD_E		EQU BIT1

LCD_RS_PORT	EQU PORTK
LCD_RS_DDR	EQU DDRK
LCD_RS		EQU BIT0

LCD_RW_PORT	EQU NULL
LCD_RW_DDR	EQU NULL
LCD_RW		EQU NULL

#ENDIF	

#IF SYSTEM_BOARD = MINIDRAGON | SYSTEM_BOARD = MINIDRAGONPLUS
LCD_USE_4BIT EQU 1

LCD_DATA_PORT 	EQU PORTK	;ON DRAGON12-PLUS DEFAULT LCD DATA PORT IS PORT K
LCD_DATA_DDR 	EQU DDRK
LCD_DB7		EQU BIT5
LCD_DB6		EQU BIT4
LCD_DB5		EQU BIT3
LCD_DB4		EQU BIT2
LCD_DATA_MASK 	EQU LCD_DB7+LCD_DB6+LCD_DB5+LCD_DB4

LCD_NYBBLE_OFFSET EQU 2		;4 BIT BUS IS OFFSET 2 PLACES TO LEFT  (LSB IS BIT 2)

LCD_E_PORT	EQU PORTK
LCD_E_DDR	EQU DDRK
LCD_E		EQU BIT1

LCD_RS_PORT	EQU PORTK
LCD_RS_DDR	EQU DDRK
LCD_RS		EQU BIT0

LCD_RW_PORT	EQU NULL
LCD_RW_DDR	EQU NULL
LCD_RW		EQU NULL

#ENDIF	

#IF SYSTEM_BOARD = DRAGONFLYBOT

LCD_USE_4BIT EQU 1

;IMPORTANT NOTE FOR DRAGONFLYBOT:
;ON THE DRAGONFLYBOT LCD_DB7 IS JUMPER SELECTABLE BETWEEN PORTM, BIT5 AND PORTP, BIT5
;ALL OF THE ROUTINES IN THIS LIBRARY ASSUME THAT THE DATA BUS BITS ARE CONTIGUOUS WITHIN A SINGLE PORT
;THIS ROUTINE CANNOT BE USED WITH THE LCD DATA BUS SPLIT ACROSS TWO PORTS AS IT IS WRITTEN.
#MSG "BE CERTAIN LCD_DB7 JUMPER IS SET TO PORT M PIN 5 AND NOT PORT P ON DRAGONFLYBOT"

LCD_DATA_PORT 	EQU PORTM	
LCD_DATA_DDR 	EQU DDRM

LCD_DB7		EQU BIT5
LCD_DB6		EQU BIT4
LCD_DB5		EQU BIT3
LCD_DB4		EQU BIT2
LCD_DATA_MASK 	EQU LCD_DB7+LCD_DB6+LCD_DB5+LCD_DB4

LCD_NYBBLE_OFFSET EQU 2		;4 BIT BUS IS OFFSET 2 PLACES TO LEFT  (LSB IS BIT 2)

LCD_E_PORT	EQU PORTE
LCD_E_DDR	EQU DDRE
LCD_E		EQU BIT7

LCD_RS_PORT	EQU PORTA
LCD_RS_DDR	EQU DDRA
LCD_RS		EQU BIT0

LCD_RW_PORT	EQU NULL
LCD_RW_DDR	EQU NULL
LCD_RW		EQU NULL

#ENDIF	;DRAGONFLYBOT

#IF SYSTEM_BOARD = DXUPCLOSE1

;;LCD_USE_4BIT EQU 1

LCD_DATA_PORT 	EQU PORTT	
LCD_DATA_DDR 	EQU DDRT

LCD_DB7		EQU BIT7
LCD_DB6		EQU BIT6
LCD_DB5		EQU BIT5
LCD_DB4		EQU BIT4
LCD_DB3		EQU BIT3
LCD_DB2		EQU BIT2
LCD_DB1		EQU BIT1
LCD_DB0		EQU BIT0
LCD_DATA_MASK 	EQU LCD_DB7+LCD_DB6+LCD_DB5+LCD_DB4

LCD_NYBBLE_OFFSET EQU 0		

LCD_E_PORT	EQU PORTM
LCD_E_DDR	EQU DDRM
LCD_E		EQU BIT1

LCD_RS_PORT	EQU PORTM
LCD_RS_DDR	EQU DDRM
LCD_RS		EQU BIT0

LCD_RW_PORT	EQU NULL
LCD_RW_DDR	EQU NULL
LCD_RW		EQU NULL

#ENDIF	;DXUPCLOSE1

#IF SYSTEM_BOARD = BATTERYMONITOR
LCD_USE_4BIT EQU 1

LCD_DATA_PORT 	EQU PORTM	;ON DRAGON12-PLUS DEFAULT LCD DATA PORT IS PORT K
LCD_DATA_DDR 	EQU DDRM
LCD_DB7		EQU BIT5
LCD_DB6		EQU BIT4
LCD_DB5		EQU BIT3
LCD_DB4		EQU BIT2
LCD_DATA_MASK 	EQU LCD_DB7+LCD_DB6+LCD_DB5+LCD_DB4

LCD_NYBBLE_OFFSET EQU 2		;4 BIT BUS IS OFFSET 2 PLACES TO LEFT  (LSB IS BIT 2)

LCD_E_PORT	EQU PORTM
LCD_E_DDR	EQU DDRM
LCD_E		EQU BIT0

LCD_RS_PORT	EQU PORTM
LCD_RS_DDR	EQU DDRM
LCD_RS		EQU BIT1

LCD_RW_PORT	EQU NULL
LCD_RW_DDR	EQU NULL
LCD_RW		EQU NULL

#ENDIF	


#IFNDEF LCD_DATA_PORT
#MSG "SELECTED SYSTEM DOES NOT HAVE A DEFINED LCD PORT."
#MSG "UNABLE TO INITIALIZE LCD CODE DUE TO UNKNOWN LCD INTERFACE CONFIGURATION."
LCD_DATA_PORT EQU NULL
#ENDIF

#IFDEF LCD_DATA_PORT 

LCD_ADDRESS_PREFIX EQU $80

;****************************************************************
;*  LCD_WRITE_CMD_NYBBLE Subroutine
;*  Author: William A. Stapleton
;*  Revision Date: 08/06/2010
;*  Input parameters required on stack: NONE
;*  INPUT PARAMETERS IN D: BYTE TO BE OUTPUT IN B
;*  Data generated: NONE
;*  Other actions: OUTPUTS COMMAND BYTE TO LCD PANEL
;*  Required peripheral hardware: LCD PANEL 
;****************************************************************

_LCD_WRITE_CMD_NYBBLE:	;EXPECTS DATA IN ACCUMULATOR B (LOW 4 BITS)
	PSHD
	BCLR LCD_RS_PORT,LCD_RS	;FORCE COMMAND MODE
	BCLR LCD_E_PORT,LCD_E	;MAKE CERTAIN CLOCK IS OFF
#IFDEF LCD_USE_RW
	BCLR LCD_RW_PORT,LCD_RW ;FORCE WRITE
#ENDIF

	LDAA #LCD_NYBBLE_OFFSET
	TBEQ A,LCD_CMD_NYBBLE_OUTPUT
	
LCD_CMD_NYBBLE_OFFSET:
	LSLB
	DBNE A,LCD_CMD_NYBBLE_OFFSET 

LCD_CMD_NYBBLE_OUTPUT:
	ANDB #LCD_DATA_MASK	;FORCE ONLY 4 BITS ACTIVE
	BCLR LCD_DATA_PORT,LCD_DATA_MASK ;CLEAR OLD DATA
	ADDB LCD_DATA_PORT	;COMBINE DATA WITH ANY OTHER PORT BITS
	STAB LCD_DATA_PORT	;WRITE RESULT BACK TO PORT

	BCLR LCD_RS_PORT,LCD_RS	;FORCE COMMAND MODE
	CALL _LCD_PULSE_CLOCK,LIBRARY_PAGE
	PULD
	RTC

;****************************************************************
;*  LCD_WRITE_DATA_NYBBLE Subroutine
;*  Author: William A. Stapleton
;*  Revision Date: 08/06/2010
;*  Input parameters required on stack: NONE
;*  INPUT PARAMETERS IN D: BYTE TO BE OUTPUT IN B
;*  Data generated: NONE
;*  Other actions: OUTPUTS DATA BYTE TO LCD PANEL
;*  Required peripheral hardware: LCD PANEL 
;****************************************************************

_LCD_WRITE_DATA_NYBBLE:	;EXPECTS DATA IN ACCUMULATOR B (LOW 4 BITS)
	PSHD
	BSET LCD_RS_PORT,LCD_RS	;FORCE DATA MODE
	BCLR LCD_E_PORT,LCD_E	;MAKE CERTAIN CLOCK IS OFF
#IFDEF LCD_USE_RW
	BCLR LCD_RW_PORT,LCD_RW ;FORCE WRITE
#ENDIF

	LDAA #LCD_NYBBLE_OFFSET
	TBEQ A,LCD_DATA_NYBBLE_OUTPUT
	
LCD_DATA_NYBBLE_OFFSET:
	LSLB
	DBNE A,LCD_DATA_NYBBLE_OFFSET 

LCD_DATA_NYBBLE_OUTPUT:
	ANDB #LCD_DATA_MASK	;FORCE ONLY 4 BITS ACTIVE
	BCLR LCD_DATA_PORT,LCD_DATA_MASK ;CLEAR OLD DATA
	ADDB LCD_DATA_PORT	;COMBINE DATA WITH ANY OTHER PORT BITS
	STAB LCD_DATA_PORT	;WRITE RESULT BACK TO PORT

	BSET LCD_RS_PORT,LCD_RS	;FORCE DATA MODE
	CALL _LCD_PULSE_CLOCK,LIBRARY_PAGE
	PULD
	RTC
	

;****************************************************************
;*  LCD_WRITE_DATA_BYTE Subroutine
;*  Author: William A. Stapleton
;*  Revision Date: 08/06/2010
;*  Input parameters required on stack: NONE
;*  INPUT PARAMETERS IN D: BYTE TO BE OUTPUT IN B
;*  Data generated: NONE
;*  Other actions: OUTPUTS DATA BYTE TO LCD PANEL
;*  Required peripheral hardware: LCD PANEL 
;****************************************************************
_LCD_WRITE_DATA_BYTE:	;ASSUMES BYTE IS IN ACCUMULATOR B
	PSHD
	BSET LCD_RS_PORT,LCD_RS	;FORCE DATA MODE
#IFDEF LCD_USE_RW
	BCLR LCD_RW_PORT,LCD_RW ;FORCE WRITE
#ENDIF
#IFDEF LCD_USE_4BIT
	PSHB
	LSRB
	LSRB
	LSRB
	LSRB
	CALL _LCD_WRITE_DATA_NYBBLE,LIBRARY_PAGE
	DELAY_BY_US #50
	PULB
	CALL _LCD_WRITE_DATA_NYBBLE,LIBRARY_PAGE
#ENDIF
#IFDEF LCD_USE_8BIT	
	STAB LCD_DATA_PORT
	CALL _LCD_PULSE_CLOCK,LIBRARY_PAGE
#ENDIF	
	PULD
	RTC

;****************************************************************
;*  LCD_WRITE_CMD_BYTE Subroutine
;*  Author: William A. Stapleton
;*  Revision Date: 08/06/2010
;*  Input parameters required on stack: NONE
;*  INPUT PARAMETERS IN D: BYTE TO BE OUTPUT IN B
;*  Data generated: NONE
;*  Other actions: OUTPUTS COMMAND BYTE TO LCD PANEL
;*  Required peripheral hardware: LCD PANEL 
;****************************************************************

_LCD_WRITE_CMD_BYTE:	;ASSUMES BYTE IS IN ACCUMULATOR B
	PSHD
	BCLR LCD_RS_PORT,LCD_RS	;FORCE COMMAND MODE
#IFDEF LCD_USE_RW
	BCLR LCD_RW_PORT,LCD_RW ;FORCE WRITE
#ENDIF
#IFDEF LCD_USE_4BIT
	PSHB
	LSRB
	LSRB
	LSRB
	LSRB
	CALL _LCD_WRITE_CMD_NYBBLE,LIBRARY_PAGE
	DELAY_BY_US #50
	PULB
	CALL _LCD_WRITE_CMD_NYBBLE,LIBRARY_PAGE
#ENDIF
#IFDEF LCD_USE_8BIT	
	STAB LCD_DATA_PORT
	CALL _LCD_PULSE_CLOCK,LIBRARY_PAGE
#ENDIF	
	PULD
	RTC


;****************************************************************
;*  LCD_SETUP Subroutine
;*  SENDS SEQUENCE OF COMMANDS TO LCD PANEL VIA SPI0
;*  TO INITIALIZE PANEL INTO KNOWN STARTING STATE
;*  Author: William A. Stapleton
;*  Revision Date: 09/25/2006
;*  Input parameters required on stack: NONE
;*  Data generated: NONE
;*  Other actions: INITIALIZES LCD PANEL
;*  Required subroutines: LCD_PULSE_CLOCK, DELAY
;*  Required libraries: NONE
;*  Required peripheral hardware: LCD PANEL ON DRAGON12
;****************************************************************
_LCD_SETUP: PSHD
	PSHX
	PSHY

	BSET LCD_DATA_DDR,LCD_DATA_MASK	
	BCLR LCD_DATA_PORT,LCD_DATA_MASK
	BSET LCD_E_DDR,LCD_E
	BCLR LCD_E_PORT,LCD_E
	BSET LCD_RS_DDR,LCD_RS
	BCLR LCD_RS_PORT,LCD_RS
#IFDEF LCD_USE_RW	
	BSET LCD_RW_DDR,LCD_RW
	BCLR LCD_RW_PORT,LCD_RW
#ENDIF

	DELAY_BY_MS	#100
;	JSR DELAY_5MS	;5ms		;LCD STARTUP PROTOCOL REQUIRES MINIMUM 20MS AFTER POWER-ON;
;	JSR DELAY_5MS	;5ms
;	JSR DELAY_5MS	;5ms
;	JSR DELAY_5MS	;5ms

	LDAB #%0011			;LCD INITIALIZATION COMMAND (MUST BE REPEATED 3 TIMES)
	CALL _LCD_WRITE_CMD_NYBBLE,LIBRARY_PAGE
	DELAY_BY_MS #50

	LDAB #%0011			;REPEAT LCD INITIALIZATION COMMAND
	CALL _LCD_WRITE_CMD_NYBBLE,LIBRARY_PAGE
	DELAY_BY_MS #50

	LDAB #%0011			;REPEAT LCD INITIALIZATION COMMAND
	CALL _LCD_WRITE_CMD_NYBBLE,LIBRARY_PAGE
	DELAY_BY_MS #50

#IFDEF LCD_USE_4BIT	

	LDAB #%0010			;SET 4-BIT MODE
	CALL _LCD_WRITE_CMD_NYBBLE,LIBRARY_PAGE
	DELAY_BY_US #500

	LDAB #%00101000			;REITERATE 4-BIT, USE BOTH DISPLAY LINES, USE STANDARD SIZE TEXT
	CALL _LCD_WRITE_CMD_BYTE,LIBRARY_PAGE
	DELAY_BY_US #500

#ENDIF

#IFDEF LCD_USE_8BIT

	LDAB #%0011			;SET 8-BIT MODE
	CALL _LCD_WRITE_CMD_NYBBLE,LIBRARY_PAGE
	DELAY_BY_US #500

	LDAB #%00111000			;REITERATE 8-BIT, USE BOTH DISPLAY LINES, USE STANDARD SIZE TEXT
	CALL _LCD_WRITE_CMD_BYTE,LIBRARY_PAGE
	DELAY_BY_US #500
#ENDIF

	LDAB #%00001111			;TURN DISPLAY ON, TURN CURSOR ON, CURSOR BLINKS
	CALL _LCD_WRITE_CMD_BYTE,LIBRARY_PAGE
	DELAY_BY_US #500

	LDAB #%00000001			;CLEAR DISPLAY, HOME CURSOR
	CALL _LCD_WRITE_CMD_BYTE,LIBRARY_PAGE
	DELAY_BY_MS #50

	LDAB #%00000110			;CURSOR MOVES AND AUTO-INCREMENTS (MOVES RIGHT)
	CALL _LCD_WRITE_CMD_BYTE,LIBRARY_PAGE
	DELAY_BY_US #500

	LDAB #%00010000			;PREFERENCE IS CURSOR MOVE, SHIFTS ARE TO RIGHT
	CALL _LCD_WRITE_CMD_BYTE,LIBRARY_PAGE
	DELAY_BY_US #500

	PULY
	PULX
	PULD
	RTC

;****************************************************************
;*  LCD_PULSE_CLOCK Subroutine
;*  PULSES LCD-E
;*  Author: William A. Stapleton
;*  Revision Date: 09/26/2005
;*  Input parameters required on stack: NONE
;*  Data generated: NONE
;*  Other actions: PULSES LCD_E IF CONNECTED AS SHOWN IN COMMENTS ABOVE
;*  Required subroutines: DELAY_50US
;*  Required libraries: NONE
;*  Required peripheral hardware: LCD PANEL ON DRAGON12
;****************************************************************

_LCD_PULSE_CLOCK:
	DELAY_BY_US #50
	BSET LCD_E_PORT,LCD_E	;PULSE LCD CLOCK (LCD_E)
	DELAY_BY_US #50
	BCLR LCD_E_PORT,LCD_E
	DELAY_BY_US #50
	RTC

_PUTC_LCD:
	LBRA _LCD_WRITE_DATA_BYTE

_PUTC_LCD_COMMAND
	LBRA _LCD_WRITE_CMD_BYTE

;****************************************************************
;*  PUTS_LCD                                            
;*  subroutine for output of a null-terminated character string to LCD
;*  Author: William A. Stapleton                                
;*  Required subroutines or macros: PUTC_LCD
;*  Required peripheral hardware: connection via serial I/O port  
;*  Expected data on stack at start of subroutine:
;*			AT SP+3: address of first character in null-terminated string
;*			at SP+1: 16-bit return address 
;*			AT sp: RETURN ppage
;*  Expected data in accumulator D at start of subroutine:
;*			NONE
;*  Data returned on stack:
;*			none
;*  Data returned in accumulator D:
;*			none
;*  Other actions:	outputs multiple bytes from memory beginning at
;*			specified address and ending with ASCII NULL ($00)
;*  Notes:		no pre-defined string length limit
;****************************************************************

_PUTS_LCD: 
	PSHX		;SAVE ORIGINAL X ON STACK
	PSHY		;SAVE ORIGINAL Y
	PSHD		;SAVE ORIGINAL D
;*  CURRENT DATA ON STACK:
;*	at SP+9: 	16-bit address of first character of string 
;*	at SP+7: 	16-bit return address 
;*	at SP+6:	return PPAGE
;*	at SP+4: 	copy of X 
;*	at SP+2: 	copy of Y 
;*	at SP:	 	copy of D 
	
	LDX 9,SP		;ADDRESS OF STRING INTO X
PUTS_LCD_TOP:
	LDAB 1,X+
	CMPB #NULL
	BEQ PUTS_LCD_END_OF_STRING
	PUTC_LCD
	BRA PUTS_LCD_TOP
	
PUTS_LCD_END_OF_STRING:
	PULD
	PULY
	PULX
	RTC		;RETURN TO CALLING PROGRAM

#ENDIF ;LCD_DATA_PORT != NULL


;THE FOLLOWING LINE RESTORES LISTING FOR CODE OUTSIDE OF THIS LIBRARY
	LIST

#ENDIF 	;LCD_IO	;using definition to prevent duplication of equates




