#IFNDEF MC9S12REGS
MC9S12REGS	EQU 1
#MSG "MC9S12_REGISTERS.INC REVISION 08/06/2010"
#MSG "COPYRIGHT 2010 WILLIAM STAPLETON"
#MSG "THIS FILE MAY BE FREELY DISTRIBUTED AS LONG AS IT REMAINS UNCHANGED AND FULLY CREDITED."

#INCLUDE SYSTEM_SELECT.INC
#INCLUDE CONSTANTS.INC

;COMMENT OUT THE FOLLOWING LINE TO INCLUDE THE FULL FILE IN THE LISTING
	NOLIST

;*****************************************
;This file is intended for use with the examples for EE 3320 at Texas State University - San Marcos.
;These are register definitions for Freescale MC9S12DP256B microprocessor on the EVBPlus.com Dragon12 board. 
;Assumes use of D-BUG12 operating system on Dragon12 in standard DEBUG mode.
;User code is expected in RAM.
;
;This file is adapted from "registers.inc" from the EVBPlus.com Dragon12 CD-ROM and
;the file "DP256reg.inc" from Axiom Manufacturing's CML-12S documentation
;
;The bitfield definitions have been added for convenience.  
;This file represents the first effort to include these definition and 
;the list may be incomplete or inaccurate.  
;Future revisions will hopefully address any shortcomings.
;Registers that simply hold a single 8-bit value or 
;that have each of the 8 bits labeled as bit0 - bit7 have not had
;explicit bit definitions created.
;*****************************************


REGBASE	 equ	$0	; register base


#IF SYSTEM_OS = DBUG12

DATASTART equ	$1000	; Start of data memory
DATAEND  equ	$1FFE	; Stack pointer initial value (end of data RAM area)
PRSTART equ	$2000	; Start of program memory (might be ROM)
PREND	equ	$3BFF	; End of program memory

; Functions in D-Bug12
;ACCESS THE FOLLOWING BY PUSHING THE PARAMETERS ON THE STACK LAST PARAMETER FIRST 
;THE LAST PARAMETER  PLACED ON THE STACK IS THE SECOND PARAMETER
;THE FIRST PARAMETER SHOULD BE LOCATED IN ACCUMULATOR D
;THE CALLING LINE SHOULD LIKE SIMILAR TO ONE OF THE FOLLOWING:
;FOR "NEAR" FUNCTIONS, E.G. GETCHAR:
;	JSR [GETCHAR,PCR]
;FOR "FAR" FUNCTIONS, E.G. GETCMDLINE
;	CALL [GETCMDLINE,PCR]
Getchar	equ	$EE84	; Implemented in emulator	
Putchar equ	$EE86   ; Implemented in emulator
Printf  equ     $EE88
GetCmdLine equ  $EE8A   ; FAR call
Sscanhex equ	$EE8E   ; FAR call
Isxdigit equ    $EE92
Toupper equ     $EE94
Isalpha equ     $EE96
Strlen  equ     $EE98
Strcpy  equ     $EE9A
Out2hex equ     $EE9C   ; FAR call
Out4hex equ     $EEA0   ; FAR call
SetUserVector equ $EEA4 ; No longer used
WriteEEByte equ $EEA6   ; FAR call
EraseEE equ     $EEAA   ; FAR call
ReadMem equ     $EEAE   ; FAR call
WriteMem equ    $EEB2   ; FAR call

VECTORTABLE equ $3E00	; Vectors go here SHOULD ALSO INITIALIZE AT RUNTIME
STATICVECTORS equ 0	; Define vectors statically (in "ROM")
INITIALIZEVECTORS equ 0	; Initialize vectors at runtime

RAMSTART equ	DATASTART ; For compatibility
RAMEND equ	DATAEND   

;*INTERRUPT VECTORS

UserRsrv0x80 equ (0*2)+VECTORTABLE
UserRsrv0x82 equ (1*2)+VECTORTABLE
UserRsrv0x84 equ (2*2)+VECTORTABLE
UserRsrv0x86 equ (3*2)+VECTORTABLE
UserRsrv0x88 equ (4*2)+VECTORTABLE
UserRsrv0x8a equ (5*2)+VECTORTABLE
UserPWMShDn equ (6*2)+VECTORTABLE
UserPortP equ (7*2)+VECTORTABLE
UserMSCAN4Tx equ (8*2)+VECTORTABLE
UserMSCAN4Rx equ (9*2)+VECTORTABLE
UserMSCAN4Errs equ (10*2)+VECTORTABLE
UserMSCAN4Wake equ (11*2)+VECTORTABLE
UserMSCAN3Tx equ (12*2)+VECTORTABLE
UserMSCAN3Rx equ (13*2)+VECTORTABLE
UserMSCAN3Errs equ (14*2)+VECTORTABLE
UserMSCAN3Wake equ (15*2)+VECTORTABLE
UserMSCAN2Tx equ (16*2)+VECTORTABLE
UserMSCAN2Rx equ (17*2)+VECTORTABLE
UserMSCAN2Errs equ (18*2)+VECTORTABLE
UserMSCAN2Wake equ (19*2)+VECTORTABLE
UserMSCAN1Tx equ (20*2)+VECTORTABLE
UserMSCAN1Rx equ (21*2)+VECTORTABLE
UserMSCAN1Errs equ (22*2)+VECTORTABLE
UserMSCAN1Wake equ (23*2)+VECTORTABLE
UserMSCAN0Tx equ (24*2)+VECTORTABLE
UserMSCAN0Rx equ (25*2)+VECTORTABLE
UserMSCAN0Errs equ (26*2)+VECTORTABLE
UserMSCAN0Wake equ (27*2)+VECTORTABLE
UserFlash equ (28*2)+VECTORTABLE
UserEEPROM equ (29*2)+VECTORTABLE
UserSPI2 equ (30*2)+VECTORTABLE
UserSPI1 equ (31*2)+VECTORTABLE
UserIIC equ (32*2)+VECTORTABLE
UserDLC equ (33*2)+VECTORTABLE
UserSCME equ (34*2)+VECTORTABLE
UserCRG equ (35*2)+VECTORTABLE
UserPAccBOv equ (36*2)+VECTORTABLE
UserModDwnCtr equ (37*2)+VECTORTABLE
UserPortH equ (38*2)+VECTORTABLE
UserPortJ equ (39*2)+VECTORTABLE
UserAtoD1 equ (40*2)+VECTORTABLE
UserAtoD0 equ (41*2)+VECTORTABLE
UserSCI1 equ (42*2)+VECTORTABLE
UserSCI0 equ (43*2)+VECTORTABLE
UserSPI0 equ (44*2)+VECTORTABLE
UserPAccEdge equ (45*2)+VECTORTABLE
UserPAccOvf equ (46*2)+VECTORTABLE
UserTimerOvf equ (47*2)+VECTORTABLE
UserTimerCh7 equ (48*2)+VECTORTABLE
UserTimerCh6 equ (49*2)+VECTORTABLE
UserTimerCh5 equ (50*2)+VECTORTABLE
UserTimerCh4 equ (51*2)+VECTORTABLE
UserTimerCh3 equ (52*2)+VECTORTABLE
UserTimerCh2 equ (53*2)+VECTORTABLE
UserTimerCh1 equ (54*2)+VECTORTABLE
UserTimerCh0 equ (55*2)+VECTORTABLE
UserRTI equ (56*2)+VECTORTABLE
UserIRQ equ (57*2)+VECTORTABLE
UserXIRQ equ (58*2)+VECTORTABLE
UserSWI equ (59*2)+VECTORTABLE
UserTrap equ (60*2)+VECTORTABLE

#ENDIF ;SYSTEM_OS = DBUG12


;*CONDITION CODE REGISTER CONTENTS

CCR_S		EQU	BIT7
CCR_X		EQU	BIT6
CCR_H		EQU	BIT5
CCR_I		EQU	BIT4
CCR_N		EQU	BIT3
CCR_Z		EQU	BIT2
CCR_V		EQU	BIT1
CCR_C		EQU	BIT0

;*
;*
;*  HC12 i/o register locations (9s12dp256)
;*
;*

;*BASIC BUS REGISTERS

PORTA:          equ REGBASE+0   ;port a = address lines a8 - a15
PTA:            equ PORTA
PORTB:          equ REGBASE+1   ;port b = address lines a0 - a7
PTB:            equ PORTB
DDRA:           equ REGBASE+2   ;port a direction register
DDRB:           equ REGBASE+3   ;port a direction register


PORTE:          equ REGBASE+8   ;port e = mode,irq and control signals
PTE:            equ PORTE
PORTE_XIRQ	EQU BIT7
PORTE_IRQ	EQU BIT6
PORTE_RW	EQU BIT5
PORTE_LSTRB	EQU BIT4
PORTE_ECLK	EQU BIT3
PORTE_MODA	EQU BIT2
PORTE_MODB	EQU BIT1
PORTE_NOACC	EQU BIT0
PORTE_XCLKS	EQU BIT0
DDRE:           equ REGBASE+9   ;port e direction register


;*PORT INTEGRATION MODULE 

PEAR:           equ REGBASE+$a  ;port e assignments
PEAR_NOACCE	EQU	BIT7
PEAR_PIPOE	EQU 	BIT5
PEAR_NECLK	EQU	BIT4
PEAR_LSTRE	EQU	BIT3
PEAR_RDWE	EQU	BIT2

MODE:           equ REGBASE+$b  ;mode register
MODE_MODC	EQU	BIT7
MODE_MODB	EQU 	BIT6
MODE_MODA	EQU	BIT5
MODE_IVIS	EQU	BIT3
MODE_EMK	EQU	BIT1
MODE_EME	EQU	BIT0

PUCR:           equ REGBASE+$c  ;port pull-up control register
PUCR_PUPKE	EQU	BIT7
PUCR_PUPEE	EQU	BIT4
PUCR_PUPBE	EQU	BIT1
PUCR_PUPAE	EQU	BIT0

RDRIV:          equ REGBASE+$d  ;port reduced drive control register
RDRIV_RDPK	EQU	BIT7
RDRIV_RDPE	EQU	BIT4
RDRIV_RDPB	EQU	BIT1
RDRIV_RDPA	EQU	BIT0

EBICTL:		equ REGBASE+$e  ;e stretch control
EBICTL_ESTR	EQU	BIT0

INITRM:         equ REGBASE+$10 ;ram location register
INITRM_RAM15	EQU 	BIT7
INITRM_RAM14	EQU 	BIT6
INITRM_RAM13	EQU 	BIT5
INITRM_RAM12	EQU 	BIT4
INITRM_RAM11	EQU 	BIT3
INITRM_RAMHAL	EQU 	BIT0

INITRG:         equ REGBASE+$11 ;register location register
INITRG_REG14	EQU	BIT6
INITRG_REG13	EQU	BIT5
INITRG_REG12	EQU	BIT4
INITRG_REG11	EQU	BIT3

