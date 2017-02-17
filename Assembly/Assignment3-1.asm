TITLE Assignment 3     (Assignment3.asm)

; Author: Vijay Kumar
; Course / Project ID   CS 261              Date: 4/25/16
; Description: This program wil display the program title and programmer's name; get the user's name and greet the user;
; Display instructions for the user; REpeatedly prompt the user to enter a number. Validate the user input to be in [-100,1](inclusive). 
; Count and accumulate the valid user numbesr until a non-negative number is entered; Calculate the (rounded integer) average of the negative numbers.
; Display the number of negative numbers entered, the sum of negative numbers entered, the average, rounded to the nearest integer, a parting message(with the 
; user's name)

INCLUDE Irvine32.inc

; (insert constant definitions here)


.data

; (insert variable definitions here)
programTitle   BYTE "Program: Programming Assignment #3",0
exCred1       BYTE "**Extra-Credit :Number the lines during user input",0
myName         BYTE "Programmer: Vijay Kumar",0
welcome        BYTE "Welcome to the Integer Accumulator.",0
prompt1        BYTE "Hi there. What's your name?",0
prompt3        BYTE "Enter a number between -100 and -1. Enter a non-negative number when you are finished to see results.",0
prompt4        BYTE "Enter another number: ",0
prompt5        BYTE "That number was out of range. Let's try again.",0
prompt6        BYTE "You entered ",0
prompt7       BYTE " valid numbers. ",0
prompt8       BYTE "The sum of all your numbers is: ",0
prompt9       BYTE "The average of all your numbers is:  ",0
goodBye        BYTE "Well this was fun! Thanks for playing. Good-Bye, ",0
prompt2        BYTE "Great to meet you, ", 0
period         BYTE ".",0
colon         BYTE ": ",0
testPhrase     BYTE "sumTotal is equal to: ",0
userName       BYTE 50   DUP(0)                   ; stores user name
LOWER          SDWORD     -100;
lineNumber     DWORD         1;
userNum        SDWORD        ?;
sumTotal       SDWORD        0;
average        SDWORD        ?;
remainder      SDWORD        ?;
accum          DWORD          0;
.code
main PROC

;//////////////////////////////////////////////////////////////////////////////////////
; Program introduction - display program title, extra credit and programmer's name
; This section print all details about program
;////////////////////////////////////////////////////////////////////////////////////

; introduce program and programmer

     mov  edx, OFFSET    programTitle        ;write program title
     call WriteString
     call CrLf
     mov  edx, OFFSET    exCred1             ;write extra credit
     call WriteString
     call CrLf
     mov  edx, OFFSET    myName                ;write my name
     call WriteString
     call CrLf



;///////////////////////////////////////////////////////////////////////////////
; Ask the user for name then greet user with name
; This section prompts the user for their name then greets them using their name
;///////////////////////////////////////////////////////////////////////////////

; greet user

     mov  edx, OFFSET    welcome                 ;greet user
     call WriteString
     call CrLf

     mov  edx, OFFSET    prompt1                 ;greet user
     call WriteString
     call CrLf
     mov  edx, OFFSET    userName                ;point to the buffer
     mov  ecx, SIZEOF    userName                ;set max characters
     call ReadSTring                             ;get input
     mov  edx, OFFSET prompt2                    ;say hello using user name
     call WriteString
     mov  edx, OFFSET userName                    
     call WriteString
     mov  edx, OFFSET period
     call WriteString
     call CrLf

;//////////////////////////////////////////////////////////////////////////////////////
; Prompt User for numbers - This section prompts the user for numbers. If the user
; input is less than -100, we ask for another number. If the number is in the range
; of -101 and -1, we add the number to our sumTotal and increment a the counter.
; when the user enters a non-negative number we jump to the resulting print section
;////////////////////////////////////////////////////////////////////////////////////

; prompt user to input numbers

  
     mov  edx, OFFSET    prompt3                  ;ask for numbers -- introductory
     call WriteString
     call CrLf
     jmp L1

  L0:

     mov  edx, OFFSET    prompt4                  ;ask for another number
     call WriteString
     call CrLf
     jmp L1
     

  outOfRange:                                     ; jump here if input is out of range
     mov edx,  OFFSET     prompt5
     call WriteString
     call CrLf
                         
  L1:                                             ; jump here to get input
     mov  eax,  lineNumber
     call WriteDec
     mov  edx, OFFSET    colon
     call WriteString
     call ReadInt                                 ; get number
     cmp  eax, LOWER                              ; compare that number to lower limite constant
     jl   outOfRange                              ; if number is less than lower we jump to outOfRange label
     cmp  eax, 0                                  ; compare number to 0
     jge  printNums                               ; if number is greater than or equal to zero we jump to printNums section


     add  eax, sumTotal                           ; add sumTotal to eax
     mov  sumTotal, eax                           ;move new sum to sumTotal
    

     inc accum                                    ; increment the accum variable
     inc lineNumber
     jmp L0                                       ; jump back to get another number

;//////////////////////////////////////////////////////////////////////////////////////
; Results Display: This section prints the amount of numbers entered, their total sum
; and the average of all acceptable entries
;////////////////////////////////////////////////////////////////////////////////////

; print the amount of numbers entered, the sum of all numbers, the average of all numbers

printNums:
     mov edx,  OFFSET    prompt6                  ; display the number found in the accum variable
     call WriteString
     mov  eax, accum
     call WriteDec
     mov edx,  OFFSET    prompt7                  
     call WriteString
     call CrLf
     mov edx,  OFFSET    prompt8                   ; display the total found in sumTotal
     call WriteString
     mov  eax, sumTotal
     call WriteInt
     mov  edx, OFFSET    period
     call WriteString
     call CrLf

     mov edx,  OFFSET    prompt9                  ; display the average of all numbers
     call WriteString
     cdq                                          ; sign extend the eax register
     mov  ebx, accum                              ; move the accum variable to ebx
     idiv  ebx                                    ; sign divide eax by ebx
     mov  remainder, edx
     neg eax;

     
    mov   average, eax                  ; move the quotient of the above devision to average variable
    mov   eax, remainder                ;  move the remainder of the above division to the eax register
    neg eax;                            ; make eax contents negative
    mov  ebx, 2                         ; move 2 to ebx
    mul  ebx                            ; multiply the remainder in eax by 2 in ebx
    cmp   eax, accum                    ; if remainder*2 < the accumulator variable
    jle    noBumpUp                     ; jump to section to not decrement the number
    mov   eax, average                  ; move the average back to eax
    inc eax                             ; decrement the variable
    neg eax                             ; negate the eax register
     call WriteInt                      ; write the value in eax to the screen
     mov  edx, OFFSET    period                      
     call WriteString
     call CrLf

    jmp bye                             ; jump to the goodbye section

     
    noBumpUp:
     mov eax, average
     neg eax
     call WriteInt                                ; write the value in eax to the screen
     mov  edx, OFFSET    period                      
     call WriteString
     call CrLf



; say goodbye

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
    mov eax, 10000                                     ;delaying program from closing screen so we can read results.
    call Delay


	exit	; exit to operating system
main ENDP

; (insert additional procedures here)

END main