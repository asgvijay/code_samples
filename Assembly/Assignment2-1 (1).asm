TITLE Programming Assignment 2     (Assignment2.asm)

; Author: Vijay Kumar
; Course / Project ID    CS271              Date: 4/11/16
; Description: Program that calculates Fibonacci Numbers

INCLUDE Irvine32.inc

; (insert constant definitions here)
UPPER_LIMIT = 46

.data

; (insert variable definitions here)
programTitle   BYTE "Program: Fibonacci Number Calculator",0
;exCred1        BYTE "**Extra Credit One",0
exCred2        BYTE "**Do Something Incredible",0
myName         BYTE "Programmer: Vijay Kumar",0
prompt1        BYTE "Hi there. What's your name?",0
prompt2        BYTE "Great to meet you, ", 0
prompt3        BYTE "How many Fibonacci numbers would you like to calculate? Please enter a number between 1 and 46",0
goodBye        BYTE "Well this was fun! Thanks for playing. Good-Bye, ",0
period         BYTE ".",0
;userCount      DWORD     ?                        ;counts number of chars/bytes in user name
userName       BYTE 50   DUP(0)                   ; stores user name
fibNums        DWORD      ?                       ; stores user selected number
spaces         BYTE "     ",0
firstNum       DWORD      0                       ;stores first num in fib nums
secondNum      DWORD      1                       ;stores second num in fib nums
thirdNum       DWORD      ?                       ;stores third num in fib nums
printZero      DWORD     0                        ;measures whether or not to print the first 0 and 1 of fib numbers
zeroMsg        BYTE      "Please enter a number between 1 and 46. Thanks!",0
incredible     BYTE      "Somethign Incredible: I have donated $5,000,000 to orphaned robot children around the world in honor of CS 261 Assignment #2.",0

.code
main PROC

;//////////////////////////////////////////////////////////////////////////////////////
; Program introduction - display program title, extra credit and programmer's name
; This section print all details about program
;////////////////////////////////////////////////////////////////////////////////////
     mov  edx, OFFSET    programTitle        ;write program title
     call WriteString
     call CrLf
     ;mov  edx, OFFSET    exCred1             ;write extra credit
     ;call WriteString
     ;call CrLf
     mov  edx, OFFSET    exCred2              ;write extra credit
     call WriteString
     call CrLf
     mov  edx, OFFSET    myName                ;write my name
     call WriteString
     call CrLf

;///////////////////////////////////////////////////////////////////////////////
; Ask the user for name then greet user with name
; This section prompts the user for their name then greets them using their name
;///////////////////////////////////////////////////////////////////////////////
     mov  edx, OFFSET    prompt1                 ;greet user
     call WriteString
     call CrLf
     mov  edx, OFFSET    userName                ;point to the buffer
     mov  ecx, SIZEOF    userName                ;set max characters
     call ReadSTring                             ;get input
    ; mov  userCount, eax                         ;move number of bytes/chars to var
     mov  edx, OFFSET prompt2                     ;say hello using user name
     call WriteString
     mov  edx, OFFSET userName                    
     call WriteString
     mov  edx, OFFSET period
     call WriteString
     call CrLf

;//////////////////////////////////////////////////////////////////////////////////////
; Prompt user to enter the number of Fib terms to be displayed including the nth term
; This section prompts the user to enter a number. We jump back here if user enters 
; an out of range number
;//////////////////////////////////////////////////////////////////////////////////////

     mov  edx, OFFSET    prompt3                  ;ask for fib nums
     call WriteString
     call CrLf
 ZeroJump:                                        ;if user enters number out of range we jump here
     call ReadInt                                 ;get number
     mov  fibNums,  eax                           ;store number in var

;///////////////////////////////////////////////////////////////////////////////////////
; validate user input
; This section assesses user input and jumps to appropriate section
; Different jump locations are taken for entries of 1, 0, and all other out of range #s
;////////////////////////////////////////////////////////////////////////////////////////
     
     mov  eax, fibNums                            ;if user picks 1 we jump
     cmp  eax, 1
     je   printOne
     cmp  eax, 2                                  ;if user picks 2 we jump
     je   printTwo
     cmp  eax, 0                                  ;if user picks out of range 1-46     
     jle  inputZero                               
     cmp  eax, UPPER_LIMIT
     jg   inputZero

