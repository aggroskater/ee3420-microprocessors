#IFNDEF TYPE_CONVERT	;using definition to prevent duplication of equates
TYPE_CONVERT EQU 1
#MSG "TYPE_CONVERT.INC REVISION 08/06/2010"
#MSG "COPYRIGHT 2010 WILLIAM STAPLETON"
#MSG "THIS FILE MAY BE FREELY DISTRIBUTED AS LONG AS IT REMAINS UNCHANGED AND FULLY CREDITED."

#INCLUDE ASCII.INC

;COMMENT OUT THE FOLLOWING LINE TO INCLUDE THE FULL FILE IN THE LISTING
;	NOLIST

;****************************************************************
;*  TYPE_CONVERT.INC                                             
;*  Include file including subroutines for type conversions
;*  e.g. text to integer, integer to text
;*  Conditional assembly requires ASM12 assembler (MiniIDE)
;*  Author: William A. Stapleton                                
;*  Start program with: N/A                                     
;*  Required libraries: none                               
;*  Required peripheral hardware: none	
;*  Special instructions: Should be included AFTER the RTS of the main program
;****************************************************************

;****************************************************************
;*  ATOI                                            
;*  CONVERSION FROM DECIMAL ASCII STRING TO 16-BIT INTEGER 
;*  Author: William A. Stapleton                                
;*  Required libraries: NONE                                  
;*  Required peripheral hardware: NONE 
;*  Expected data on stack at start of subroutine:
;*			at SP+3: ADDRESS OF NULL-TERMINATED STRING CONTAINING A "NUMBER" 
;*			at SP+1:  16-bit return address 
;* 			at SP: return PPAGE
;*  Data returned on stack:
;*			NONE
;*  Data returned in accumulator D:
;*  			INTEGER VALUE CREATED FROM CONVERSION
;*  Notes:		ONLY ACCEPTS DIGITS '0' - '9' FOR INPUT
;*			UNSIGNED INTEGERS ONLY
;****************************************************************

_ATOI:	PSHX			;SAVE REGISTERS
	PSHY
	LEAS -4,SP			;RESERVE SPACE ON STACK

;*  CURRENT DATA ON STACK:
;*	at SP+11: 	ADDRESS OF NULL-TERMINATED STRING CONTAINING A "NUMBER" 
;*	at SP+9: 	16-bit return address 
;*	AT SP+8:	RETURN PPAGE
;*	at SP+6: 	copy of X 
;*	at SP+4: 	copy of Y 
;*	at SP+2: 	space for single digit temporary
;*	at SP: 		space to format target integer

	MOVW #0, 0,SP		;TARGET INTEGER INITIALIZED TO 0
	MOVW #0, 2,SP		;INDIVIDUAL DIGIT VALUE CAST AS 16-BIT INITIALIZED TO 0
	LDX 11,SP		;X HAS ADDRESS OF INPUT STRING
ATOI1:	LDAA 1,X+		;LOAD 1 CHARACTER
	CMPA #'0'		;IS CHARACTER BETWEEN '0' AND '9'
	BLT ATOI_DONE
	CMPA #'9'
	BGT ATOI_DONE
	SUBA #'0'		;CONVERT ASCII TO 8-BIT INTEGER
	TFR A,D			;CAST AS 16-BIT INTEGER
	STD 2,SP		;SAVE DIGIT
	LDD 0,SP		;LOAD CURRENT TARGET
	LDY #10
	EMUL			;NEW TARGET = OLD TARGET * 10
	ADDD 2,SP		;NEW TARGET = OLD TARGET * 10 + NEW DIGIT
	STD 0,SP		;SAVE NEW TARGET
	BRA ATOI1
ATOI_DONE:
	LDD 0,SP		;AFTER ALL DIGITS ADDED RETURN TARGET

	LEAS 4,SP		;CLEAN UP TEMPORARY STORAGE
	PULY			;RESTORE REGISTERS
	PULX
	RTC