INITEE:         equ REGBASE+$12 ;eeprom location register
INITEE_EE15	EQU	BIT7
INITEE_EE14	EQU	BIT6
INITEE_EE13	EQU	BIT5
INITEE_EE12	EQU	BIT4
INITEE_EEON	EQU	BIT0

MISC:           equ REGBASE+$13 ;miscellaneous mapping control
MISC_EXSTR1	EQU	BIT3
MISC_EXSTR0	EQU	BIT2
MISC_ROMHM	EQU	BIT1
MISC_ROMON	EQU	BIT0

MTST0:          equ REGBASE+$14 ; reserved

ITCR:           equ REGBASE+$15 ;interrupt test control register
ITCR_WRINT	EQU	BIT4
ITCR_ADR3	EQU	BIT3
ITCR_ADR2	EQU	BIT2
ITCR_ADR1	EQU	BIT1
ITCR_ADR0	EQU	BIT0

ITEST:          equ REGBASE+$16 ;interrupt test register
ITEST_INTE	EQU	BIT7	;THIS SEEMS TO CAUSE A CONFLICT SOMEWHERE
ITEST_INTC	EQU	BIT6
ITEST_INTA	EQU	BIT5
ITEST_INT8	EQU	BIT4
ITEST_INT6	EQU	BIT3
ITEST_INT4	EQU	BIT2
ITEST_INT2	EQU	BIT1
ITEST_INT0	EQU	BIT0

MTST1:          equ REGBASE+$17 ; reserved

PARTIDH:	equ REGBASE+$1a ;part id high
PARTIDL:	equ REGBASE+$1b ;part id low
PARTID:		EQU PARTIDH	;WORD ACCESS TO PARTID BYTES

MEMSIZ0:	equ REGBASE+$1c ;memory size
MEMSIZ1:	equ REGBASE+$1d ;memory size
MEMSIZ:		EQU MEMSIZ0	;WORD ACCESS

INTCR:          equ REGBASE+$1e ;interrupt control register
INTCR_IRQE	EQU	BIT7
INTCR_IRQEN	EQU	BIT6

HPRIO:          equ REGBASE+$1f ;high priority reg

#IF SYSTEM_CPU = C32 | SYSTEM_CPU = C128
DBGC1		EQU	REGBASE+$20
DBGSC		EQU	REGBASE+$21
DBGTBH		EQU	REGBASE+$22
DBGTBL		EQU	REGBASE+$23
DBGCNT		EQU	REGBASE+$24
DBGCCX		EQU	REGBASE+$25
DBGCCH		EQU	REGBASE+$26
DBGCCL		EQU	REGBASE+$27
DBGC2		EQU	REGBASE+$28
DBGC3		EQU	REGBASE+$29		
DBGCAX		EQU	REGBASE+$2A
DBGCAH		EQU	REGBASE+$2B
DBGCAL		EQU	REGBASE+$2C
DBGCBX		EQU	REGBASE+$2D
DBGCBH		EQU	REGBASE+$2E
DBGCBL		EQU	REGBASE+$2F
#ENDIF ;SYSTEM_CPU = C32 | SYSTEM_CPU = C128

BKPCT0:         equ REGBASE+$28 ;break control register
BKPCT1:         equ REGBASE+$29 ;break control register
BKP0X:          equ REGBASE+$2a ; break 0 index register
BKP0H:          equ REGBASE+$2b ; break 0 pointer high
BKP0L:          equ REGBASE+$2c ; break 0 pointer low
BKP1X:          equ REGBASE+$2d ; break 1 index register
BKP1H:          equ REGBASE+$2e ; break 1 pointer high
BKP1L:          equ REGBASE+$2f ; break 1 pointer low

PPAGE:		equ REGBASE+$30 ;program page register

PORTK:		equ REGBASE+$32 ;port k data
PTK:		equ PORTK
DDRK:		equ REGBASE+$33 ;port k direction


;*CRG

SYNR:           equ REGBASE+$34 ; synthesizer / multiplier register
SYNR_SYN5	EQU 	BIT5
SYNR_SYN4	EQU 	BIT4
SYNR_SYN3	EQU 	BIT3
SYNR_SYN2	EQU 	BIT2
SYNR_SYN1	EQU 	BIT1
SYNR_SYN0	EQU 	BIT0
REFDV:          equ REGBASE+$35 ; reference divider register
REFDV_REFDV3	EQU 	BIT3
REFDV_REFDV2	EQU 	BIT2
REFDV_REFDV1	EQU 	BIT1
REFDV_REFDV0	EQU 	BIT0
CTFLG:          equ REGBASE+$36 ; reserved
CRGFLG:         equ REGBASE+$37 ; pll flags register
CRGFLG_RTIF	EQU 	BIT7
CRGFLG_PORF	EQU 	BIT6
CRGFLG_LOCKIF	EQU 	BIT4
CRGFLG_LOCK	EQU 	BIT3
CRGFLG_TRACK	EQU 	BIT2
CRGFLG_SCMIF	EQU 	BIT1
CRGFLG_SCM	EQU 	BIT0
CRGINT:         equ REGBASE+$38 ; pll interrupt register
CRGINT_RTIE	EQU 	BIT7
CRGINT_LOCKIE	EQU 	BIT4
CRGINT_SCMIE	EQU 	BIT1
CLKSEL:         equ REGBASE+$39 ; clock select register
CLKSEL_PLLSEL	EQU 	BIT7
CLKSEL_PSTP	EQU 	BIT6
CLKSEL_SYSWAI	EQU 	BIT5
CLKSEL_ROAWAI	EQU 	BIT4
CLKSEL_PLLWAI	EQU 	BIT3
CLKSEL_CWAI	EQU 	BIT2
CLKSEL_RTIWAI	EQU 	BIT1
CLKSEL_COPWAI	EQU 	BIT0
PLLCTL:         equ REGBASE+$3a ; pll control register
PLLCTL_CME	EQU 	BIT7
PLLCTL_PLLON	EQU 	BIT6
PLLCTL_AUTO	EQU 	BIT5
PLLCTL_ACQ	EQU 	BIT4
PLLCTL_PRE	EQU 	BIT2
PLLCTL_PCE	EQU 	BIT1
PLLCTL_SCME	EQU 	BIT0
RTICTL:         equ REGBASE+$3b ;real time interrupt control
COPCTL:         equ REGBASE+$3c ;watchdog control
COPCTL_WCOP	EQU 	BIT7
COPCTL_RSBCK	EQU	BIT6
COPCTL_CR2	EQU	BIT2
COPCTL_CR1	EQU	BIT1
COPCTL_CR0	EQU	BIT0
FORBYP:         equ REGBASE+$3d ;RESERVED
CTCTL:          equ REGBASE+$3e ;RESERVED
ARMCOP:         equ REGBASE+$3f ;cop reset register

;*ECT

TIOS:           equ REGBASE+$40 ;timer input/output select
CFORC:          equ REGBASE+$41 ;timer compare force
OC7M:           equ REGBASE+$42 ;timer output compare 7 mask
OC7D:           equ REGBASE+$43 ;timer output compare 7 data
TCNT:           equ REGBASE+$44 ;timer counter register hi
*TCNT:          equ REGBASE+$45 ;timer counter register lo
TCNTH:          equ REGBASE+$44 ;timer counter register hi
TCNTL:          equ REGBASE+$45 ;timer counter register lo
TSCR:           equ REGBASE+$46 ;timer system control register
TSCR1:          equ TSCR 	;timer system control register
TSCR1_TEN	EQU	BIT7
TSCR1_TSWAI	EQU	BIT6
TSCR1_TSFRZ	EQU	BIT5
TSCR1_TFFCA	EQU	BIT4

TTOV:           equ REGBASE+$47 ;reserved
TCTL1:          equ REGBASE+$48 ;timer control register 1
TCTL1_OM7	EQU	BIT7
TCTL1_OL7	EQU	BIT6
TCTL1_OM6	EQU	BIT5
TCTL1_OL6	EQU	BIT4
TCTL1_OM5	EQU	BIT3
TCTL1_OL5	EQU	BIT2
TCTL1_OM4	EQU	BIT1
TCTL1_OL4	EQU	BIT0
TCTL2:          equ REGBASE+$49 ;timer control register 2
TCTL2_OM3	EQU	BIT7
TCTL2_OL3	EQU	BIT6
TCTL2_OM2	EQU	BIT5
TCTL2_OL2	EQU	BIT4
TCTL2_OM1	EQU	BIT3
TCTL2_OL1	EQU	BIT2
TCTL2_OM0	EQU	BIT1
TCTL2_OL0	EQU	BIT0
TCTL3:          equ REGBASE+$4a ;timer control register 3
TCTL3_EDG7B	EQU	BIT7
TCTL3_EDG7A	EQU	BIT6
TCTL3_EDG6B	EQU	BIT5
TCTL3_EDG6A	EQU	BIT4
TCTL3_EDG5B	EQU	BIT3
TCTL3_EDG5A	EQU	BIT2
TCTL3_EDG4B	EQU	BIT1
TCTL3_EDG4A	EQU	BIT0
TCTL4:          equ REGBASE+$4b ;timer control register 4
TCTL4_EDG3B	EQU	BIT7
TCTL4_EDG3A	EQU	BIT6
TCTL4_EDG2B	EQU	BIT5
TCTL4_EDG2A	EQU	BIT4
TCTL4_EDG1B	EQU	BIT3
TCTL4_EDG1A	EQU	BIT2
TCTL4_EDG0B	EQU	BIT1
TCTL4_EDG0A	EQU	BIT0
TMSK1:          equ REGBASE+$4c ;timer interrupt mask 1
TIE:            EQU TMSK1	
TMSK2:          equ REGBASE+$4d ;timer interrupt mask 2
TSCR2:          equ TMSK2
TSCR2_TOI	EQU	BIT7
TSCR2_TCRE	EQU	BIT3
TSCR2_PR2	EQU	BIT2
TSCR2_PR1	EQU	BIT1
TSCR2_PR0	EQU	BIT0
TFLG1:          equ REGBASE+$4e ;timer flags 1
TFLG2:          equ REGBASE+$4f ;timer flags 2
TFLG2_TOF	EQU	BIT7
TC0:            equ REGBASE+$50 ;timer capture/compare register 0
TC1:            equ REGBASE+$52 ;timer capture/compare register 1
TC2:            equ REGBASE+$54 ;timer capture/compare register 2
TC3:            equ REGBASE+$56 ;timer capture/compare register 3
TC4:            equ REGBASE+$58 ;timer capture/compare register 4
TC5:            equ REGBASE+$5a ;timer capture/compare register 5
TC6:            equ REGBASE+$5c ;timer capture/compare register 6
TC7:            equ REGBASE+$5e ;timer capture/compare register 7

