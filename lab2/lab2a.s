; vim: set filetype=asmhc12:                                                                                                     

; This program has us using some of the macros provided by Dr. Stapleton.

; Instructions:

; a. First, output a prompt to the terminal screen via SCI0 asking the user to
; enter his/her name.  

; b. Next, input a string from the keyboard via SCI0 which is assumed to be the
; user’s name.  

; c. Next, your program should output a message “Hello name, the
; sum of all the ASCII codes in your name is ##.”  For this “name” should be
; replaced with whatever string the user entered after the name prompt.  The
; token “##” should be replaced with a number calculated by adding all of the
; “unsigned char” ASCII codes for the letters entered by the user in their
; name.  

; d. Next, your program should output a scond message on a new line “Your lucky
; number is ##.”  The token “##” should be replaced with a number calculated
; dividing the sum of ASCII codes previously calculated by 20 then adding 1 to
; the remainder of the division.  

#INCLUDE ../HC12TOOLS.INC