;****************************************************************
;*  ATOI_2                                            
;*  CONVERSION FROM BINARY ASCII STRING TO 16-BIT INTEGER 
;*  Author: William A. Stapleton                                
;*  Required libraries: NONE                                  
;*  Required peripheral hardware: NONE 
;*  Expected data on stack at start of subroutine:
;*			at SP+3: ADDRESS OF NULL-TERMINATED STRING CONTAINING A "NUMBER" 
;*			at SP+1:  16-bit return address 
;* 			at SP: return PPAGE
;*  Data returned on stack:
;*			NONE
;*  Data returned in accumulator D:
;*  			INTEGER VALUE CREATED FROM CONVERSION
;*  Notes:		ONLY ACCEPTS DIGITS '0' - '1' FOR INPUT
;*			UNSIGNED INTEGERS ONLY
;****************************************************************
_ATOI_2:	PSHX			;SAVE REGISTERS
	PSHY
	LEAS -4,SP			;RESERVE SPACE ON STACK
	
;*  CURRENT DATA ON STACK:
;*	at SP+11: 	ADDRESS OF NULL-TERMINATED STRING CONTAINING A "NUMBER" 
;*	at SP+9: 	16-bit return address 
;*	AT SP+8:	RETURN PPAGE
;*	at SP+6: 	copy of X 
;*	at SP+4: 	copy of Y 
;*	at SP+2: 	space for single digit temporary
;*	at SP: 		space to format target integer

	MOVW #0, 0,SP		;TARGET INTEGER INITIALIZED TO 0
	MOVW #0, 2,SP		;INDIVIDUAL DIGIT VALUE CAST AS 16-BIT INITIALIZED TO 0
	LDX 11,SP		;X HAS ADDRESS OF INPUT STRING
ATOI_2_1:	LDAA 1,X+		;LOAD 1 CHARACTER
	CMPA #'0'		;IS CHARACTER BETWEEN '0' AND '1'
	BLT ATOI_2_DONE
	CMPA #'1'
	BGT ATOI_2_DONE
	SUBA #'0'		;CONVERT ASCII TO 8-BIT INTEGER
	TFR A,D			;CAST AS 16-BIT INTEGER
	STD 2,SP		;SAVE DIGIT
	LDD 0,SP		;LOAD CURRENT TARGET
	LDY #2			;BASE IS 2 (BINARY)
	EMUL			;NEW TARGET = OLD TARGET * 2
	ADDD 2,SP		;NEW TARGET = OLD TARGET * 2 + NEW DIGIT
	STD 0,SP		;SAVE NEW TARGET
	BRA ATOI_2_1
ATOI_2_DONE:
	LDD 0,SP		;AFTER ALL DIGITS ADDED RETURN TARGET

	LEAS 4,SP		;CLEAN UP TEMPORARY STORAGE
	PULY			;RESTORE REGISTERS
	PULX
	RTC

;****************************************************************
;*  ATOI_16                                            
;*  CONVERSION FROM HEXADECIMAL ASCII STRING TO 16-BIT INTEGER 
;*  Author: William A. Stapleton                                
;*  Required libraries: NONE                                  
;*  Required peripheral hardware: NONE 
;*  Expected data on stack at start of subroutine:
;*			at SP+3: ADDRESS OF NULL-TERMINATED STRING CONTAINING A "NUMBER" 
;*			at SP+1:  16-bit return address 
;* 			at SP: return PPAGE
;*  Data returned on stack:
;*			NONE
;*  Data returned in accumulator D:
;*  			INTEGER VALUE CREATED FROM CONVERSION
;*  Notes:		ONLY ACCEPTS DIGITS '0' - '9' AND 'A' - 'F' FOR INPUT
;*			CONVERTS INPUT STRING TO UPPERCASE
;*			UNSIGNED INTEGERS ONLY
;****************************************************************
_ATOI_16:	PSHX			;SAVE REGISTERS
	PSHY
	LEAS -4,SP			;RESERVE SPACE ON STACK

