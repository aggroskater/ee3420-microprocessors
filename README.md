ee3420-microprocessors
======================

Repository for EE 2420 Microprocessors class with Dr. Stapleton. Dr. Stapleton 
provided many, many subroutines for use in this course in conjunction with the 
Dragon12 development boards by EVB Plus. They were placed on the flash memory. 
Depending on the precise model and revision of the development board in use 
(Dragon12, Dragon12 Plus, Dragon12 Plus2), the location on flash and the paging 
to access it would be slightly different. However, the subroutines themselves 
remained the same as far as I know. Dr. Stapleton flashed all of the boards 
used in class via the two-board POD set up. I have provided what I believe to 
be a relatively recent version of the flash .s29 file that may or may not work 
for anyone who trys to program the flash memory with it. It is located in this 
directory as:

    Dragon12-Plus_FLASH_Image_01-16-2013.s29

Assuming you can successfully program the flash memory for your particular 
development board, then all of the macros utilized in this course (like GETS, 
PUTS, and numerous other C functions Dr. Stapleton implemented in assembler for 
the HCS12 models) should function. Can't make any promises though.
