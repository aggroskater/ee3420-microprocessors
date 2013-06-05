#IFNDEF SCI_IO	;using definition to prevent duplication of equates
SCI_IO EQU 1
#MSG "SCI_IO.INC REVISION 01/27/2012"
#MSG "COPYRIGHT 2012 WILLIAM STAPLETON"
#MSG "THIS FILE MAY BE FREELY DISTRIBUTED AS LONG AS IT REMAINS UNCHANGED AND FULLY CREDITED."

#include "mc9s12_registers.inc"
#include ASCII.INC		;definitions for ASCII control characters

;COMMENT OUT THE FOLLOWING LINE TO INCLUDE THE FULL FILE IN THE LISTING
;	NOLIST

;****************************************************************
;*  SCI_IO.INC                                             
;*  Include file including several subroutines for text-based
;*  input and output.  
;*  These routines are similar to the C functions 
;*  getc(), putc(), gets(), puts()
;*  Conditional assembly requires ASM12 assembler (MiniIDE)
;*  Author: William A. Stapleton                                
;*  Start program with: N/A                                     
;*  Required libraries: ASCII.INC, Dragon12_registers.inc                                 
;*  Required peripheral hardware: connection to terminal via serial I/O ports
;*				connection via SCI0, SCI1, SPI0, SPI1, or SPI2 to
;*				any text-based terminal-like device 	
;*  Special instructions: Should be included AFTER the RTS of the main program
;****************************************************************


INPUT_ECHO EQU 1


;****************************************************************
;* THE FOLLOWING ARE SIMPLE INPUT AND OUTPUT SUBROUTINES 
;* TARGETED FOR THE Dragon12 BOARDS (MC9S12DP256B)
;****************************************************************

;****************************************************************
;*  GETC_xxxx                                             
;*  subroutines for input of a single character from serial port 
;*  Author: William A. Stapleton                                
;*  Required libraries: ASCII.INC, Dragon12_registers.inc                                  
;*  Required peripheral hardware: connection via serial I/O port  
;*  Expected data on stack at start of subroutine:
;*			at SP+1: 16-bit return address 
;*			at SP: return PPAGE
;*  Expected data in accumulator D at start of subroutine:
;*			none
;*  Data returned on stack:
;*			none
;*  Data returned in accumulator D:
;*  			ASCII code input (8 bits in B)
;*  Notes:		waits indefinitely for character to be input
;****************************************************************
;* consists of GETC_SCI0, GETC_SCI1,
;****************************************************************

_GETC_SCI0:

	BRCLR SCI0SR1,SCI_RDRF,*  	;WAIT WHILE RDRF=0
	LDAB SCI0DRL		;READ CHARACTER FROM SCI
#IFDEF INPUT_ECHO
	PUTC_SCI0
#ENDIF	
	RTC		;RETURN TO CALLING PROGRAM


;GETC_SCI0 ROUTINE ENDS


;* SOME SYSTEMS HAVE ONLY 1 SCI PORT
#IFDEF SCI1SR1
_GETC_SCI1:

	BRCLR SCI1SR1,SCI_RDRF,*  	;WAIT WHILE RDRF=0
	LDAB SCI1DRL		;READ CHARACTER FROM SCI
#IFDEF INPUT_ECHO
	PUTC_SCI1
#ENDIF	
	RTC		;RETURN TO CALLING PROGRAM


#ENDIF  ;SCI1SR1

;GETC_SCI1 ROUTINE ENDS

_GETC_SCI0_NOECHO:

	BRCLR SCI0SR1,SCI_RDRF,*  	;WAIT WHILE RDRF=0
	LDAB SCI0DRL		;READ CHARACTER FROM SCI
	RTC		;RETURN TO CALLING PROGRAM


;GETC_SCI0 ROUTINE ENDS


;* SOME SYSTEMS HAVE ONLY 1 SCI PORT
#IFDEF SCI1SR1
_GETC_SCI1_NOECHO:

	BRCLR SCI1SR1,SCI_RDRF,*  	;WAIT WHILE RDRF=0
	LDAB SCI1DRL		;READ CHARACTER FROM SCI
	RTC		;RETURN TO CALLING PROGRAM


#ENDIF  ;SCI1SR1

;GETC_SCI1 ROUTINE ENDS