;*  CURRENT DATA ON STACK:
;*	at SP+11: 	ADDRESS OF NULL-TERMINATED STRING CONTAINING A "NUMBER" 
;*	at SP+9: 	16-bit return address 
;*	AT SP+8:	RETURN PPAGE
;*	at SP+6: 	copy of X 
;*	at SP+4: 	copy of Y 
;*	at SP+2: 	space for single digit temporary
;*	at SP: 		space to format target integer

	LDX 11,SP
	UCASE <0,X>		;FORCE INPUT TO UPPER CASE
	
	MOVW #0, 0,SP		;TARGET INTEGER INITIALIZED TO 0
	MOVW #0, 2,SP		;INDIVIDUAL DIGIT VALUE CAST AS 16-BIT INITIALIZED TO 0
	LDX 11,SP		;X HAS ADDRESS OF INPUT STRING
ATOI_16_1:	LDAA 1,X+		;LOAD 1 CHARACTER
	CMPA #'0'		;IS CHARACTER BETWEEN '0' AND '1'
	BLT ATOI_16_DONE
	CMPA #'9'
	BLE ATOI_16_2
	CMPA #'A'
	BLT ATOI_16_DONE
	CMPA #'F'
	BGT ATOI_16_DONE
ATOI_16_2:
	SUBA #'0'		;CONVERT ASCII TO 8-BIT INTEGER
	CMPA #10
	BLT ATOI_16_3		;A>=10 MEANS 'A'-'F' SO NEED CORRECTION FACTOR
	SUBA #7
ATOI_16_3:
	TFR A,D			;CAST AS 16-BIT INTEGER
	STD 2,SP		;SAVE DIGIT
	LDD 0,SP		;LOAD CURRENT TARGET
	LDY #16			;BASE IS 16 (HEXADECIMAL)
	EMUL			;NEW TARGET = OLD TARGET * 16
	ADDD 2,SP		;NEW TARGET = OLD TARGET * 16 + NEW DIGIT
	STD 0,SP		;SAVE NEW TARGET
	BRA ATOI_16_1
ATOI_16_DONE:
	LDD 0,SP		;AFTER ALL DIGITS ADDED RETURN TARGET

	LEAS 4,SP			;CLEAN UP TEMPORARY STORAGE
	PULY			;RESTORE REGISTERS
	PULX
	RTC


;****************************************************************
;*  ITOA                                            
;*  CONVERSION FROM 16-BIT INTEGER TO DECIMAL ASCII STRING
;*  Author: William A. Stapleton                                
;*  Required libraries: NONE                                  
;*  Required peripheral hardware: NONE 
;*  Expected data on stack at start of subroutine:
;*			at SP+5: address of target string
;*			at SP+3: integer value to be converted
;*			at SP+1:  16-bit return address 
;* 			at SP: return PPAGE;*  Data returned on stack:
;*			NONE
;*  Data returned in accumulator D:
;*  			none
;*  Notes:		UNSIGNED INTEGERS ONLY
;*			RESULTING STRING IS NULL-TERMINATED ASCII
;****************************************************************

_ITOA:	PSHX			;SAVE REGISTERS
	PSHY
	PSHD
;*  CURRENT DATA ON STACK:
;*	at SP+11: 	ADDRESS OF NULL-TERMINATED STRING CONTAINING A "NUMBER" 
;*	AT SP+9:	16-BIT UNSIGNED DATA TO BE CONVERTED TO STRING
;*	at SP+7: 	16-bit return address 
;*	AT SP+6:	RETURN PPAGE
;*	at SP+4: 	copy of X 
;*	at SP+2: 	copy of Y 
;*	at SP: 		copy of D

	LDD 9,SP		;DATA TO BE CONVERTED
	LDY #0			;Y WILL COUNT DIGITS
ITOA1:	LDX #10			;BASE 10 ARITHMETIC			
	IDIV			;INTEGER /10 TO YIELD X=QUOTIENT, D=REMAINDER 
	PSHD			;SAVE REMAINDER ON STACK
	INY			;ADD TO DIGIT COUNT
	TFR X,D			;QUOTIENT BECOMES NEW INTEGER
	CPD #0			;IF QUOTIENT IS ZERO ALL DIGITS FOUND
	BNE ITOA1		;REPEAT

	LEAX 0,SP		;GET CURRENT STACK POINTER INTO X
	PSHX			;COPY ONTO STACK
	LDD 0,SP		;GET COPY OF SAVED SP INTO D
	PULX			;CLEAR COPY OF SP OFF STACK
	PSHY			;COPY OF DIGIT COUNT IONTO STACK
	ADDD 0,SP		;ADD DIGIT COUNT TO D
	ADDD 0,SP		;ADD DIGIT COUNT TO D A SECOND TIME BECASE EACH DIGIT IS STORED AS A 16-BIT WORD
	PULY			;CLEAR STACK OF COPY OF COPY OF DIGIT COUNT