PACTL:          equ REGBASE+$60 ;pulse accumulator controls
PACTL_PAEN	EQU	BIT6
PACTL_PAMOD	EQU	BIT5
PACTL_PEDGE	EQU	BIT4
PACTL_CLK1	EQU	BIT3
PACTL_CLK0	EQU	BIT2
PACTL_PAOVI	EQU	BIT1
PACTL_PAI	EQU	BIT0
PAFLG:          equ REGBASE+$61 ;pulse accumulator flags
PAFLG_PAOVF	EQU	BIT1
PAFLG_PAIF	EQU	BIT0

PACN3:          equ REGBASE+$62 ;pulse accumulator counter 3
PACN2:          equ REGBASE+$63 ;pulse accumulator counter 2
PACA:		equ PACN3	;Pulse Accumulator A is PACN3/PACN2 concatenated

#IF SYSTEM_CPU = C32 | SYSTEM_CPU = C128
PACNT		EQU	$0062		;PACN3 - HI BYTE
PACNTH		EQU	$0062		;PACN3 - HI BYTE
PACNTL		EQU	$0063		;PACN2 - LO BYTE
#ENDIF ;SYSTEM_CPU = C32 | SYSTEM_CPU = C128

#IF SYSTEM_CPU = DP256 | SYSTEM_CPU = DG256 | SYSTEM_CPU = DT256 | SYSTEM_CPU = DJ256
PACN1:          equ REGBASE+$64 ;pulse accumulator counter 1
PACN0:          equ REGBASE+$65 ;pulse accumulator counter 0

PACB:		equ PACN1	;Pulse Accumulator B is PACN1/PACN0 concatenated

MCCTL:          equ REGBASE+$66 ;modulus down conunter control
MCCTL_MCZI	EQU	BIT7
MCCTL_MODMC	EQU	BIT6
MCCTL_RDMCL	EQU	BIT5
MCCTL_ICLAT	EQU	BIT4
MCCTL_FLMC	EQU	BIT3
MCCTL_MCEN	EQU	BIT2
MCCTL_MCPR1	EQU	BIT1
MCCTL_MCPR0	EQU	BIT0
MCFLG:          equ REGBASE+$67 ;down counter flags
MCFLG_MCZF	EQU	BIT7
MCFLG_POLF3	EQU	BIT3
MCFLG_POLF2	EQU	BIT2
MCFLG_POLF1	EQU	BIT1
MCFLG_POLF0	EQU	BIT0
ICPAR:          equ REGBASE+$68 ;input pulse accumulator control
ICPAR_PA3EN	EQU	BIT3
ICPAR_PA2EN	EQU	BIT2
ICPAR_PA1EN	EQU	BIT1
ICPAR_PA0EN	EQU	BIT0
DLYCT:          equ REGBASE+$69 ;delay count to down counter
DLYCY_DLY1	EQU	BIT1
DLYCY_DLY0	EQU	BIT0
ICOVW:          equ REGBASE+$6a ;input control overwrite register
ICSYS:          equ REGBASE+$6b ;input control system control
ICSYS_SH37	EQU BIT7
ICSYS_SH26	EQU BIT6
ICSYS_SH15	EQU BIT5
ICSYS_SH04	EQU BIT4
ICSYS_TFMOD	EQU BIT3
ICSYS_PACMX	EQU BIT2
ICSYS_BUFEN	EQU BIT1
ICSYS_LATQ	EQU BIT0

TIMTST:         equ REGBASE+$6d ;timer test register
TIMTST_TCBYP	EQU	BIT1

PBCTL:          equ REGBASE+$70 ; pulse accumulator b control
PBCTL_PBEN	EQU	BIT6
PBCTL_PBOVI	EQU	BIT1
PBFLG:          equ REGBASE+$71 ; pulse accumulator b flags
PBFLG_PBOVF	EQU	BIT1
PA3H:           equ REGBASE+$72 ; pulse accumulator holding register 3
PA2H:           equ REGBASE+$73 ; pulse accumulator holding register 2
PA1H:           equ REGBASE+$74 ; pulse accumulator holding register 1
PA0H:           equ REGBASE+$75 ; pulse accumulator holding register 0

MCCNT:          equ REGBASE+$76 ; modulus down counter register
*MCCNTL:        equ REGBASE+$77 ; low byte
TCOH:           equ REGBASE+$78 ; capture 0 holding register
TC1H:           equ REGBASE+$7a ; capture 1 holding register
TC2H:           equ REGBASE+$7c ; capture 2 holding register
TC3H:           equ REGBASE+$7e ; capture 3 holding register
#ENDIF ;SYSTEM_CPU = DP256 | SYSTEM_CPU = DG256 | SYSTEM_CPU = DT256 | SYSTEM_CPU = DJ256

;*ATD (BITS GOOD FOR ALL ATD UNITS)

#IF SYSTEM_CPU = C32 | SYSTEM_CPU = C128
ATDCTL0		EQU	$0080		;ATDCTL0 - RESERVED
ATDCTL1		EQU	$0081		;ATDCTL1 - RESERVED
ATDCTL2		EQU	$0082		;ATDCTL2 - ATD CONTROL REGISTER
ATDCTL3		EQU	$0083		;ATDCTL3 - ATD CONTROL REGISTER
ATDCTL4		EQU	$0084		;ATDCTL4 - ATD CONTROL REGISTER
ATDCTL5		EQU	$0085		;ATDCTL5 - ATD CONTROL REGISTER

ATDTEST0	EQU	$0088	;ATDTEST
ATDTEST1	EQU	$0089	;ATDTEST

ATDDIEN1	EQU	$8D
ATDDIEN		EQU	$8D

ATDDR0H		EQU	$0090
ATDDR0L		EQU	$0091
ATDDR1H		EQU	$0092
ATDDR1L		EQU	$0093
ATDDR2H		EQU	$0094
ATDDR2L		EQU	$0095
ATDDR3H		EQU	$0096
ATDDR3L		EQU	$0097
ATDDR4H		EQU	$0098
ATDDR4L		EQU	$0099
ATDDR5H		EQU	$009A
ATDDR5L		EQU	$009B
ATDDR6H		EQU	$009C
ATDDR6L		EQU	$009D
ATDDR7H		EQU	$009E
ATDDR7L		EQU	$009F
#ENDIF ;SYSTEM_CPU = C32 | SYSTEM_CPU = C128


ATD0CTL0:       equ REGBASE+$80 ;adc control 0 (reserved)
ATD0CTL1:       equ REGBASE+$81 ;adc control 1 (reserved)
ATD0CTL2:       equ REGBASE+$82 ;adc control 2
ATD_ADPU	EQU	BIT7
ATD_AFFC	EQU	BIT6
ATD_AWAI	EQU	BIT5
ATD_ETRIGLE	EQU	BIT4
ATD_ETRIGP	EQU	BIT3
ATD_ETRIGE	EQU	BIT2
ATD_ASCIE	EQU	BIT1
ATD_ASCIF	EQU	BIT0
ATD0CTL3:       equ REGBASE+$83 ;adc control 3
ATD_S8C		EQU	BIT6
ATD_S4C		EQU	BIT5
ATD_S2C		EQU	BIT4
ATD_S1C		EQU	BIT3
ATD_FIFO	EQU	BIT2
ATD_FRZ1	EQU	BIT1
ATD_FRZ0	EQU	BIT0
ATD0CTL4:       equ REGBASE+$84 ;adc control 4
ATD_SRES8	EQU	BIT7
ATD_SMP1	EQU	BIT6
ATD_SMP0	EQU	BIT5
ATD_PRS4	EQU	BIT4
ATD_PRS3	EQU	BIT3
ATD_PRS2	EQU	BIT2
ATD_PRS1	EQU	BIT1
ATD_PRS0	EQU	BIT0
ATD0CTL5:       equ REGBASE+$85 ;adc control 5
ATD_DJM		EQU	BIT7
ATD_DSGN	EQU	BIT6
ATD_SCAN	EQU	BIT5
ATD_MULT	EQU	BIT4
ATD_CC		EQU	BIT2
ATD_CB		EQU	BIT1
ATD_CA		EQU	BIT0
ATD0STAT:       equ REGBASE+$86 ;adc status register hi
ATD0STAT0:	equ ATD0STAT
ATD_SCF		EQU	BIT7
ATD_ETORF	EQU	BIT5
ATD_FIFOR	EQU	BIT4
ATD_CC2		EQU	BIT2
ATD_CC1		EQU	BIT1
ATD_CC0		EQU	BIT0
*atd0stat       equ REGBASE+$87 ;adc status register lo
ATD0STAT1	equ ATD0STAT+1
ATD_CCF7	EQU	BIT7
ATD_CCF6	EQU	BIT6
ATD_CCF5	EQU	BIT5
ATD_CCF4	EQU	BIT4
ATD_CCF3	EQU	BIT3
ATD_CCF2	EQU	BIT2
ATD_CCF1	EQU	BIT1
ATD_CCF0	EQU	BIT0
ATD0TEST:       equ REGBASE+$88 ;adc test (reserved)
*atd0test       equ REGBASE+$89 ;low-half of 16-bit atd0test
ATD0DIEN:	equ REGBASE+$8d ;
#IF SYSTEM_CPU = DP256 | SYSTEM_CPU = DG256 | SYSTEM_CPU = DT256 | SYSTEM_CPU = DJ256
PORTAD:         equ REGBASE+$8f 
#ENDIF ;SYSTEM_CPU = DP256 | SYSTEM_CPU = DG256 | SYSTEM_CPU = DT256 | SYSTEM_CPU = DJ256
PORTAD0:        EQU REGBASE+$8f;port adc = input only
ADR00H:         equ REGBASE+$90 ;adc result 0 register
ADR01H:         equ REGBASE+$92 ;adc result 1 register
ADR02H:         equ REGBASE+$94 ;adc result 2 register
ADR03H:         equ REGBASE+$96 ;adc result 3 register
ADR04H:         equ REGBASE+$98 ;adc result 4 register
ADR05H:         equ REGBASE+$9a ;adc result 5 register
ADR06H:         equ REGBASE+$9c ;adc result 6 register
ADR07H:         equ REGBASE+$9e ;adc result 7 register

#IF SYSTEM_CPU = DP256 | SYSTEM_CPU = DG256 | SYSTEM_CPU = DT256 | SYSTEM_CPU = DJ256
;*PWM