;****************************************************************
;*  GETS_SCI0                                             
;*  subroutine for input of a character STRING from SCI0 
;*  with a maximum character count specified and automatic
;*  null-termination of the resulting string
;*  Author: William A. Stapleton                                
;*  Required subroutines or macros: GETC_SCI0
;*  Required peripheral hardware: connection via SCI port  
;*  Expected data on stack at start of subroutine:
;*			at SP+3: 16-bit address of first character of string
;*			at SP+1: 16-bit return address 
;*                      at SP: return PPAGE
;*  Expected data in accumulator D at start of subroutine:
;*			NONE
;*  Data returned on stack:
;*			none
;*  Data returned in accumulator D:
;*			count of characters returned
;*  Other actions:	updates multiple bytes in memory beginning at
;*			specified address and ending with ASCII NULL ($00)
;*			input continues until ASCII CR ($0D) is received.
;*  Notes:		waits indefinitely for characters to be input
;****************************************************************
_GETS_SCI0:
	PSHX		;SAVE ORIGINAL X ON STACK
	PSHY		;SAVE ORIGINAL Y
;*  CURRENT DATA ON STACK:
;*	at SP+7: 	16-bit address of first character of string 
;*	at SP+5: 	16-bit return address 
;*      at SP+4: 	return PPAGE
;*	at SP+2: 	copy of X 
;*	at SP:	 	copy of Y 

	LDY 7,SP	;COPY STRING ADDRESS TO Y
	LDX #0 		;X IS CHARACTER COUNT
	
GETS_SCI0_TOP:
	GETC_SCI0	;GET A CHARACTER INTO B
	CMPB #CR	;IS IT CARRIAGE RETURN?
	BEQ GETS_SCI0_DONE
	STAB 1,Y+
	INX
	BRA GETS_SCI0_TOP	;GET NEXT CHARACTER
	
GETS_SCI0_DONE:	
	MOVB #NULL, 0,Y	;NULL-TERMINATE THE STRING
	TFR X,D		;PUT COUNT INTO D
	PULY		;RESTORE ORIGINAL Y
	PULX 		;RESTORE ORIGINAL X
	RTC		;RETURN TO CALLING PROGRAM


;GETS_SCI0 ROUTINE ENDS
;THE CALLING PROGRAM SHOULD CLEAN THE STACK OF ALL PUSHED DATA

;* SOME SYSTEMS HAVE ONLY 1 SCI PORT
#IFDEF _GETC_SCI1
_GETS_SCI1:
	PSHX		;SAVE ORIGINAL X ON STACK
	PSHY		;SAVE ORIGINAL Y
;*  CURRENT DATA ON STACK:
;*	at SP+7: 	16-bit address of first character of string 
;*	at SP+5: 	16-bit return address 
;*      at SP+4: 	return PPAGE
;*	at SP+2: 	copy of X 
;*	at SP:	 	copy of Y 

	LDY 7,SP	;COPY STRING ADDRESS TO Y
	LDX #0 		;X IS CHARACTER COUNT
	
GETS_SCI1_TOP:
	GETC_SCI1	;GET A CHARACTER INTO B
	CMPB #CR	;IS IT CARRIAGE RETURN?
	BEQ GETS_SCI1_DONE
	STAB 1,Y+
	INX
	BRA GETS_SCI1_TOP	;GET NEXT CHARACTER
	
GETS_SCI1_DONE:	
	MOVB #NULL, 0,Y	;NULL-TERMINATE THE STRING
	TFR X,D		;PUT COUNT INTO D
	PULY		;RESTORE ORIGINAL Y
	PULX 		;RESTORE ORIGINAL X
	RTC		;RETURN TO CALLING PROGRAM

;GETS_SCI1 ROUTINE ENDS
;THE CALLING PROGRAM SHOULD CLEAN THE STACK OF ALL PUSHED DATA
#ENDIF

_GETS_SCI0_NOECHO:
	PSHX		;SAVE ORIGINAL X ON STACK
	PSHY		;SAVE ORIGINAL Y
;*  CURRENT DATA ON STACK:
;*	at SP+7: 	16-bit address of first character of string 
;*	at SP+5: 	16-bit return address 
;*      at SP+4: 	return PPAGE
;*	at SP+2: 	copy of X 
;*	at SP:	 	copy of Y 

	LDY 7,SP	;COPY STRING ADDRESS TO Y
	LDX #0 		;X IS CHARACTER COUNT
	