;AT THIS POINT D CONTAINS THE VALUE OF THE STACK POINTER FROM BEFORE STOREING A VARIABLE NUMBER OF DIGITS
	TFR D,X			;NOW X POINTS TO INITAL STACK AND SP POINTS TO STACK WITH DIGITS STORED

	
	LDX 11,X		;LOAD ADDRESS OF TARGET STRING
ITOA2:	PULD			;READ MOST SIGNIFICANT DIGIT LEFT ON STACK
	ADDB #'0'		;CONVERT TO ASCII
	STAB 1,X+		;STORE CHARACTER IN STRING
	DBNE Y,ITOA2		;DECREMENT CHARACTER COUNT, IF NON-ZERO REPEAT
	
	MOVB #NULL, 0,X		;AFTER ALL CHARACTERS ADDED TO STRING, NULL-TERMINATE
	
	PULD		
	PULY
	PULX
	RTC

	

;****************************************************************
;*  ITOA_2                                           
;*  CONVERSION FROM 16-BIT INTEGER TO BINARY ASCII STRING
;*  Author: William A. Stapleton                                
;*  Required libraries: NONE                                  
;*  Required peripheral hardware: NONE 
;*  Expected data on stack at start of subroutine:
;*			at SP+5: address of target string
;*			at SP+3: integer value to be converted
;*			at SP+1:  16-bit return address 
;* 			at SP: return PPAGE
;*  Data returned on stack:
;*			NONE
;*  Data returned in accumulator D:
;*  			none
;*  Notes:		UNSIGNED INTEGERS ONLY
;*			RESULTING STRING IS NULL-TERMINATED ASCII
;****************************************************************

_ITOA_2:	PSHX			;SAVE REGISTERS
	PSHY
	PSHD
;*  CURRENT DATA ON STACK:
;*	at SP+11: 	ADDRESS OF NULL-TERMINATED STRING CONTAINING A "NUMBER" 
;*	AT SP+9:	16-BIT UNSIGNED DATA TO BE CONVERTED TO STRING
;*	at SP+7: 	16-bit return address 
;*	AT SP+6:	RETURN PPAGE
;*	at SP+4: 	copy of X 
;*	at SP+2: 	copy of Y 
;*	at SP: 		copy of D

	LDD 9,SP
	LDY #0			;Y WILL COUNT DIGITS
ITOA_2_1: LDX #2		;BASE 2 ARITHMETIC			
	IDIV			;INTEGER /2 TO YIELD X=QUOTIENT, D=REMAINDER 
	PSHD			;SAVE REMAINDER ON STACK
	INY			;ADD TO DIGIT COUNT
	TFR X,D			;QUOTIENT BECOMES NEW INTEGER
	CPD #0			;IF QUOTIENT IS ZERO ALL DIGITS FOUND
	BNE ITOA_2_1		;REPEAT
	
	LEAX 0,SP		;GET CURRENT STACK POINTER INTO X
	PSHX			;COPY ONTO STACK
	LDD 0,SP		;GET COPY OF SAVED SP INTO D
	PULX			;CLEAR COPY OF SP OFF STACK
	PSHY			;COPY OF DIGIT COUNT IONTO STACK
	ADDD 0,SP		;ADD DIGIT COUNT TO D
	ADDD 0,SP		;ADD DIGIT COUNT TO D A SECOND TIME BECASE EACH DIGIT IS STORED AS A 16-BIT WORD
	PULY			;CLEAR STACK OF COPY OF COPY OF DIGIT COUNT
;AT THIS POINT D CONTAINS THE VALUE OF THE STACK POINTER FROM BEFORE STOREING A VARIABLE NUMBER OF DIGITS
	TFR D,X			;NOW X POINTS TO INITAL STACK AND SP POINTS TO STACK WITH DIGITS STORED

	
	LDX 11,X		;LOAD ADDRESS OF TARGET STRING