PWME:		equ REGBASE+$a0 ;pwm enable
PWMPOL:         equ REGBASE+$a1 ;pwm polarity
PWMCLK:         equ REGBASE+$a2 ;pwm clock select register
PWMPRCLK:       equ REGBASE+$a3 ;pwm prescale clock select register
PWM_PCKB2	EQU	BIT6
PWM_PCKB1	EQU	BIT5
PWM_PCKB0	EQU	BIT4
PWM_PCKA2	EQU	BIT2
PWM_PCKA1	EQU	BIT1
PWM_PCKA0	EQU	BIT0
PWMCAE:         equ REGBASE+$a4 ;pwm center align select register
PWMCTL:         equ REGBASE+$a5 ;pwm control register
PWM_CON67	EQU	BIT7
PWM_CON45	EQU	BIT6
PWM_CON23	EQU	BIT5
PWM_CON01	EQU	BIT4
PWM_PSWAI	EQU	BIT3
PWM_PFRZ	EQU	BIT2
PWMTST:         equ REGBASE+$a6 ;reserved
PWMPRSC:        equ REGBASE+$a7 ;reserved
PWMSCLA:        equ REGBASE+$a8 ;pwm scale a
PWMSCLB:        equ REGBASE+$a9 ;pwm scale b
PWMSCNTA:       equ REGBASE+$aa ;reserved
PWMSCNTB:       equ REGBASE+$ab ;reserved
PWMCNT0:        equ REGBASE+$ac ;pwm channel 0 counter
PWMCNT1:        equ REGBASE+$ad ;pwm channel 1 counter
PWMCNT2:        equ REGBASE+$ae ;pwm channel 2 counter
PWMCNT3:        equ REGBASE+$af ;pwm channel 3 counter
PWMCNT4:        equ REGBASE+$b0 ;pwm channel 4 counter
PWMCNT5:        equ REGBASE+$b1 ;pwm channel 5 counter
PWMCNT6:        equ REGBASE+$b2 ;pwm channel 6 counter
PWMCNT7:        equ REGBASE+$b3 ;pwm channel 7 counter
PWMPER0:        equ REGBASE+$b4 ;pwm channel 0 period
PWMPER1:        equ REGBASE+$b5 ;pwm channel 1 period
PWMPER2:        equ REGBASE+$b6 ;pwm channel 2 period
PWMPER3:        equ REGBASE+$b7 ;pwm channel 3 period
PWMPER4:        equ REGBASE+$b8 ;pwm channel 4 period
PWMPER5:        equ REGBASE+$b9 ;pwm channel 5 period
PWMPER6:        equ REGBASE+$ba ;pwm channel 6 period
PWMPER7:        equ REGBASE+$bb ;pwm channel 7 period
PWMDTY0:        equ REGBASE+$bc ;pwm channel 0 duty cycle
PWMDTY1:        equ REGBASE+$bd ;pwm channel 1 duty cycle
PWMDTY2:        equ REGBASE+$be ;pwm channel 2 duty cycle
PWMDTY3:        equ REGBASE+$bf ;pwm channel 3 duty cycle
PWMDTY4:        equ REGBASE+$c0 ;pwm channel 0 duty cycle
PWMDTY5:        equ REGBASE+$c1 ;pwm channel 1 duty cycle
PWMDTY6:        equ REGBASE+$c2 ;pwm channel 2 duty cycle
PWMDTY7:        equ REGBASE+$c3 ;pwm channel 3 duty cycle
PWMSDN:         equ REGBASE+$c4 ;pwm shutdown register
PWM_PWMIF	EQU	BIT7
PWM_PWMIE	EQU	BIT6
PWM_PWMRSTRT	EQU	BIT5
PWM_PWMLVL	EQU	BIT4
PWM_PWM7IN	EQU	BIT2
PWM_PWM7INL	EQU	BIT1
PWM_PWM7ENA	EQU	BIT0

#ENDIF ;SYSTEM_CPU = DP256 | SYSTEM_CPU = DG256 | SYSTEM_CPU = DT256 | SYSTEM_CPU = DJ256

;*SCI (BITS GOOD FOR ALL SCI UNITS)

SC0BDH:         equ REGBASE+$c8 ;sci 0 baud reg hi byte
SC0BDL:         equ REGBASE+$c9 ;sci 0 baud reg lo byte
SC0BAUD:	EQU 	SC0BDH
SCI_BDH_SBR12	EQU 	BIT4	;BAUD BITS IN UPPER BYTE ONLY
SCI_BDH_SBR11	EQU 	BIT3
SCI_BDH_SBR10	EQU 	BIT2
SCI_BDH_SBR9	EQU 	BIT1
SCI_BDH_SBR8	EQU 	BIT0
SCI_SBR12	EQU 	BIT12	;ALL SCI BAUD BITS FROM 16-BIT WORD
SCI_SBR11	EQU 	BIT11
SCI_SBR10	EQU 	BIT10
SCI_SBR9	EQU 	BIT9
SCI_SBR8	EQU 	BIT8
SCI_SBR7	EQU 	BIT7
SCI_SBR6	EQU 	BIT6
SCI_SBR5	EQU 	BIT5
SCI_SBR4	EQU 	BIT4
SCI_SBR3	EQU 	BIT3
SCI_SBR2	EQU 	BIT2
SCI_SBR1	EQU 	BIT1
SCI_SBR0	EQU 	BIT0
SC0CR1:         equ REGBASE+$ca ;sci 0 control1 reg
SCI_LOOPS	EQU	BIT7
SCI_SCISWAI	EQU	BIT6
SCI_RSRC	EQU	BIT5
SCI_M		EQU	BIT4
SCI_WAKE	EQU	BIT3
SCI_ILT		EQU	BIT2
SCI_PE		EQU	BIT1
SCI_PT		EQU	BIT0
SC0CR2:         equ REGBASE+$cb ;sci 0 control2 reg
SCI_TIE		EQU	BIT7
SCI_TCIE	EQU	BIT6
SCI_RIE		EQU	BIT5
SCI_ILIE	EQU	BIT4
SCI_TE		EQU	BIT3
SCI_RE		EQU	BIT2
SCI_RWU		EQU	BIT1
SCI_SBK		EQU	BIT0
SC0SR1:         equ REGBASE+$cc ;sci 0 status reg 1
SCI_TDRE	EQU	BIT7
SCI_TC		EQU	BIT6
SCI_RDRF	EQU	BIT5
SCI_IDLE	EQU	BIT4
SCI_OR		EQU	BIT3
SCI_NF		EQU	BIT2
SCI_FE		EQU	BIT1
SCI_PF		EQU	BIT0
SC0SR2:         equ REGBASE+$cd ;sci 0 status reg 2
SCI_BRK13	EQU	BIT2
SCI_TXDIR	EQU	BIT1
SCI_RAF		EQU	BIT0
SC0DRH:         equ REGBASE+$ce ;sci 0 data reg hi
SC0DRL:         equ REGBASE+$cf ;sci 0 data reg lo
SCI_R8		EQU	BIT7
SCI_T8		EQU	BIT6

SCI0BDH:        equ REGBASE+$c8 ;sci 0 baud reg hi byte
SCI0BDL:        equ REGBASE+$c9 ;sci 0 baud reg lo byte
SCI0CR1:        equ REGBASE+$ca ;sci 0 control1 reg
SCI0CR2:        equ REGBASE+$cb ;sci 0 control2 reg
SCI0SR1:        equ REGBASE+$cc ;sci 0 status reg 1
SCI0SR2:        equ REGBASE+$cd ;sci 0 status reg 2
SCI0DRH:        equ REGBASE+$ce ;sci 0 data reg hi
SCI0DRL:        equ REGBASE+$cf ;sci 0 data reg lo
SCI0BAUD:	EQU SCI0BDH	;16-BIT
SCI0CONTROL	EQU SCI0CR1	;16-BIT
SCI0STATUS 	EQU SCI0SR1	;16-BIT
SCI0DATA	EQU SCI0DRH	;16-BIT

#IF SYSTEM_CPU = C32 | SYSTEM_CPU = C128
;SCI - Asynchronous Serial Interface
SCIBDH		EQU	$00C8		;SCI0BDH - SCI BAUD RATE CONTROL REGISTER
SCIBDL		EQU	$00C9		;SCI0BDL - SCI BAUD RATE CONTROL REGISTER
SCICR1		EQU	$00CA		;SCI0CR1 - SCI CONTROL REGISTER
SCICR2		EQU	$00CB		;SCI0CR2 - SCI CONTROL REGISTER
SCISR1		EQU	$00CC		;SCI0SR1 - SCI STATUS REGISTER
SCISR2		EQU	$00CD		;SCI0SR2 - SCI STATUS REGISTER
SCIDRH		EQU	$00CE		;SCI0DRH - SCI DATA REGISTER
SCIDRL		EQU	$00CF		;SCI0DRL - SCI DATA REGISTER
#ENDIF ;SYSTEM_CPU = C32 | SYSTEM_CPU = C128

#IF SYSTEM_CPU = DP256 | SYSTEM_CPU = DG256 | SYSTEM_CPU = DT256 | SYSTEM_CPU = DJ256

SC1BDH:         equ REGBASE+$d0 ;sci 1 baud reg hi byte
SC1BDL:         equ REGBASE+$d1 ;sci 1 baud reg lo byte
SC1CR1:         equ REGBASE+$d2 ;sci 1 control1 reg
SC1CR2:         equ REGBASE+$d3 ;sci 1 control2 reg
SC1SR1:         equ REGBASE+$d4 ;sci 1 status reg 1
SC1SR2:         equ REGBASE+$d5 ;sci 1 status reg 2
SC1DRH:         equ REGBASE+$d6 ;sci 1 data reg hi
SC1DRL:         equ REGBASE+$d7 ;sci 1 data reg lo

SCI1BDH:        equ REGBASE+$d0 ;sci 1 baud reg hi byte
SCI1BDL:        equ REGBASE+$d1 ;sci 1 baud reg lo byte
SCI1CR1:        equ REGBASE+$d2 ;sci 1 control1 reg
SCI1CR2:        equ REGBASE+$d3 ;sci 1 control2 reg
SCI1SR1:        equ REGBASE+$d4 ;sci 1 status reg 1
SCI1SR2:        equ REGBASE+$d5 ;sci 1 status reg 2
SCI1DRH:        equ REGBASE+$d6 ;sci 1 data reg hi
SCI1DRL:        equ REGBASE+$d7 ;sci 1 data reg lo
SCI1BAUD:	EQU SCI1BDH	;16-BIT
SCI1CONTROL	EQU SCI1CR1	;16-BIT
SCI1STATUS 	EQU SCI1SR1	;16-BIT
SCI1DATA	EQU SCI1DRH	;16-BIT
#ENDIF ;SYSTEM_CPU = DP256 | SYSTEM_CPU = DG256 | SYSTEM_CPU = DT256 | SYSTEM_CPU = DJ256

;*SPI (BITS GOOD FOR ALL SPI UNITS)

SPI0CR1:        equ REGBASE+$d8 ;spi 0 control1 reg
SPI_SPIE	EQU	BIT7
SPI_SPE		EQU	BIT6
SPI_SPTIE	EQU	BIT5
SPI_MSTR	EQU	BIT4
SPI_CPOL	EQU	BIT3
SPI_CPHA	EQU	BIT2
SPI_SSOE	EQU	BIT1
SPI_LSBFE	EQU	BIT0
SPI0CR2:        equ REGBASE+$d9 ;spi 0 control2 reg
SPI_MODFEN	EQU	BIT4
SPI_BIDIROE	EQU	BIT3
SPI_SPISWAI	EQU	BIT1
SPI_SPC0	EQU	BIT0
SPI0BR:         equ REGBASE+$da ;spi 0 baud reg
SPI_SPPR2	EQU	BIT6
SPI_SPPR1	EQU	BIT5
SPI_SPPR0	EQU	BIT4
SPI_SPR2	EQU	BIT2
SPI_SPR1	EQU	BIT1
SPI_SPR0	EQU	BIT0
SPI0SR:         equ REGBASE+$db ;spi 0 status reg hi
SPI_SPIF	EQU	BIT7
SPI_SPTEF	EQU	BIT5
SPI_MODF	EQU	BIT4
SPI0DR:         equ REGBASE+$dd ;spi 0 data reg
SP0DR:          equ REGBASE+$dd ;spi 0 data reg