GETS_SCI0_NOECHO_TOP:
	GETC_SCI0_NOECHO	;GET A CHARACTER INTO B
	CMPB #CR	;IS IT CARRIAGE RETURN?
	BEQ GETS_SCI0_NOECHO_DONE
	STAB 1,Y+
	INX
	BRA GETS_SCI0_NOECHO_TOP	;GET NEXT CHARACTER
	
GETS_SCI0_NOECHO_DONE:	
	MOVB #NULL, 0,Y	;NULL-TERMINATE THE STRING
	TFR X,D		;PUT COUNT INTO D
	PULY		;RESTORE ORIGINAL Y
	PULX 		;RESTORE ORIGINAL X
	RTC		;RETURN TO CALLING PROGRAM


;GETS_SCI0 ROUTINE ENDS
;THE CALLING PROGRAM SHOULD CLEAN THE STACK OF ALL PUSHED DATA

;* SOME SYSTEMS HAVE ONLY 1 SCI PORT
#IFDEF _GETC_SCI1_NOECHO
_GETS_SCI1_NOECHO:
	PSHX		;SAVE ORIGINAL X ON STACK
	PSHY		;SAVE ORIGINAL Y
;*  CURRENT DATA ON STACK:
;*	at SP+7: 	16-bit address of first character of string 
;*	at SP+5: 	16-bit return address 
;*      at SP+4: 	return PPAGE
;*	at SP+2: 	copy of X 
;*	at SP:	 	copy of Y 

	LDY 7,SP	;COPY STRING ADDRESS TO Y
	LDX #0 		;X IS CHARACTER COUNT
	
GETS_SCI1_NOECHO_TOP:
	GETC_SCI1_NOECHO	;GET A CHARACTER INTO B
	CMPB #CR	;IS IT CARRIAGE RETURN?
	BEQ GETS_SCI1_NOECHO_DONE
	STAB 1,Y+
	INX
	BRA GETS_SCI1_NOECHO_TOP	;GET NEXT CHARACTER
	
GETS_SCI1_NOECHO_DONE:	
	MOVB #NULL, 0,Y	;NULL-TERMINATE THE STRING
	TFR X,D		;PUT COUNT INTO D
	PULY		;RESTORE ORIGINAL Y
	PULX 		;RESTORE ORIGINAL X
	RTC		;RETURN TO CALLING PROGRAM

;GETS_SCI1 ROUTINE ENDS
;THE CALLING PROGRAM SHOULD CLEAN THE STACK OF ALL PUSHED DATA
#ENDIF

;****************************************************************
;*  PUTC_xxxx                                            
;*  subroutine for output a single character to serial I/O port  
;*  Author: William A. Stapleton                                
;*  Required libraries: DP256REG.INC                                  
;*  Required peripheral hardware: connection via serial I/O port  
;*  Expected data on stack at start of subroutine:
;*			at SP+1: 16-bit return address 
;*			at SP: return PPAGE
;*  Expected data in accumulator D at start of subroutine:
;*			character to be output (in B)
;*  Data returned on stack:
;*			none
;*  Data returned in accumulator D:
;*			none
;*  Other actions:	writes one character to serial I/O port
;*  Notes:		waits for  port availablity
;****************************************************************
_PUTC_SCI0: 
	BRCLR SCI0SR1,SCI_TDRE,*  	;WAIT WHILE TDRE=0
	STAB SCI0DRL	;WRITE CHARACTER TO SCI 
	RTC		;RETURN TO CALLING PROGRAM
;PUTC_SCI0 ROUTINE ENDS


;* SOME SYSTEMS HAVE ONLY 1 SCI PORT
#IFDEF SCI1SR1
_PUTC_SCI1: 
	BRCLR SCI1SR1,SCI_TDRE,*  	;WAIT WHILE TDRE=0
	STAB SCI1DRL	;WRITE CHARACTER TO SCI 
	RTC		;RETURN TO CALLING PROGRAM
;PUTC_SCI1 ROUTINE ENDS
;* SOME SYSTEMS HAVE ONLY 1 SCI PORT


#ENDIF ;SCI1SR1


