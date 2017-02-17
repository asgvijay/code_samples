TITLE Assignment 1     (Assignment1.asm)

; Author: Vijay Kumar
; Course / Project ID: Assignment 1                 Date: 3/29/16
; Description: Assignment #1

INCLUDE Irvine32.inc

; (insert constant definitions here)

.data

userNum1  DWORD ?    ;integer to be entered by user
userNum2  DWORD ?    ;interger to be entered by user
intro_1   BYTE "Hi, my name is Vijay. I will be performing a bit of magical, elementary math.", 0
intro_2   BYTE "Program: Elementary Mathematics.", 0
instr_1   BYTE "This program will take two numbers and provide the sum, difference, product, and quotient and remainder.", 0
instr_2   BYTE "Please enter two integers.", 0
instr_3   BYTE "Thank you. Now I will perform the math.", 0
addString BYTE "The sum of your two numbers is: ",0 
subString BYTE "The difference of your two numbers is: ", 0
mulString BYTE "The product of your two numbers is: ", 0
quoString BYTE "The quotient and remainder of your two numbers are: ", 0 
quoStringCont BYTE  " and ",0
resultAdd DWORD ?        ; variable for addition
resultSub DWORD ?        ; variable for subtraction
resultMul DWORD ?        ; variable for multiplication
resultDivQ     DWORD ?   ; variable for division -- quotient
resultDivR     DWORD ?   ; variable for division -- remainder
goodBye   BYTE "Good-Bye.", 0
newNum    BYTE "Please enter your numbers again, and ensure that the second number is less than the first. Thank you!",0
exCredit  BYTE "**EC: Program verifies second number less than first.",0
exCredit1  BYTE "**EC: Program allows user to continue or quit.",0
userCont  BYTE "Would you like to try again? Press 1 to continue, 0 to exit.",0
contNum   DWORD     1;   ;variable to test if user wants to continue

.code
main PROC


; Display name and program title on output screen
     mov  edx, OFFSET    intro_2   ;display program name
     call WriteString
     call CrLf
     mov edx, OFFSET     exCredit  ; display extra credit
     call WriteString
     call CrLf
     mov edx, OFFSET     exCredit1 ; display extra credit
     call WriteString
     call CrLf
     mov edx,  OFFSET    intro_1   ;introduce programmer
     call WriteString
     call CrLf
     

; program while loop, if eax equals 0 then program loop does not continue
L2:
     mov eax, contNum    ; set eax to 1
     cmp eax, 0          ; compare eax to zero
     jz L1               ; jump to L1 if zero flag was set

; Display instructions for the user
     mov edx, OFFSET    instr_1    ;display instructions
     call WriteString
     call CrLf

; Prompt the user to enter two numbers

     mov edx, OFFSET    instr_2    ;prompt user for numbers
     call WriteString
     call CrLf
     call ReadInt
     mov  userNum1, eax            ;write first number to userNum1 var
     call ReadInt
     mov userNum2, eax             ;write second number to userNum2 var

;validate user input
     mov  eax, userNum1            ;move userNum1 to EAX
     beginwhile1:
          cmp  eax, userNum2  ; test to see if userNum2 is less than eax
          jg  endwhile        ;if eax is greater than userNum2, we continue with program, otherwise we request new num
          mov  edx, OFFSET    newNum    ;prompt user for new numbers
          call WriteString
          call CrLF
          call ReadInt
          mov  userNum1, eax            ;write input to userNum1
          call ReadInt
          mov userNum2, eax             ;write input to userNum2
          mov eax,  userNum1            ; put userNum1 into eax
          jmp beginwhile1               ;jump back to beginwhile1 loop
     endwhile:

;Calculate the sum, difference, product, quotient and remainder of the numbers
     ;calculate sum
     mov  eax, userNum1       ;move userNum1 to eax
     mov  ebx,  userNum2      ;move userNum2 to ebx
     ADD  eax, ebx            ; add ebx to eax
     mov  resultAdd, eax      ; move eax to result variable

     ;calculate difference
     mov  eax, userNum1       ;move userNum1 to eax 
     mov  ebx,  userNum2      ;move userNum2 to ebx
     sub  eax, ebx            ;subtract ebx from eax
     mov  resultSub, eax      ;move eax to result var

     ;calculate product        
     mov  eax, userNum1       ;move userNum1 to eax
     mov  ebx,  userNum2      ;move userNum2 to ebx
     mul  ebx                 ;multiply eax by ebx
     mov  resultMul, eax      ;move eax to result var

     ;calculate quotient
     mov  eax, userNum1        ;move userNum1 to eax
     mov  ebx,  userNum2      ;move userNum2 to ebx
     div  ebx                 ;div eax by ebx
     mov  resultDivQ, eax     ; move eax quotient to result var
     mov  resultDivR, edx     ;move edx remainder to result var

  

;Report Result
     
     ;report addition
     mov  edx, OFFSET    addString      ;display addition result
     call WriteString
     mov  eax, resultAdd
     call WriteDec
     call CrLf

     ;report subtraction
     mov  edx, OFFSET    subString      ;display subtraction result
     call WriteString
     mov  eax, resultSub
     call WriteDec
     call CrLf

     ;report Mulltiplication
     mov  edx, OFFSET    mulString      ;display multiplication result
     call WriteString
     mov  eax, resultMul
     call WriteDec
     call CrLf


     ;report Quotien and Remainder
     mov  edx, OFFSET    quoString      ;display quotient result
     call WriteString
     mov  eax, resultDivQ
     call WriteDec
     mov  edx, OFFSET    quoStringCont  ;display remainder result
     call WriteString
     mov eax, resultDivR
     call WriteDec
     call CrLf

; would the user like to continue

     mov edx, OFFSET    userCont        ;ask the user to continue or exit
     call WriteString
     call CrLf
     call ReadInt
     mov  contNum, eax                  ; write input to eax
     jmp L2                             ; jump back to beginning loop
     
L1:
;Display terminating message
     mov edx,  OFFSET    goodBye        ;say goodbye
     call WriteString
     call CrLf



	exit	; exit to operating system
main ENDP



END main