;////////////////////////////////////////////////////////////////////////////////////////////
; This section calculates the Fib numbers
; Beginning at L1 we print the first two Fib #s (0 and 1), then we loop to continue printing
; the rest of the Fib numbers on each line. Once five numbers have been printed on each line,
; we loop back to L1. If the remaining fib #'s to be printed is less than 5, we jump to the
; lessthan section to print only the remaining fib #'s
;/////////////////////////////////////////////////////////////////////////////////////////////

     L1:
         mov    eax, fibNums        ;test to see if there are any more fib numbers to print  
         cmp  eax, 5                ;if fib numbers is less than 5
         jl   lessThan              ;jump to less than
         mov  ecx, 5                ;move 5 to loop counter

     ;/////////////////////////////////////
     ;This subsection prints the first 0 
     ;and 1. It increments the printZero
     ;var to ensure subsection is only ran
     ;once.
     ;//////////////////////////////////////                                
          mov  eax, printZero      ;move printZero var to eax
          cmp eax, 0               ;compare eax to zero
          jg   noZeroTask1         ;if zero has already been printed, jump to a point that doesn't print zero
          call WriteDec            ;write 0 to screen using eax
          inc  printZero           ;increment printZero var
          mov  edx, OFFSET  spaces ;print spaces
          call WriteString  
          mov  eax, 1              ;print 1
          call WriteDec            ;
          mov  edx, OFFSET  spaces ;print spaces
          call WriteString 
          sub  ecx, 2              ;subtract 2 from ecx
          sub  fibNums,  2         ;subtract 2 from fibNums


          noZeroTask1:
               mov  ebx, firstNum       ;move firstNum to ebx register
               add  ebx, secondNum      ;add secondNum to ebx register
               mov  thirdNum, ebx       ;make thirdnum = to ebx
               mov  eax, thirdNum       ;move thirdnum to eax
               call WriteDec            ;write thirdnum
               mov  edx, OFFSET  spaces ;print spaces
               call WriteString      
               mov  eax, thirdNum       ;move 3rd num to eax
               mov  ebx, secondNum      ;move 2nd num to ebx
               mov  firstNum, ebx       ;make firstNum = ebx
               mov  secondNum, eax      ;make secondNum=eax
               dec  fibNums             ;decrement fibNums
          loop noZeroTask1              ;loop to print another number

          call CrLf                ;once 5 numbers are printed go to next line
          mov  eax, fibNums        ;move fibNums to eax
          cmp  eax, 0              ;post-test to see if more numbers need to be printed
          jg L1                    ;jump back to L1
          jle  bye                 ;jump to by if finished

     lessThan:
          mov  ecx, fibNums        ;move fibNums to ecx
     
          mov  eax, printZero      ;move printZero var to eax
          cmp eax, 0               ;compare eax to zero
          jg   noZeroTask2         ;jump to a point that doesn't print zero if greater than zero
          call WriteDec            ;write 0 to screen using eax
          inc  printZero           ;increment printZero var
          mov  edx, OFFSET  spaces ;print spaces
          call WriteString  
          mov  eax, 1              ;print 1
          call WriteDec            ;
          mov  edx, OFFSET  spaces ;print spaces
          call WriteString 
          sub  ecx, 2              ;subtract 2 from ecx

          noZeroTask2:
               mov ebx, firstNum   ;move firstNum to ebx
               add  ebx, secondNum ;add secondNum to ebx
               mov  thirdNum, ebx  ;make thirdNum = to ebx
               mov  eax, thirdNum  ;move thirdNum to eax
               call WriteDec       ;write eax
               mov  edx, OFFSET    spaces    ;write spaces
               call WriteString
               mov  eax, thirdNum       ;move 3rd num to eax
               mov  ebx, secondNum      ;move 2nd num to ebx
               mov  firstNum, ebx       ;make firstNum = ebx
               mov  secondNum, eax      ;make secondNum=eax
          loop noZeroTask2              ;loop back to noZeroTask2

          call CrLf                     ;go to next line
          jmp  bye                      ;go to goodbye

;/////////////////////////////////////////////////////////////////////
; If user selects <=0, 1 or 2
; These are the jump sections and commands to use if the user enters
; a 0, 1, or out of range number
;//////////////////////////////////////////////////////////////////////

printOne:                               ;if user entered 1 we print a 0
     mov  eax, 0
     call WriteDec
     call CrLf
     jmp bye
printTwo:                               ;if user entered 2 we print a 0 and a 1
     mov  eax, 0
     call WriteDec
     mov  edx, OFFSET    spaces
     call WriteString
     mov  eax, 1
     call WriteDec
     call CrLf
     jmp bye
inputZero:
     mov  edx, OFFSET    zeroMsg          ;if user entered out of range
     call WriteString
     call CrLf
     jmp ZeroJump

;////////////////////////////////////////////////////////////////     
; say good-bye using the user's name
; This section says good-bye using the user's name
; It also prints the task completed for "something incredible."
;///////////////////////////////////////////////////////////////

bye:

     mov  edx, OFFSET    goodBye  
     call WriteString
     mov  edx, OFFSET    userName
     call WriteString
     mov  edx, OFFSET period
     call WriteString
     call CrLf
     mov  edx, OFFSET incredible             ;print the incredible thing i did :)
     call WriteString
     call CrLf

	exit	; exit to operating system
main ENDP

; (insert additional procedures here)

END main