ITOA_2_2: PULD			;READ MOST SIGNIFICANT DIGIT LEFT ON STACK
	ADDB #'0'		;CONVERT TO ASCII
	STAB 1,X+		;STORE CHARACTER IN STRING
	DBNE Y,ITOA_2_2		;DECREMENT CHARACTER COUNT, IF NON-ZERO REPEAT
	
	MOVB #NULL, 0,X		;AFTER ALL CHARACTERS ADDED TO STRING, NULL-TERMINATE
	
	PULD		
	PULY
	PULX
	RTC


;****************************************************************
;*  ITOA_16                                           
;*  CONVERSION FROM 16-BIT INTEGER TO HEXADECIMAL ASCII STRING
;*  Author: William A. Stapleton                                
;*  Required libraries: NONE                                  
;*  Required peripheral hardware: NONE 
;*  Expected data on stack at start of subroutine:
;*			at SP+5: address of target string
;*			at SP+3: integer value to be converted
;*			at SP+1:  16-bit return address 
;* 			at SP: return PPAGE
;*  Data returned on stack:
;*			NONE
;*  Data returned in accumulator D:
;*  			none
;*  Notes:		UNSIGNED INTEGERS ONLY
;*			RESULTING STRING IS NULL-TERMINATED ASCII
;****************************************************************

_ITOA_16:	PSHX			;SAVE REGISTERS
	PSHY
	PSHD
;*  CURRENT DATA ON STACK:
;*	at SP+11: 	ADDRESS OF NULL-TERMINATED STRING CONTAINING A "NUMBER" 
;*	AT SP+9:	16-BIT UNSIGNED DATA TO BE CONVERTED TO STRING
;*	at SP+7: 	16-bit return address 
;*	AT SP+6:	RETURN PPAGE
;*	at SP+4: 	copy of X 
;*	at SP+2: 	copy of Y 
;*	at SP: 		copy of D

	LDD 9,SP
	LDY #0			;Y WILL COUNT DIGITS
ITOA_16_1: LDX #16		;BASE 2 ARITHMETIC			
	IDIV			;INTEGER /2 TO YIELD X=QUOTIENT, D=REMAINDER 
	PSHD			;SAVE REMAINDER ON STACK
	INY			;ADD TO DIGIT COUNT
	TFR X,D			;QUOTIENT BECOMES NEW INTEGER
	CPD #0			;IF QUOTIENT IS ZERO ALL DIGITS FOUND
	BNE ITOA_16_1		;REPEAT
	
	LEAX 0,SP		;GET CURRENT STACK POINTER INTO X
	PSHX			;COPY ONTO STACK
	LDD 0,SP		;GET COPY OF SAVED SP INTO D
	PULX			;CLEAR COPY OF SP OFF STACK
	PSHY			;COPY OF DIGIT COUNT IONTO STACK
	ADDD 0,SP		;ADD DIGIT COUNT TO D
	ADDD 0,SP		;ADD DIGIT COUNT TO D A SECOND TIME BECASE EACH DIGIT IS STORED AS A 16-BIT WORD
	PULY			;CLEAR STACK OF COPY OF COPY OF DIGIT COUNT
;AT THIS POINT D CONTAINS THE VALUE OF THE STACK POINTER FROM BEFORE STOREING A VARIABLE NUMBER OF DIGITS
	TFR D,X			;NOW X POINTS TO INITAL STACK AND SP POINTS TO STACK WITH DIGITS STORED

	
	LDX 11,X		;LOAD ADDRESS OF TARGET STRING
ITOA_16_2: PULD			;READ MOST SIGNIFICANT DIGIT LEFT ON STACK
	ADDB #'0'		;CONVERT TO ASCII
	CMPB #'9'		;CHARACTER > '9' MEANS HEXADECIMAL 'A'-'F' SO ADJUST
	BLE ITOA_16_3
	ADDB #7			;ADD 7 TO GO FROM '9' TO 'A'
