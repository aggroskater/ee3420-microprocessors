#IFNDEF SPI_IO	;using definition to prevent duplication of equates
SPI_IO_INC EQU 1
#MSG "SPI_IO.INC REVISION 08/06/2010"
#MSG "COPYRIGHT 2010 WILLIAM STAPLETON"
#MSG "THIS FILE MAY BE FREELY DISTRIBUTED AS LONG AS IT REMAINS UNCHANGED AND FULLY CREDITED."

#include ASCII.INC		;definitions for ASCII control characters
#include "MC9S12_registers.inc"

;COMMENT OUT THE FOLLOWING LINE TO INCLUDE THE FULL FILE IN THE LISTING
;	NOLIST

;****************************************************************
;* THE FOLLOWING ARE SIMPLE INPUT AND OUTPUT SUBROUTINES 
;* TARGETED FOR THE Dragon12 BOARDS (MC9S12DP256B)
;****************************************************************

;****************************************************************
;*  SPIx_RW Subroutine
;*  Subroutine exchanges a single byte via SPI
;*  Author: William A. Stapleton
;*  Revision Date: 4/9/2007
;*  Expected data on stack at start of subroutine:
;*			at SP+1:  16-bit return address 
;* 			at SP: return PPAGE
;*  Expected data in accumulator D at start of subroutine:
;*			byte to be output (in B)
;*  Data returned on stack:
;*			none
;*  Data returned in accumulator D:
;*			byte returned by SPI (in B)
;*   			byte that was output (in A)
;*  Required subroutines: NONE
;*  Required libraries: ECE383_Dragon12_registers.inc
;*  Required peripheral hardware: Connection via SPI
;****************************************************************
_SPI0_RW:
	TFR B,A
	BRCLR SPI0SR,SPI_SPTEF,*
	STAB SPI0DR
	BRCLR SPI0SR,SPI_SPTEF,*
	LDAB SPI0DR
	RTC
;SPI0_RW ROUTINE ENDS


;* SOME SYSTEMS HAVE ONLY 1 SPI MODULE
#IFDEF SPI1SR
_SPI1_RW:
	TFR B,A
	BRCLR SPI1SR,SPI_SPTEF,*
	STAB SPI1DR
	BRCLR SPI1SR,SPI_SPTEF,*
	LDAB SPI1DR
	RTC
;SPI1_RW ROUTINE ENDS


#ENDIF

;* SOME SYSTEMS HAVE ONLY 1 SPI MODULE
#IFDEF SPI2SR
_SPI2_RW:
	TFR B,A
	BRCLR SPI2SR,SPI_SPTEF,*
	STAB SPI2DR
	BRCLR SPI2SR,SPI_SPTEF,*
	LDAB SPI2DR
	RTC
;SPI2_RW ROUTINE ENDS


#ENDIF

;****************************************************************
;*  SPI0_SEND_BYTES                                             
;*  subroutine for EXCHANGE of a NULL-TERMINATED STRING from SPI0 
;*  with a maximum character count specified and automatic
;*  null-termination of the resulting string
;*  Author: William A. Stapleton                                
;*  Required subroutines or macros: SPI0_RW
;*  Required peripheral hardware: connection via SCI port  
;*  Expected data on stack at start of subroutine:
;*			at SP+3: 16-bit address of first character of string
;*			at SP+1:  16-bit return address 
;* 			at SP: return PPAGE
;*  Expected data in accumulator D at start of subroutine:
;*			NONE
;*  Data returned on stack:
;*			none
;*  Data returned in accumulator D:
;*			count of characters returned
;*  Other actions:	updates multiple bytes in memory beginning at
;*			specified address and ending with ASCII NULL ($00)
;*  Notes:		waits indefinitely for characters to be input
;****************************************************************

_SPI0_SEND_BYTES:
	PSHD
	PSHX
	PSHY
;*  CURRENT DATA ON STACK:
;*	at SP+9: 	16-bit address of first character of string 
;*	at SP+7:  16-bit return address 
;* 	at SP+6: return PPAGE
;*	at SP+4: 	copy of D 
;*	at SP+2: 	copy of X 
;*	at SP:	 	copy of Y 

	LDX 9,SP		;ADDRESS OF START OF STRING 
SPI0_SEND_A_BYTE:	
	LDAB 0,X
	TFR B,A	
	SPI0_RW
	STAB 1,X+
	TSTA
	BNE SPI0_SEND_A_BYTE
	PULY
	PULX
	PULD
	RTC



;* SOME SYSTEMS HAVE ONLY 1 SPI MODULE
#IFDEF _SPI1_RW
_SPI1_SEND_BYTES:
	PSHD
	PSHX
	PSHY
;*  CURRENT DATA ON STACK:
;*	at SP+9: 	16-bit address of first character of string 
;*	at SP+7:  16-bit return address 
;* 	at SP+6: return PPAGE
;*	at SP+4: 	copy of D 
;*	at SP+2: 	copy of X 
;*	at SP:	 	copy of Y 

	LDX 9,SP		;ADDRESS OF START OF STRING 
SPI1_SEND_A_BYTE:	
	LDAB 0,X
	TFR B,A	
	SPI1_RW
	STAB 1,X+
	TSTA
	BNE SPI1_SEND_A_BYTE
	PULY
	PULX
	PULD
	RTC


#ENDIF

;* SOME SYSTEMS HAVE ONLY 1 SPI MODULE
#IFDEF _SPI2_RW
_SPI2_SEND_BYTES:
	PSHD
	PSHX
	PSHY
;*  CURRENT DATA ON STACK:
;*	at SP+9: 	16-bit address of first character of string 
;*	at SP+7:  16-bit return address 
;* 	at SP+6: return PPAGE
;*	at SP+4: 	copy of D 
;*	at SP+2: 	copy of X 
;*	at SP:	 	copy of Y 

	LDX 9,SP		;ADDRESS OF START OF STRING 
SPI2_SEND_A_BYTE:	
	LDAB 0,X
	TFR B,A	
	SPI2_RW
	STAB 1,X+
	TSTA
	BNE SPI2_SEND_A_BYTE
	PULY
	PULX
	PULD
	RTC


#ENDIF

;THE FOLLOWING LINE RESTORES LISTING FOR CODE OUTSIDE OF THIS LIBRARY
	LIST

#ENDIF			;#IFNDEF SPI_IO