;NOTE: SPI1 AND SPI2 DEFINED LATER IN MEMORY

#IF SYSTEM_CPU = C32 | SYSTEM_CPU = C128
;SPI - Serial Peripheral Interface
SPICR1		EQU	$00D8		;SPI0CR1 - SPI CONTROL REGISTER
SPICR2		EQU	$00D9		;SPI0CR2 - SPI CONTROL REGISTER
SPIBR		EQU	$00DA		;SPI0BR - SPI BAUD RATE REGISTER
SPISR		EQU	$00DB		;SPI0SR - SPI STATUS REGISTER
SPIDR		EQU	$00DD		;SPI0DR - SPI DATA REGISTER
#ENDIF ;SYSTEM_CPU = C32 | SYSTEM_CPU = C128


#IF SYSTEM_CPU = C32 | SYSTEM_CPU = C128
;PWM (Pulse width Modulator)
PWME		EQU	$E0	
PWMPOL		EQU	$E1
PWMCLK		EQU	$E2
PWMPRCLK	EQU	$E3
PWM_PCKB2	EQU	BIT6
PWM_PCKB1	EQU	BIT5
PWM_PCKB0	EQU	BIT4
PWM_PCKA2	EQU	BIT2
PWM_PCKA1	EQU	BIT1
PWM_PCKA0	EQU	BIT0

PWMCAE		EQU	$E4
PWMCTL		EQU	$E5
PWM_CON67	EQU	BIT7
PWM_CON45	EQU	BIT6
PWM_CON23	EQU	BIT5
PWM_CON01	EQU	BIT4
PWM_PSWAI	EQU	BIT3
PWM_PFRZ	EQU	BIT2

PWMTST		EQU	$E6
PWMPRSC		EQU	$E7
PWMSCLA		EQU	$E8
PWMSCLB		EQU	$E9
PWMSCNTA	EQU	$EA
PWMSCNTB	EQU	$EB

PWMCNT0		EQU	$EC
PWMCNT1		EQU	$ED
PWMCNT2		EQU	$EE
PWMCNT3		EQU	$EF
PWMCNT4		EQU	$F0
PWMCNT5		EQU	$F1

PWMPER0		EQU	$F2
PWMPER1		EQU	$F3
PWMPER2		EQU	$F4
PWMPER3		EQU	$F5
PWMPER4		EQU	$F6
PWMPER5		EQU	$F7

PWMDTY0		EQU	$F8
PWMDTY1		EQU	$F9
PWMDTY2		EQU	$FA
PWMDTY3		EQU	$FB
PWMDTY4		EQU	$FC
PWMDTY5		EQU	$FD
;reserveD	EQU	$FE
#ENDIF ;SYSTEM_CPU = C32 | SYSTEM_CPU = C128

#IF SYSTEM_CPU = DP256 | SYSTEM_CPU = DG256 | SYSTEM_CPU = DT256 | SYSTEM_CPU = DJ256
;*IIC

IBAD:		equ REGBASE+$e0 ;i2c bus address register
IBFD:		equ REGBASE+$e1 ;i2c bus frequency divider
IBCR:		equ REGBASE+$e2 ;i2c bus control register
IIC_IBEN	EQU	BIT7
IIC_IBIE	EQU	BIT6
IIC_MSSL	EQU	BIT5
IIC_TXRX	EQU	BIT4
IIC_TXAK	EQU	BIT3
IIC_RSTA	EQU	BIT2
IIC_IBSWAI	EQU	BIT0
IBSR:		equ REGBASE+$e3 ;i2c bus status register
IIC_TCF		EQU	BIT7
IIC_IAAS	EQU	BIT6
IIC_IBB		EQU	BIT5
IIC_IBAL	EQU	BIT4
IIC_SRW		EQU	BIT2
IIC_IBIF	EQU	BIT1
IIC_RXAK	EQU	BIT0
IBDR:		equ REGBASE+$e4 ;i2c bus message data register
#ENDIF ;SYSTEM_CPU = DP256 | SYSTEM_CPU = DG256 | SYSTEM_CPU = DT256 | SYSTEM_CPU = DJ256


#IF SYSTEM_CPU = DP256 | SYSTEM_CPU = DJ256 
;* BDLC

DLCBCR1:	equ REGBASE+$e8 ;bdlc control regsiter 1
DLCBCR1_IMSG	EQU	BIT7
DLCBCR1_CLKS	EQU	BIT6	
DLCBCR1_IE	EQU	BIT1
DLCBCR1_WCM	EQU	BIT0
DLCBSVR:	equ REGBASE+$e9 ;bdlc state vector register
DLCBCR2:	equ REGBASE+$ea ;bdlc control register 2
DLCBCR2_SMRST	EQU	BIT7
DLCBCR2_DLOOP	EQU	BIT6
DLCBCR2_RX4XE	EQU	BIT5
DLCBCR2_NBFS	EQU	BIT4
DLCBCR2_TEOD	EQU	BIT3
DLCBCR2_TSIFR	EQU	BIT2
DLCBCR2_TMIFR1	EQU	BIT1
DLCBCR2_TMIFR0	EQU	BIT0
DLCBDR:		equ REGBASE+$eb ;bdlc data register
DLCBARD:	equ REGBASE+$ec ;bdlc analog delay register
DLCBARD_RXPOL	EQU	BIT6
DLCBARD_BO3	EQU	BIT3
DLCBARD_BO2	EQU	BIT2
DLCBARD_BO1	EQU	BIT1
DLCBARD_BO0	EQU	BIT0
DLCBRSR:	equ REGBASE+$ed ;bdlc rate select register
DLCSCR:		equ REGBASE+$ee ;bdlc control register
DLCSCR_BDLCE	EQU	BIT4
DLCBSTAT:	equ REGBASE+$ef ;bdlc status register
DLCBSTAT_IDLE	EQU	BIT0
#ENDIF ;SYSTEM_CPU = DP256 | SYSTEM_CPU = DJ256 

#IF SYSTEM_CPU = DP256 | SYSTEM_CPU = DG256 | SYSTEM_CPU = DT256 | SYSTEM_CPU = DJ256
;* SPI (SEE SPI0 FOR BIT DEFINITIONS)

SPI1CR1:        equ REGBASE+$f0 ;spi 1 control1 reg
SPI1CR2:        equ REGBASE+$f1 ;spi 1 control2 reg
SPI1BR:         equ REGBASE+$f2 ;spi 1 baud reg
SPI1SR:         equ REGBASE+$f3 ;spi 1 status reg hi
SPI1DR:         equ REGBASE+$f5 ;spi 1 data reg
SP1DR:          equ REGBASE+$f5 ;spi 1 data reg

SPI2CR1:        equ REGBASE+$f8 ;spi 2 control1 reg
SPI2CR2:        equ REGBASE+$f9 ;spi 2 control2 reg
SPI2BR:         equ REGBASE+$fa ;spi 2 baud reg
SPI2SR:         equ REGBASE+$fb ;spi 2 status reg hi
SPI2DR:         equ REGBASE+$fd ;spi 2 data reg
SP2DR:          equ REGBASE+$fd ;spi 2 data reg
#ENDIF ;SYSTEM_CPU = DP256 | SYSTEM_CPU = DG256 | SYSTEM_CPU = DT256 | SYSTEM_CPU = DJ256


;* 256 kbyte FLASH

FCLKDIV:	equ REGBASE+$100 ;flash clock divider
FCLKDIV_FDIVLD	EQU	BIT7
FCLKDIV_PRDIV8	EQU	BIT6
FCLKDIV_FDIV5	EQU	BIT5
FCLKDIV_FDIV4	EQU	BIT4
FCLKDIV_FDIV3	EQU	BIT3
FCLKDIV_FDIV2	EQU	BIT2
FCLKDIV_FDIV1	EQU	BIT1
FCLKDIV_FDIV0	EQU	BIT0
FSEC:		equ REGBASE+$101 ;flash security register
FSEC_KEYEN	EQU	BIT7
FSEC_NV4	EQU	BIT6
FSEC_NV3	EQU	BIT5
FSEC_NV2	EQU	BIT4
FSEC_NV1	EQU	BIT3
FSEC_NV0	EQU	BIT2
FSEC_SEC1 	EQU	BIT1
FSEC_SEC0 	EQU	BIT0
FCNFG:		equ REGBASE+$103 ;flash configuration register
FCNFG_CBEIE	EQU	BIT7
FCNFG_CCIE	EQU	BIT6
FCNFG_KEYACC	EQU	BIT5
FCNFG_BKSEL1	EQU	BIT1
FCNFG_BKSEL0	EQU	BIT0
FPROT:		equ REGBASE+$104 ;flash protection register
FPROT_FPOPEN	EQU	BIT7
FPROT_NV6	EQU	BIT6
FPROT_FPHDIS	EQU	BIT5
FPROT_FPHS1	EQU	BIT4
FPROT_FPHS0	EQU	BIT3
FPROT_FPLDIS	EQU	BIT2
FPROT_FPLS1	EQU	BIT1
FPROT_FPLS0	EQU	BIT0
FSTAT:		equ REGBASE+$105 ;flash status register
FSTAT_CBEIF	EQU	BIT7
FSTAT_CCIF	EQU	BIT6
FSTAT_PVIOL	EQU	BIT5
FSTAT_ACCERR	EQU	BIT4
FSTAT_BLANK	EQU	BIT2
FCMD:		equ REGBASE+$106 ;flash command register
FCMD_CMDB6	EQU	BIT6
FCMD_CMDB5	EQU	BIT5
FCMD_CMDB2	EQU	BIT2
FCMD_CMDB0	EQU	BIT0


#IF SYSTEM_CPU = DP256 | SYSTEM_CPU = DG256 | SYSTEM_CPU = DT256 | SYSTEM_CPU = DJ256
;* 4 kbyte EEPROM