ITOA_16_3:
	STAB 1,X+		;STORE CHARACTER IN STRING
	DBNE Y,ITOA_16_2		;DECREMENT CHARACTER COUNT, IF NON-ZERO REPEAT
	
	MOVB #NULL, 0,X		;AFTER ALL CHARACTERS ADDED TO STRING, NULL-TERMINATE
	
	PULD		
	PULY
	PULX
	RTC


;****************************************************************
;*  ITOA_FIXED                                           
;*  CONVERSION FROM 16-BIT INTEGER TO FIXED-LENGTH 5-DIGIT DECIMAL ASCII STRING
;*  Author: William A. Stapleton                                
;*  Required libraries: NONE                                  
;*  Required peripheral hardware: NONE 
;*  Expected data on stack at start of subroutine:
;*			at SP+5: address of target string
;*			at SP+3: integer value to be converted
;*			at SP+1:  16-bit return address 
;* 			at SP: return PPAGE
;*  Data returned on stack:
;*			NONE
;*  Data returned in accumulator D:
;*  			none
;*  Notes:		UNSIGNED INTEGERS ONLY
;*			RESULTING STRING IS FIXED LENGTH, NULL-TERMINATED ASCII
;****************************************************************	
_ITOA_FIXED:	
	PSHX
	PSHY
	PSHD
;*  CURRENT DATA ON STACK:
;*	at SP+11: 	ADDRESS OF NULL-TERMINATED STRING CONTAINING A "NUMBER" 
;*	AT SP+9:	16-BIT UNSIGNED DATA TO BE CONVERTED TO STRING
;*	at SP+7: 	16-bit return address 
;*	AT SP+6:	RETURN PPAGE
;*	at SP+4: 	copy of X 
;*	at SP+2: 	copy of Y 
;*	at SP: 		copy of D
	
	LDD 9,SP
	LDY #5			;Y WILL COUNT DIGITS
ITOAF1:	LDX #10			;BASE 10 ARITHMETIC			
	IDIV			;INTEGER /10 TO YIELD X=QUOTIENT, D=REMAINDER 
	PSHD			;SAVE REMAINDER ON STACK
	TFR X,D			;QUOTIENT BECOMES NEW INTEGER
	DBNE Y,ITOAF1		;REPEAT
	
	LDY #5			
	LDX 21,SP		;LOAD ADDRESS OF TARGET STRING -> 5 DIGITS PUSHED AS 16-BIT WORDS MOVES 10,SP TO 20,SP
ITOAF2:	PULD			;READ MOST SIGNIFICANT DIGIT LEFT ON STACK
	ADDB #'0'		;CONVERT TO ASCII
	STAB 1,X+		;STORE CHARACTER IN STRING
	DBNE Y,ITOAF2		;DECREMENT CHARACTER COUNT, IF NON-ZERO REPEAT
	
	MOVB #NULL, 0,X		;AFTER ALL CHARACTERS ADDED TO STRING, NULL-TERMINATE
	
	PULD		
	PULY
	PULX
	RTC


;****************************************************************
;*  ITOA_2_FIXED                                           
;*  CONVERSION FROM 16-BIT INTEGER TO BINARY 16-DIGIT ASCII STRING
;*  Author: William A. Stapleton                                
;*  Required libraries: NONE                                  
;*  Required peripheral hardware: NONE 
;*  Expected data on stack at start of subroutine:
;*			at SP+4: address of target string
;*			at SP+3: integer value to be converted
;*			at SP+1:  16-bit return address 
;* 			at SP: return PPAGE
;*  Data returned on stack:
;*			NONE
;*  Data returned in accumulator D:
;*  			none
;*  Notes:		UNSIGNED INTEGERS ONLY
;*			RESULTING STRING IS NULL-TERMINATED ASCII
;****************************************************************

_ITOA_2_FIXED:	PSHX			;SAVE REGISTERS
	PSHY
	PSHD
;*  CURRENT DATA ON STACK:
;*	at SP+11: 	ADDRESS OF NULL-TERMINATED STRING CONTAINING A "NUMBER" 
;*	AT SP+9:	16-BIT UNSIGNED DATA TO BE CONVERTED TO STRING
;*	at SP+7: 	16-bit return address 
;*	AT SP+6:	RETURN PPAGE
;*	at SP+4: 	copy of X 
;*	at SP+2: 	copy of Y 
;*	at SP: 		copy of D

	LDD 9,SP
	LDY #16			;Y WILL COUNT DIGITS