;****************************************************************
;*  PUTS_xxxx                                             
;*  subroutine for output of a null-terminated character string to serial I/O port
;*  Author: William A. Stapleton                                
;*  Required subroutines or macros: PUTC_xxxx
;*  Required peripheral hardware: connection via serial I/O port  
;*  Expected data on stack at start of subroutine:
;*			AT SP+3: address of first character in null-terminated string
;*			at SP+1: 16-bit return address 
;*			at SP: return PPAGE
;*  Expected data in accumulator D at start of subroutine:
;*			none
;*  Data returned in accumulator D:
;*			none
;*  Other actions:	outputs multiple bytes from memory beginning at
;*			specified address and ending with ASCII NULL ($00)
;*  Notes:		no pre-defined string length limit
;****************************************************************
_PUTS_SCI0: 
	PSHX		;SAVE ORIGINAL X ON STACK
	PSHY		;SAVE ORIGINAL Y
	PSHD		;SAVE ORIGINAL D
;*  CURRENT DATA ON STACK:
;*	at SP+9: 	16-bit address of first character of string 
;*	at SP+7: 	16-bit return address 
;*      at SP+6: 	return PPAGE
;*	at SP+4: 	copy of X 
;*	at SP+2: 	copy of Y 
;*	at SP:	 	copy of D 

	LDX 9,SP		;ADDRESS OF STRING INTO X
PUTS_SCI0_TOP:
	LDAB 1,X+
	CMPB #NULL
	BEQ PUTS_SCI0_END_OF_STRING
	PUTC_SCI0
	BRA PUTS_SCI0_TOP
	
PUTS_SCI0_END_OF_STRING:
	PULD
	PULY
	PULX
	RTC		;RETURN TO CALLING PROGRAM

;PUTS_SCI0 ROUTINE ENDS
;THE CALLING PROGRAM SHOULD CLEAN THE STACK OF ALL PUSHED DATA


;* SOME SYSTEMS HAVE ONLY 1 SCI PORT
#IFDEF _PUTC_SCI1
_PUTS_SCI1: 
	PSHX		;SAVE ORIGINAL X ON STACK
	PSHY		;SAVE ORIGINAL Y
	PSHD		;SAVE ORIGINAL D
;*  CURRENT DATA ON STACK:
;*	at SP+9: 	16-bit address of first character of string 
;*	at SP+7: 	16-bit return address 
;*      at SP+6: 	return PPAGE
;*	at SP+4: 	copy of X 
;*	at SP+2: 	copy of Y 
;*	at SP:	 	copy of D 

	LDX 9,SP		;ADDRESS OF STRING INTO X
PUTS_SCI1_TOP:
	LDAB 1,X+
	CMPB #NULL
	BEQ PUTS_SCI1_END_OF_STRING
	PUTC_SCI1
	BRA PUTS_SCI1_TOP
	
PUTS_SCI1_END_OF_STRING:
	PULD
	PULY
	PULX
	RTC		;RETURN TO CALLING PROGRAM
#ENDIF

;* SOME SYSTEMS HAVE ONLY 1 SCI PORT
#IFDEF _PUTC_SCI1
_PUTS_SCI_BOTH: 
	PSHX		;SAVE ORIGINAL X ON STACK
	PSHY		;SAVE ORIGINAL Y
	PSHD		;SAVE ORIGINAL D
;*  CURRENT DATA ON STACK:
;*	at SP+9: 	16-bit address of first character of string 
;*	at SP+7: 	16-bit return address 
;*      at SP+6: 	return PPAGE
;*	at SP+4: 	copy of X 
;*	at SP+2: 	copy of Y 
;*	at SP:	 	copy of D 

	LDX 9,SP		;ADDRESS OF STRING INTO X
PUTS_SCI_BOTH_TOP:
	LDAB 1,X+
	CMPB #NULL
	BEQ PUTS_SCI_BOTH_END_OF_STRING
	PUTC_SCI0
	PUTC_SCI1
	BRA PUTS_SCI_BOTH_TOP
	
PUTS_SCI_BOTH_END_OF_STRING:
	PULD
	PULY
	PULX
	RTC		;RETURN TO CALLING PROGRAM
#ENDIF


;THE FOLLOWING LINE RESTORES LISTING FOR CODE OUTSIDE OF THIS LIBRARY
	LIST

#ENDIF			;#IFNDEF SERIALIO_INC