ECLKDIV:	equ REGBASE+$110 ;eeprom clock divider
ECLKDIV_EDIVLD	EQU	BIT7
ECLKDIV_PRDIV8	EQU	BIT6
ECLKDIV_EDIV5	EQU	BIT5
ECLKDIV_EDIV4	EQU	BIT4
ECLKDIV_EDIV3	EQU	BIT3
ECLKDIV_EDIV2	EQU	BIT2
ECLKDIV_EDIV1	EQU	BIT1
ECLKDIV_EDIV0	EQU	BIT0
ECNFG:		equ REGBASE+$113 ;eeprom configuration register
ECNFG_CBEIE	EQU	BIT7
ECNFG_CCIE	EQU	BIT6
EPROT:		equ REGBASE+$114 ;eeprom protection register
EPROT_EPOPEN	EQU 	BIT7
EPROT_NV6	EQU 	BIT6
EPROT_NV5	EQU 	BIT5
EPROT_NV4	EQU 	BIT4
EPROT_EPDIS	EQU 	BIT3
EPROT_EP2	EQU 	BIT2
EPROT_EP1	EQU 	BIT1
EPROT_EP0	EQU 	BIT0
ESTAT:		equ REGBASE+$115 ;eeprom status register
ESTAT_CBEIF	EQU	BIT7
ESTAT_CCIF	EQU	BIT6
ESTAT_PVIOL	EQU	BIT5
ESTAT_ACCERR	EQU	BIT4
ESTAT_BLANK	EQU	BIT2
ECMD:		equ REGBASE+$116 ;eeprom command register
ECMD_CMDB6	EQU	BIT6
ECMD_CMDB5	EQU	BIT5
ECMD_CMDB2	EQU	BIT2
ECMD_CMDB0	EQU	BIT0
#ENDIF ;SYSTEM_CPU = DP256 | SYSTEM_CPU = DG256 | SYSTEM_CPU = DT256 | SYSTEM_CPU = DJ256


#IF SYSTEM_CPU = DP256 | SYSTEM_CPU = DG256 | SYSTEM_CPU = DT256 | SYSTEM_CPU = DJ256
;*ATD (SEE ATD0 FOR BIT DEFINITIONS)

ATD1CTL0:       equ REGBASE+$120 ;adc1 control 0 (reserved)
ATD1CTL1:       equ REGBASE+$121 ;adc1 control 1 (reserved)
ATD1CTL2:       equ REGBASE+$122 ;adc1 control 2
ATD1CTL3:       equ REGBASE+$123 ;adc1 control 3
ATD1CTL4:       equ REGBASE+$124 ;adc1 control 4
ATD1CTL5:       equ REGBASE+$125 ;adc1 control 5
ATD1STAT:       equ REGBASE+$126 ;adc1 status register hi
ATD1STAT0	equ ATD1STAT
ATD1STAT1	equ ATD1STAT+1
*atd1stat       equ REGBASE+$127 ;adc1 status register lo
ATD1TEST:       equ REGBASE+$128 ;adc1 test (reserved)
*atd1test       equ REGBASE+$129 ;
ATDDIEN:	equ REGBASE+$12d ;adc1 input enable register
ATD1DIEN:	equ REGBASE+$12d ;adc1 input enable register
PORTAD1:        equ REGBASE+$12f ;port adc1 = input only
ADR10H:         equ REGBASE+$130 ;adc1 result 0 register
ADR11H:         equ REGBASE+$132 ;adc1 result 1 register
ADR12H:         equ REGBASE+$134 ;adc1 result 2 register
ADR13H:         equ REGBASE+$136 ;adc1 result 3 register
ADR14H:         equ REGBASE+$138 ;adc1 result 4 register
ADR15H:         equ REGBASE+$13a ;adc1 result 5 register
ADR16H:         equ REGBASE+$13c ;adc1 result 6 register
ADR17H:         equ REGBASE+$13e ;adc1 result 7 register
#ENDIF ;SYSTEM_CPU = DP256 | SYSTEM_CPU = DG256 | SYSTEM_CPU = DT256 | SYSTEM_CPU = DJ256


;* CAN (BITS GOOD FOR ALL CAN UNITS)

CAN0CTL0:	equ REGBASE+$140 ;can0 control register 0
CAN_CTL0_RXFRM	EQU	BIT7
CAN_CTL0_RXACT	EQU	BIT6
CAN_CTL0_CSWAI	EQU	BIT5
CAN_CTL0_SYNCH	EQU	BIT4
CAN_CTL0_TIME	EQU	BIT3
CAN_CTL0_WUPE	EQU	BIT2
CAN_CTL0_SLPRQ	EQU	BIT1
CAN_CTL0_INITRQ	EQU	BIT0
CAN0CTL1:	equ REGBASE+$141 ;can0 control register 1
CAN_CTL1_CANE	EQU	BIT7
CAN_CTL1_CLKSRC	EQU	BIT6
CAN_CTL1_LOOPB	EQU	BIT5
CAN_CTL1_LISTEN	EQU	BIT4
CAN_CTL1_WUPM	EQU	BIT2
CAN_CTL1_SLPAK	EQU	BIT1
CAN_CTL1_INITAK	EQU	BIT0
CAN0BTR0:	equ REGBASE+$142 ;can0 bus timing register 0
CAN_BTR0_SJW1	EQU	BIT7
CAN_BTR0_SJW0	EQU	BIT6
CAN_BTR0_BRP5	EQU	BIT5
CAN_BTR0_BRP4	EQU	BIT4
CAN_BTR0_BRP3	EQU	BIT3
CAN_BTR0_BRP2	EQU	BIT2
CAN_BTR0_BRP1	EQU	BIT1
CAN_BTR0_BRP0	EQU	BIT0
CAN0BTR1:	equ REGBASE+$143 ;can0 bus timing register 1
CAN_BTR1_SAMP	EQU	BIT7
CAN_BTR1_TSEG22	EQU	BIT6
CAN_BTR1_TSEG21	EQU	BIT5
CAN_BTR1_TSEG20	EQU	BIT4
CAN_BTR1_TSEG13	EQU	BIT3
CAN_BTR1_TSEG12	EQU	BIT2
CAN_BTR1_TSEG11	EQU	BIT1
CAN_BTR1_TSEG10	EQU	BIT0
CAN0RFLG:	equ REGBASE+$144 ;can0 receiver flags
CAN_RFLG_WUPIF	EQU	BIT7
CAN_RFLG_CSCIF	EQU	BIT6
CAN_RFLG_RSTAT1	EQU	BIT5
CAN_RFLG_RSTAT0	EQU	BIT4
CAN_RFLG_TSTAT1	EQU	BIT3
CAN_RFLG_TSTAT0	EQU	BIT2
CAN_RFLG_OVRIF	EQU	BIT1
CAN_RFLG_RXF	EQU	BIT0
CAN0RIER:	equ REGBASE+$145 ;can0 receiver interrupt enables
CAN_RIER_WUPIE	EQU	BIT7
CAN_RIER_CSCIE	EQU	BIT6
CAN_RIER_RSTATE1	EQU	BIT5
CAN_RIER_RSTATE0	EQU	BIT4
CAN_RIER_TSTATE1	EQU	BIT3
CAN_RIER_TSTATE0	EQU	BIT2
CAN_RIER_OVRIE	EQU	BIT1
CAN_RIER_RXFIE	EQU	BIT0
CAN0TFLG:	equ REGBASE+$146 ;can0 transmit flags
CAN_TFLG_TXE2	EQU	BIT2
CAN_TFLG_TXE1	EQU	BIT1
CAN_TFLG_TXE0	EQU	BIT0
CAN0TIER:	equ REGBASE+$147 ;can0 transmit interrupt enables
CAN_TIER_TXEIE2	EQU	BIT2
CAN_TIER_TXEIE1	EQU	BIT1
CAN_TIER_TXEIE0	EQU	BIT0
CAN0TARQ:	equ REGBASE+$148 ;can0 transmit message abort control
CAN_TARQ_ABTRQ2	EQU	BIT2
CAN_TARQ_ABTRQ1	EQU	BIT1
CAN_TARQ_ABTRQ0	EQU	BIT0
CAN0TAAK:	equ REGBASE+$149 ;can0 transmit message abort status
CAN_TAAK_ABTAK2	EQU	BIT2
CAN_TAAK_ABTAK1	EQU	BIT1
CAN_TAAK_ABTAK0	EQU	BIT0
CAN0TBSEL:	equ REGBASE+$14a ;can0 transmit buffer select
CAN_TBSEL_TX2	EQU	BIT2
CAN_TBSEL_TX1	EQU	BIT1
CAN_TBSEL_TX0	EQU	BIT0
CAN0IDAC:	equ REGBASE+$14b ;can0 identfier acceptance control
CAN_IDAC_IDAM1	EQU	BIT5
CAN_IDAC_IDAM0	EQU	BIT4
CAN_IDAC_IDHIT2	EQU	BIT2
CAN_IDAC_IDHIT1	EQU	BIT1
CAN_IDAC_IDHIT0	EQU	BIT0

CAN0RERR:	equ REGBASE+$14e ;can0 receive error counter
CAN0TERR:	equ REGBASE+$14f ;can0 transmit error counter
CAN0IDA0:	equ REGBASE+$150 ;can0 identifier acceptance register 0
CAN0IDA1:	equ REGBASE+$151 ;can0 identifier acceptance register 1
CAN0IDA2:	equ REGBASE+$152 ;can0 identifier acceptance register 2
CAN0IDA3:	equ REGBASE+$153 ;can0 identifier acceptance register 3
CAN0IDM0:	equ REGBASE+$154 ;can0 identifier mask register 0
CAN0IDM1:	equ REGBASE+$155 ;can0 identifier mask register 1
CAN0IDM2:	equ REGBASE+$156 ;can0 identifier mask register 2
CAN0IDM3:	equ REGBASE+$157 ;can0 identifier mask register 3
CAN0IDA4:	equ REGBASE+$158 ;can0 identifier acceptance register 4
CAN0IDA5:	equ REGBASE+$159 ;can0 identifier acceptance register 5
CAN0IDA6:	equ REGBASE+$15a ;can0 identifier acceptance register 6
CAN0IDA7:	equ REGBASE+$15b ;can0 identifier acceptance register 7
CAN0IDM4:	equ REGBASE+$15c ;can0 identifier mask register 4
CAN0IDM5:	equ REGBASE+$15d ;can0 identifier mask register 5
CAN0IDM6:	equ REGBASE+$15e ;can0 identifier mask register 6
CAN0IDM7:	equ REGBASE+$15f ;can0 identifier mask register 7
CAN0RXFG:	equ REGBASE+$160 ;can0 rx foreground buffer thru +$16f
CAN0TXFG:	equ REGBASE+$170 ;can0 tx foreground buffer thru +$17f