ITOA_2F_1: LDX #2		;BASE 2 ARITHMETIC			
	IDIV			;INTEGER /2 TO YIELD X=QUOTIENT, D=REMAINDER 
	PSHD			;SAVE REMAINDER ON STACK
	TFR X,D			;QUOTIENT BECOMES NEW INTEGER
	DBNE Y,ITOA_2F_1		;REPEAT
	
	LDY #16			;Y WILL COUNT DIGITS
	LDX 43,SP		;LOAD ADDRESS OF TARGET STRING -> 16 DIGITS PUSHED AS 16-BIT WORDS MOVES 10,SP TO 42,SP
ITOA_2F_2: PULD			;READ MOST SIGNIFICANT DIGIT LEFT ON STACK
	ADDB #'0'		;CONVERT TO ASCII
	STAB 1,X+		;STORE CHARACTER IN STRING
	DBNE Y,ITOA_2F_2		;DECREMENT CHARACTER COUNT, IF NON-ZERO REPEAT
	
	MOVB #NULL, 0,X		;AFTER ALL CHARACTERS ADDED TO STRING, NULL-TERMINATE
	
	PULD		
	PULY
	PULX
	RTC


;****************************************************************
;*  ITOA_16_FIXED                                           
;*  CONVERSION FROM 16-BIT INTEGER TO 4-DIGIT HEXADECIMAL ASCII STRING
;*  Author: William A. Stapleton                                
;*  Required libraries: NONE                                  
;*  Required peripheral hardware: NONE 
;*  Expected data on stack at start of subroutine:
;*			at SP+5: address of target string
;*			at SP+3: integer value to be converted
;*			at SP+1:  16-bit return address 
;* 			at SP: return PPAGE
;*  Data returned on stack:
;*			NONE
;*  Data returned in accumulator D:
;*  			none
;*  Notes:		UNSIGNED INTEGERS ONLY
;*			RESULTING STRING IS NULL-TERMINATED ASCII
;****************************************************************

_ITOA_16_FIXED:	PSHX			;SAVE REGISTERS
	PSHY
	PSHD
;*  CURRENT DATA ON STACK:
;*	at SP+11: 	ADDRESS OF NULL-TERMINATED STRING CONTAINING A "NUMBER" 
;*	AT SP+9:	16-BIT UNSIGNED DATA TO BE CONVERTED TO STRING
;*	at SP+7: 	16-bit return address 
;*	AT SP+6:	RETURN PPAGE
;*	at SP+4: 	copy of X 
;*	at SP+2: 	copy of Y 
;*	at SP: 		copy of D

	LDD 9,SP
	LDY #4			;Y WILL COUNT DIGITS
ITOA_16F_1: LDX #16		;BASE 2 ARITHMETIC			
	IDIV			;INTEGER /2 TO YIELD X=QUOTIENT, D=REMAINDER 
	PSHD			;SAVE REMAINDER ON STACK
	TFR X,D			;QUOTIENT BECOMES NEW INTEGER
	DBNE Y,ITOA_16F_1		;REPEAT
	
	LDY #4			;Y WILL COUNT DIGITS
	LDX 19,SP		;LOAD ADDRESS OF TARGET STRING -> 4 DIGITS PUSHED AS 16-BIT WORDS MOVES 10,SP TO 18,SP
ITOA_16F_2: PULD			;READ MOST SIGNIFICANT DIGIT LEFT ON STACK
	ADDB #'0'		;CONVERT TO ASCII
	CMPB #'9'		;CHARACTER > '9' MEANS HEXADECIMAL 'A'-'F' SO ADJUST
	BLT ITOA_16F_3
	ADDB #7			;ADD 7 TO GO FROM '9' TO 'A'
ITOA_16F_3:
	STAB 1,X+		;STORE CHARACTER IN STRING
	DBNE Y,ITOA_16F_2		;DECREMENT CHARACTER COUNT, IF NON-ZERO REPEAT
	
	MOVB #NULL, 0,X		;AFTER ALL CHARACTERS ADDED TO STRING, NULL-TERMINATE
	
	PULD		
	PULY
	PULX
	RTC