#IF SYSTEM_CPU = C32 | SYSTEM_CPU = C128
;CAN (Motorola Scalable CAN - MSCAN)
CANCTL0		EQU	$0140
CANCTL1		EQU	$0141
CANBTR0		EQU	$0142
CANBTR1		EQU	$0143
CANRFLG		EQU	$0144
CANRIER		EQU	$0145
CANTFLG		EQU	$0146
CANTIER		EQU	$0147
CANTARQ		EQU	$0148
CANTAAK		EQU	$0149
CANTBSEL	EQU	$014A
CANIDAC		EQU	$014B
CANRXERR	EQU	$014E
CANTXERR	EQU	$014F
CANIDAR0	EQU	$0150
CANIDAR1	EQU	$0151
CANIDAR2	EQU	$0152
CANIDAR3	EQU	$0153
CANIDMR0	EQU	$0154
CANIDMR1	EQU	$0155
CANIDMR2	EQU	$0156
CANIDMR3	EQU	$0157
CANIDAR4	EQU	$0158
CANIDAR5	EQU	$0159
CANIDAR6	EQU	$015A
CANIDAR7	EQU	$015B
CANIDMR4	EQU	$015C
CANIDMR5	EQU	$015D
CANIDMR6	EQU	$015E
CANIDMR7	EQU	$015F
CANRXFG		EQU	$0160		;RECEIVE BUFFER = $0160-$016F
CANTXFG		EQU	$0170		;TRANSMIT BUFFER = $0170-$017F
#ENDIF ;SYSTEM_CPU = C32 | SYSTEM_CPU = C128


#IF SYSTEM_CPU = DP256 | SYSTEM_CPU = DT256 
CAN1CTL0:	equ REGBASE+$180 ;can1 control register 0
CAN1CTL1:	equ REGBASE+$181 ;can1 control register 1
CAN1BTR0:	equ REGBASE+$182 ;can1 bus timing register 0
CAN1BTR1:	equ REGBASE+$183 ;can1 bus timing register 1
CAN1RFLG:	equ REGBASE+$184 ;can1 receiver flags
CAN1RIER:	equ REGBASE+$185 ;can1 receiver interrupt enables
CAN1TFLG:	equ REGBASE+$186 ;can1 transmit flags
CAN1TIER:	equ REGBASE+$187 ;can1 transmit interrupt enables
CAN1TARQ:	equ REGBASE+$188 ;can1 transmit message abort control
CAN1TAAK:	equ REGBASE+$189 ;can1 transmit message abort status
CAN1TBSEL:	equ REGBASE+$18a ;can1 transmit buffer select
CAN1IDAC:	equ REGBASE+$18b ;can1 identfier acceptance control

CAN1RERR:	equ REGBASE+$18e ;can1 receive error counter
CAN1TERR:	equ REGBASE+$18f ;can1 transmit error counter
CAN1IDA0:	equ REGBASE+$190 ;can1 identifier acceptance register 0
CAN1IDA1:	equ REGBASE+$191 ;can1 identifier acceptance register 1
CAN1IDA2:	equ REGBASE+$192 ;can1 identifier acceptance register 2
CAN1IDA3:	equ REGBASE+$193 ;can1 identifier acceptance register 3
CAN1IDM0:	equ REGBASE+$194 ;can1 identifier mask register 0
CAN1IDM1:	equ REGBASE+$195 ;can1 identifier mask register 1
CAN1IDM2:	equ REGBASE+$196 ;can1 identifier mask register 2
CAN1IDM3:	equ REGBASE+$197 ;can1 identifier mask register 3
CAN1IDA4:	equ REGBASE+$198 ;can1 identifier acceptance register 4
CAN1IDA5:	equ REGBASE+$199 ;can1 identifier acceptance register 5
CAN1IDA6:	equ REGBASE+$19a ;can1 identifier acceptance register 6
CAN1IDA7:	equ REGBASE+$19b ;can1 identifier acceptance register 7
CAN1IDM4:	equ REGBASE+$19c ;can1 identifier mask register 4
CAN1IDM5:	equ REGBASE+$19d ;can1 identifier mask register 5
CAN1IDM6:	equ REGBASE+$19e ;can1 identifier mask register 6
CAN1IDM7:	equ REGBASE+$19f ;can1 identifier mask register 7
CAN1RXFG:	equ REGBASE+$1a0 ;can1 rx foreground buffer thru +$1af
CAN1TXFG:	equ REGBASE+$1b0 ;can1 tx foreground buffer thru +$1bf
#ENDIF ;SYSTEM_CPU = DP256 | SYSTEM_CPU = DT256 

#IF SYSTEM_CPU = DP256 
CAN2CTL0:	equ REGBASE+$1c0 ;can2 control register 0
CAN2CTL1:	equ REGBASE+$1c1 ;can2 control register 1
CAN2BTR0:	equ REGBASE+$1c2 ;can2 bus timing register 0
CAN2BTR1:	equ REGBASE+$1c3 ;can2 bus timing register 1
CAN2RFLG:	equ REGBASE+$1c4 ;can2 receiver flags
CAN2RIER:	equ REGBASE+$1c5 ;can2 receiver interrupt enables
CAN2TFLG:	equ REGBASE+$1c6 ;can2 transmit flags
CAN2TIER:	equ REGBASE+$1c7 ;can2 transmit interrupt enables
CAN2TARQ:	equ REGBASE+$1c8 ;can2 transmit message abort control
CAN2TAAK:	equ REGBASE+$1c9 ;can2 transmit message abort status
CAN2TBSEL:	equ REGBASE+$1ca ;can2 transmit buffer select
CAN2IDAC:	equ REGBASE+$1cb ;can2 identfier acceptance control

CAN2RERR:	equ REGBASE+$1ce ;can2 receive error counter
CAN2TERR:	equ REGBASE+$1cf ;can2 transmit error counter
CAN2IDA0:	equ REGBASE+$1d0 ;can2 identifier acceptance register 0
CAN2IDA1:	equ REGBASE+$1d1 ;can2 identifier acceptance register 1
CAN2IDA2:	equ REGBASE+$1d2 ;can2 identifier acceptance register 2
CAN2IDA3:	equ REGBASE+$1d3 ;can2 identifier acceptance register 3
CAN2IDM0:	equ REGBASE+$1d4 ;can2 identifier mask register 0
CAN2IDM1:	equ REGBASE+$1d5 ;can2 identifier mask register 1
CAN2IDM2:	equ REGBASE+$1d6 ;can2 identifier mask register 2
CAN2IDM3:	equ REGBASE+$1d7 ;can2 identifier mask register 3
CAN2IDA4:	equ REGBASE+$1d8 ;can2 identifier acceptance register 4
CAN2IDA5:	equ REGBASE+$1d9 ;can2 identifier acceptance register 5
CAN2IDA6:	equ REGBASE+$1da ;can2 identifier acceptance register 6
CAN2IDA7:	equ REGBASE+$1db ;can2 identifier acceptance register 7
CAN2IDM4:	equ REGBASE+$1dc ;can2 identifier mask register 4
CAN2IDM5:	equ REGBASE+$1dd ;can2 identifier mask register 5
CAN2IDM6:	equ REGBASE+$1de ;can2 identifier mask register 6
CAN2IDM7:	equ REGBASE+$1df ;can2 identifier mask register 7
CAN2RXFG:	equ REGBASE+$1e0 ;can2 rx foreground buffer thru +$1ef
CAN2TXFG:	equ REGBASE+$1f0 ;can2 tx foreground buffer thru +$1ff

CAN3CTL0:	equ REGBASE+$200 ;can3 control register 0
CAN3CTL1:	equ REGBASE+$201 ;can3 control register 1
CAN3BTR0:	equ REGBASE+$202 ;can3 bus timing register 0
CAN3BTR1:	equ REGBASE+$203 ;can3 bus timing register 1
CAN3RFLG:	equ REGBASE+$204 ;can3 receiver flags
CAN3RIER:	equ REGBASE+$205 ;can3 receiver interrupt enables
CAN3TFLG:	equ REGBASE+$206 ;can3 transmit flags
CAN3TIER:	equ REGBASE+$207 ;can3 transmit interrupt enables
CAN3TARQ:	equ REGBASE+$208 ;can3 transmit message abort control
CAN3TAAK:	equ REGBASE+$209 ;can3 transmit message abort status
CAN3TBSEL:	equ REGBASE+$20a ;can3 transmit buffer select
CAN3IDAC:	equ REGBASE+$20b ;can3 identfier acceptance control

CAN3RERR:	equ REGBASE+$20e ;can3 receive error counter
CAN3TERR:	equ REGBASE+$20f ;can3 transmit error counter
CAN3IDA0:	equ REGBASE+$210 ;can3 identifier acceptance register 0
CAN3IDA1:	equ REGBASE+$211 ;can3 identifier acceptance register 1
CAN3IDA2:	equ REGBASE+$212 ;can3 identifier acceptance register 2
CAN3IDA3:	equ REGBASE+$213 ;can3 identifier acceptance register 3
CAN3IDM0:	equ REGBASE+$214 ;can3 identifier mask register 0
CAN3IDM1:	equ REGBASE+$215 ;can3 identifier mask register 1
CAN3IDM2:	equ REGBASE+$216 ;can3 identifier mask register 2
CAN3IDM3:	equ REGBASE+$217 ;can3 identifier mask register 3
CAN3IDA4:	equ REGBASE+$218 ;can3 identifier acceptance register 4
CAN3IDA5:	equ REGBASE+$219 ;can3 identifier acceptance register 5
CAN3IDA6:	equ REGBASE+$21a ;can3 identifier acceptance register 6
CAN3IDA7:	equ REGBASE+$21b ;can3 identifier acceptance register 7
CAN3IDM4:	equ REGBASE+$21c ;can3 identifier mask register 4
CAN3IDM5:	equ REGBASE+$21d ;can3 identifier mask register 5
CAN3IDM6:	equ REGBASE+$21e ;can3 identifier mask register 6
CAN3IDM7:	equ REGBASE+$21f ;can3 identifier mask register 7
CAN3RXFG:	equ REGBASE+$220 ;can3 rx foreground buffer thru +$22f
CAN3TXFG:	equ REGBASE+$230 ;can3 tx foreground buffer thru +$23f
#ENDIF ;SYSTEM_CPU = DP256 

;* EXTENDED PORTS

PORTT:		equ REGBASE+$240 ;portt data register
PTT:		equ REGBASE+$240 ;portt data register
PTIT:		equ REGBASE+$241 ;portt input register
DDRT:		equ REGBASE+$242 ;portt direction register
RDRT:		equ REGBASE+$243 ;portt reduced drive register
PERT:		equ REGBASE+$244 ;portt pull device enable
PPST:		equ REGBASE+$245 ;portt pull polarity select, 0=ACTIVE LOW, 1=ACTIVE HIGH

;IMPORTANT NOTE THE MODRR REGISTER HAS VERY DIFFERENT ACTION ON C FAMILY AND D FAMILY
;ALSO MODRR LOCATED IN DIFFERENT ADDRESS ON C FAMILY AND D FAMILY
#IF SYSTEM_CPU = C32 | SYSTEM_CPU = C128
MODRR:		equ REGBASE+$247 ; module routing register FOR PORT T PINS 0-4
MODDR0:		EQU BIT0	;BIT=0 ROUTES PORT T TO PIN, BIT=1 ROUTES PORT P TO PIN
MODDR1:		EQU BIT1	;BIT=0 ROUTES PORT T TO PIN, BIT=1 ROUTES PORT P TO PIN
MODDR2:		EQU BIT2	;BIT=0 ROUTES PORT T TO PIN, BIT=1 ROUTES PORT P TO PIN
MODDR3:		EQU BIT3	;BIT=0 ROUTES PORT T TO PIN, BIT=1 ROUTES PORT P TO PIN
MODDR4:		EQU BIT4	;BIT=0 ROUTES PORT T TO PIN, BIT=1 ROUTES PORT P TO PIN
#ENDIF ;SYSTEM_CPU = C32 | SYSTEM_CPU = C128

PORTS:		equ REGBASE+$248 ;ports data register
PTS:		equ REGBASE+$248 ;ports data register
PTIS:		equ REGBASE+$249 ;ports input register
DDRS:		equ REGBASE+$24a ;ports direction register
RDRS:		equ REGBASE+$24b ;ports reduced drive register
PERS:		equ REGBASE+$24c ;ports pull device enable
PPSS:		equ REGBASE+$24d ;ports pull polarity select, 0=ACTIVE LOW, 1=ACTIVE HIGH
WOMS:		equ REGBASE+$24e ;ports wired or mode register

PORTM:		equ REGBASE+$250 ;portm data register
PTM:		equ REGBASE+$250 ;portm data register
PTIM:		equ REGBASE+$251 ;portm input register
DDRM:		equ REGBASE+$252 ;portm direction register
RDRM:		equ REGBASE+$253 ;portm reduced drive register
PERM:		equ REGBASE+$254 ;portm pull device enable
PPSM:		equ REGBASE+$255 ;portm pull polarity select, 0=ACTIVE LOW, 1=ACTIVE HIGH
WOMM:		equ REGBASE+$256 ;portm wired or mode register


#IF SYSTEM_CPU = DP256 | SYSTEM_CPU = DG256 | SYSTEM_CPU = DT256 | SYSTEM_CPU = DJ256
MODRR:		equ REGBASE+$257 ;portm module routing register
MODDR0:		EQU BIT0	;MODDR[1:0] CONTROLS CAN0 ROUTING
MODDR1:		EQU BIT1	
				;MODRR [1:0]=00 MEANS CAN0 RX -> PM0, TX -> PM1
				;MODRR [1:0]=01 MEANS CAN0 RX -> PM2, TX -> PM3
				;MODRR [1:0]=01 ONLY VALID IF CAN1 DISABLED
				;MODRR [1:0]=10 MEANS CAN0 RX -> PM4, TX -> PM5
				;MODRR [1:0]=10 ONLY VALID IF CAN2 DISABLED
				;MODRR [1:0]=11 RESERVED

MODDR2:		EQU BIT2	;MODRR[3:2] CONTROLS CAN4 ROUTING
MODDR3:		EQU BIT3
				;MODRR [3:2]=00 MEANS CAN4 RX -> PJ6, TX -> PJ7
				;MODRR [3:2]=01 MEANS CAN4 RX -> PM4, TX -> PM5
				;MODRR [3:2]=01 ONLY VALID IF CAN2 DISABLED AND CAN0 NOT ROUTED OR DISABLED
				;MODRR [3:2]=10 MEANS CAN4 RX -> PM6, TX -> PM7
				;MODRR [3:2]=10 ONLY VALID IF CAN3 DISABLED
				;MODRR [3:2]=11 RESERVED
MODDR4:		EQU BIT4	;MODDR[4] IS SPI0 ROUTING
				;MODDR[4]=0 MEANS SPI0 MISO -> PS4, MOSI -> PS5, SCLK -> PS6, SS -> PS7
				;MODDR[4]=1 MEANS SPI0 MISO -> PM2, MOSI -> PM4, SCLK -> PM5, SS -> PM3
				;MODDR[4]-=1 ONLY VALID IF CAN PORTS ROUTED TO PM2-5 ARE DISABLED
MODDR5:		EQU BIT5	;MODDR5 IS SPI1 ROUTING
				;MODDR[5]=0 MEANS SPI1 MISO -> PP0, MOSI -> PP1, SCLK -> PP2, SS -> PP3
				;MODDR[5]=1 MEANS SPI1 MISO -> PH0, MOSI -> PH1, SCLK -> PH2, SS -> PH3
MODDR6:		EQU BIT6	;MODDR6 IS SPI2 ROUTING
				;MODDR[6]=0 MEANS SPI2 MISO -> PP4, MOSI -> PP5, SCLK -> PP6, SS -> PP7
				;MODDR[6]=1 MEANS SPI2 MISO -> PH4, MOSI -> PH5, SCLK -> PH6, SS -> PH7
;IMPORTANT NOTE FOR PORT P:  IF PWM ENABLED, IT TAKES PRECEDENCE OVER SPI AND GENERAL I/O, SPI TAKES PRECEDENCE OVER GENERAL I/O
#ENDIF ;SYSTEM_CPU = DP256 | SYSTEM_CPU = DG256 | SYSTEM_CPU = DT256 | SYSTEM_CPU = DJ256

PORTP:		equ REGBASE+$258 ;portp data register
PTP:		equ REGBASE+$258 ;portp data register
PTIP:		equ REGBASE+$259 ;portp input register
DDRP:		equ REGBASE+$25a ;portp direction register
RDRP:		equ REGBASE+$25b ;portp reduced drive register
PERP:		equ REGBASE+$25c ;portp pull device enable
PPSP:		equ REGBASE+$25d ;portp pull polarity select, 0=ACTIVE LOW, 1=ACTIVE HIGH
PIEP:		equ REGBASE+$25e ;portp interrupt enable register
PIFP:		equ REGBASE+$25f ;portp interrupt flag register

#IF SYSTEM_CPU = DP256 | SYSTEM_CPU = DG256 | SYSTEM_CPU = DT256 | SYSTEM_CPU = DJ256
PORTH:		equ REGBASE+$260 ;porth data register
PTH:		equ REGBASE+$260 ;porth data register
PTIH:		equ REGBASE+$261 ;porth input register
DDRH:		equ REGBASE+$262 ;porth direction register
RDRH:		equ REGBASE+$263 ;porth reduced drive register
PERH:		equ REGBASE+$264 ;porth pull device enable
PPSH:		equ REGBASE+$265 ;porth pull polarity select, 0=ACTIVE LOW, 1=ACTIVE HIGH
PIEH:		equ REGBASE+$266 ;porth interrupt enable register
PIFH:		equ REGBASE+$267 ;porth interrupt flag register
#ENDIF ;SYSTEM_CPU = DP256 | SYSTEM_CPU = DG256 | SYSTEM_CPU = DT256 | SYSTEM_CPU = DJ256


PORTJ:		equ REGBASE+$268 ;portp data register
PTJ:		equ REGBASE+$268 ;portp data register
PTIJ:		equ REGBASE+$269 ;portp input register
DDRJ:		equ REGBASE+$26a ;portp direction register
RDRJ:		equ REGBASE+$26b ;portp reduced drive register
PERJ:		equ REGBASE+$26c ;portp pull device enable
PPSJ:		equ REGBASE+$26d ;portp pull polarity select, 0=ACTIVE LOW, 1=ACTIVE HIGH
PIEJ:		equ REGBASE+$26e ;portp interrupt enable register
PIFJ:		equ REGBASE+$26f ;portp interrupt flag register


#IF SYSTEM_CPU = C32 | SYSTEM_CPU = C128
PORTAD		EQU	$270
PTAD		EQU	$270	
PTIAD		equ	$271	; Port AD
DDRAD		equ	$272	; Port AD
RDRAD		equ	$273	; Port AD
PERAD		equ	$274	; Port AD
PPSAD		equ	$275	; Port AD, 0=ACTIVE LOW, 1=ACTIVE HIGH
#ENDIF ;SYSTEM_CPU = C32 | SYSTEM_CPU = C128

#IF SYSTEM_CPU = DP256 | SYSTEM_CPU = DG256 | SYSTEM_CPU = DT256 | SYSTEM_CPU = DJ256
;*CAN

CAN4CTL0:	equ REGBASE+$280 ;can4 control register 0
CAN4CTL1:	equ REGBASE+$281 ;can4 control register 1
CAN4BTR0:	equ REGBASE+$282 ;can4 bus timing register 0
CAN4BTR1:	equ REGBASE+$283 ;can4 bus timing register 1
CAN4RFLG:	equ REGBASE+$284 ;can4 receiver flags
CAN4RIER:	equ REGBASE+$285 ;can4 receiver interrupt enables
CAN4TFLG:	equ REGBASE+$286 ;can4 transmit flags
CAN4TIER:	equ REGBASE+$287 ;can4 transmit interrupt enables
CAN4TARQ:	equ REGBASE+$288 ;can4 transmit message abort control
CAN4TAAK:	equ REGBASE+$289 ;can4 transmit message abort status
CAN4TBSEL:	equ REGBASE+$28a ;can4 transmit buffer select
CAN4IDAC:	equ REGBASE+$28b ;can4 identfier acceptance control

CAN4RERR:	equ REGBASE+$28e ;can4 receive error counter
CAN4TERR:	equ REGBASE+$28f ;can4 transmit error counter
CAN4IDA0:	equ REGBASE+$290 ;can4 identifier acceptance register 0
CAN4IDA1:	equ REGBASE+$291 ;can4 identifier acceptance register 1
CAN4IDA2:	equ REGBASE+$292 ;can4 identifier acceptance register 2
CAN4IDA3:	equ REGBASE+$293 ;can4 identifier acceptance register 3
CAN4IDM0:	equ REGBASE+$294 ;can4 identifier mask register 0
CAN4IDM1:	equ REGBASE+$295 ;can4 identifier mask register 1
CAN4IDM2:	equ REGBASE+$296 ;can4 identifier mask register 2
CAN4IDM3:	equ REGBASE+$297 ;can4 identifier mask register 3
CAN4IDA4:	equ REGBASE+$298 ;can4 identifier acceptance register 4
CAN4IDA5:	equ REGBASE+$299 ;can4 identifier acceptance register 5
CAN4IDA6:	equ REGBASE+$29a ;can4 identifier acceptance register 6
CAN4IDA7:	equ REGBASE+$29b ;can4 identifier acceptance register 7
CAN4IDM4:	equ REGBASE+$29c ;can4 identifier mask register 4
CAN4IDM5:	equ REGBASE+$29d ;can4 identifier mask register 5
CAN4IDM6:	equ REGBASE+$29e ;can4 identifier mask register 6
CAN4IDM7:	equ REGBASE+$29f ;can4 identifier mask register 7
CAN4RXFG:	equ REGBASE+$2a0 ;can4 rx foreground buffer thru +$2af
CAN4TXFG:	equ REGBASE+$2b0 ;can4 tx foreground buffer thru +$2bf
#ENDIF ;SYSTEM_CPU = DP256 | SYSTEM_CPU = DG256 | SYSTEM_CPU = DT256 | SYSTEM_CPU = DJ256

;THE FOLLOWING LINE RESTORES LISTING FOR CODE OUTSIDE OF THIS LIBRARY
	LIST

;* end registers
#ENDIF	;MC9S12REGS