;****************************************************************
;*  UCASE                                           
;*  CONVERSION OF ASCII STRING TO UPPERCASE
;*  Author: William A. Stapleton                                
;*  Required libraries: NONE                                  
;*  Required peripheral hardware: NONE 
;*  Expected data on stack at start of subroutine:
;*			at SP+3: address of target string
;*			at SP+1:  16-bit return address 
;* 			at SP: return PPAGE
;*  Data returned on stack:
;*			NONE
;*  Data returned in accumulator D:
;*  			none
;*  Notes:		CONVERTS 'a'-'z' INTO 'A'-'Z'
;*			RESULTING STRING OVERWRITES ORIGINAL
;****************************************************************	

_UCASE:	
	PSHX
	PSHY
	PSHD
;*  CURRENT DATA ON STACK:
;*	at SP+9: 	ADDRESS OF STRING 
;*	at SP+7: 	16-bit return address 
;*	AT SP+6: 	RETURN PPAGE
;*	at SP+4: 	copy of X 
;*	at SP+2: 	copy of Y 
;*	at SP: 		copy of D

	LDX 9,SP	;ADDRESS OF STRING
UCASE1: LDAB 1,X+	;READ 1 CHARACTER, POINT TO NEXT CHARACTER
	CMPB #NULL
	BEQ UCASE_DONE	;NULL MEANS END OF STRING
	CMPB #'a'
	BLT UCASE1	;CHARACTRER < 'a' NEEDS NO ACTION
	CMPB #'z'
	BGT UCASE1	;CHARACTER > 'z' NEEDS NO ACTION
	SUBB #$20	;ALL LOWER CASE CHARACTERS ARE $20 HIGHER THAN UPPER CASE COUNTERPARTS
	STAB -1,X	;WRITE NEW CHARACTER OVER ORIGINAL
	BRA UCASE1

UCASE_DONE
	PULD		
	PULY
	PULX
	RTC



;****************************************************************
;*  LCASE                                           
;*  CONVERSION OF ASCII STRING TO LOWERCASE
;*  Author: William A. Stapleton                                
;*  Required libraries: NONE                                  
;*  Required peripheral hardware: NONE 
;*  Expected data on stack at start of subroutine:
;*			at SP+3: address of target string
;*			at SP+1:  16-bit return address 
;* 			at SP: return PPAGE
;*  Data returned on stack:
;*			NONE
;*  Data returned in accumulator D:
;*  			none
;*  Notes:		CONVERTS 'A'-'Z' INTO 'a'-'z'
;*			RESULTING STRING OVERWRITES ORIGINAL
;****************************************************************	

_LCASE:	
	PSHX
	PSHY
	PSHD
;*  CURRENT DATA ON STACK:
;*	at SP+9: 	ADDRESS OF STRING 
;*	at SP+7: 	16-bit return address 
;*	AT sp+6: 	RETURN PPAGE
;*	at SP+4: 	copy of X 
;*	at SP+2: 	copy of Y 
;*	at SP: 		copy of D

	LDX 9,SP	;ADDRESS OF STRING
LCASE1: LDAB 1,X+	;READ 1 CHARACTER, POINT TO NEXT CHARACTER
	CMPB #NULL
	BEQ LCASE_DONE	;NULL MEANS END OF STRING
	CMPB #'A'
	BLT LCASE1	;CHARACTRER < 'A' NEEDS NO ACTION
	CMPB #'Z'
	BGT LCASE1	;CHARACTER > 'Z' NEEDS NO ACTION
	ADDB #$20	;ALL LOWER CASE CHARACTERS ARE $20 HIGHER THAN UPPER CASE COUNTERPARTS
	STAB -1,X	;WRITE NEW CHARACTER OVER ORIGINAL
	BRA LCASE1

LCASE_DONE
	PULD		
	PULY
	PULX
	RTC


;THE FOLLOWING LINE RESTORES LISTING FOR CODE OUTSIDE OF THIS LIBRARY
	LIST

#ENDIF		;TYPE_CONVERT