TITLE Assignment 6 A    (A6A.asm)

; Author: Vijay Kumar
; Course / Project ID      CS 271 Assignment 6 A            Date: 5/23/16
; Description: 

INCLUDE Irvine32.inc

displayString MACRO 

     push edx
     mov edx, [ebp+12]
     call WriteString 
     pop edx

ENDM

getString MACRO 
     push ecx
     push edx
     mov  edx, [ebp+20]
     call WriteString
     call CrLf
     mov  edx, [ebp+8]
     mov  ecx, SIZEOF userInput
     call ReadString
     mov  byteCount, eax
     pop edx
     pop ecx
ENDM

.data

intro          BYTE "PROGRAMMING ASSIGNMENT 6: designing low-level I/O procedures", 0
author         BYTE "Written by: Vijay Kumar", 0
goodbye        BYTE "Thanks for playing!", 0
getStrPrompt   BYTE "Please enter a number.", 0
userIntegers   DWORD 10 DUP (?)
userInput      BYTE 32 DUP(0)
byteCount      DWORD     ?
userPrompt     BYTE "Please provide 10 unsigned decimal integers. Each number needs to be small enough to fit inside a 32 bit register. After you have finished inputting the raw numbers, I will dsiplay a list of the integers, their sum, and their average value.", 0
outofRange1    BYTE "ERROR: You did not enter an unsigned number or your number was too big. Let's try again.", 0
xVal           DWORD     0;
newString      BYTE 100 DUP(0)
comma          BYTE ", ", 0
sizeVal        DWORD     ?
yourNumber     BYTE "Your Numbers are:", 0
theSum         BYTE "The sum of all your numbers is: ", 0
theAverage     BYTE "The aveage of all your numbers is: ", 0




.code
main PROC

mov edx, OFFSET intro                                  ; introduce program
call WriteString
call CrLf
mov edx, OFFSET author
call WriteString
call CrLf


push OFFSET outofRange1                                ; push paramaters
push OFFSET userPrompt
push OFFSET getStrPrompt
push OFFSET xVal
push OFFSET userIntegers
push OFFSET userInput
call ReadVal                                           ; read in string of numeric values and convert to integers

push OFFSET comma                                      ; push parameters
push OFFSET yourNumber
push OFFSET newString
push OFFSET userIntegers
call writeVal                                          ; read in array of integers and convert to string then print

call CrLf 

push OFFSET theAverage                                 ; push parameters
push OFFSET theSum
push OFFSET userIntegers
call findSumAve                                        ; print sum and average of integers


call CrLf                                              ; say goodbye
mov edx, OFFSET goodbye
call WriteString
call CrLf

 mov eax, 10000                                        ;delaying program from closing screen so we can read results.
     call Delay


	exit	; exit to operating system
main ENDP

;------------------------------------------------------------------------------------
; ReadVal --- USES and CHANGES EBX, EDX, EAX, ECX, ESI, EDI, DL, AL -
; reads in a number from user using getString macro and converts string
; into integer. Stores all converted numbers in array
; Receives: address of:  outofRange message, userPrompt, get string prompt
; integer value, integer array and user input array. Must push data on stack
; in specified order:
;    : out of range message
;    : userPrompt message
;    : prompt to get number in string format
;    : address of DWORD variable
;    : address of array to store converted integers
;    : address of string buffer to use for user input
; Returns: an array of integers stored at address of for storing converted integers
;-------------------------------------------------------------------------------------

ReadVal PROC

     push ebp
     mov  ebp, esp
     mov edx, [ebp+24]                       ; user prompt
     call WriteString
     call CrLf
     mov  ecx, 10                            ; amount of numbers for user to enter
     mov  eax, 0              
     mov [ebp+16], eax                       ; intialize integer value
     mov edi, [ebp+12]                       ; point to array for converted integers
    
Loop1:
     
     GetString
     push ecx                                ; remember ecx
     mov  ecx, byteCount 
     mov  esi, [ebp +8]                      ; point to the user entered string
     cmp  ecx, 11                            ; check to see if number has too many digits
     jge  OutofRange
Loop2:
     cld
     mov  eax, 0
     lodsb                                   ; load data into eax, test for range, then convert to integer
     mov  dl, al
     mov  eax, [ebp+16]
     cmp  dl, 48
     jl   OutofRange
     cmp  dl, 57
     jg   OutofRange
     push edx
     mov  ebx, 10
     mul  ebx
     ;jc   OutofRange
     pop edx
     sub  dl, 48
     movzx  edx, dl
     add  eax, edx
     mov  [ebp+16] ,eax
     jmp contLoop

OutofRange:                                  ; display out of range message if non-number
     
     mov  edx, [ebp +28]
     call WriteString
     pop ecx
     jmp Loop1
contLoop:
     loop Loop2


     mov [edi], eax                          ; store integer in converted integer array
     mov  eax, 0
     mov [ebp+16], eax
     add  edi, 4
     pop ecx
     loop Loop1

     jmp quit



quit:
     pop ebp

ret 24

ReadVal ENDP

;------------------------------------------------------------------------------------
; WriteVal --- USES and CHANGES EBX, EDX, EAX, ECX, ESI, EDI -
; reads in a number from user using getString macro and converts string
; into integer. Stores all converted numbers in array
; Receives: address of:  outofRange message, userPrompt, get string prompt
; integer value, integer array and user input array. Must push data on stack
; in specified order:
;    : out of range message
;    : userPrompt message
;    : prompt to get number in string format
;    : address of DWORD variable
;    : address of array to store converted integers
;    : address of string buffer to use for user input
; Returns: an array of integers stored at address of for storing converted integers
;-------------------------------------------------------------------------------------

writeVal PROC

     push ebp                                     ; set up stack frame
     mov  ebp, esp
     mov  esi, [ebp+8]
     mov  ecx, 10
     mov ebx, 0
     mov  edx, [ebp +16]                          ; display, 'your number....'
     call WriteString
     call CrLf
     jmp Loop3

printcomma:
     mov edx,  [ebp+20]                           ; display comma
     call WriteString 

Loop3:
    
    ; push [ebp+12]                                ; clear buffer                               
     ;call clearEdi                               ; THIS IS AN UPDATE

     mov  edi, [ebp+12]
     mov  eax, [esi]                              
     add  esi, 4


intToString:                                      ; convert the int to string

     mov edx,  0
     mov  ebx, 10
     div ebx
     add  dl, 48
     push eax
     mov  eax, edx
     stosb
     pop eax
     cmp eax, 0
     jne intToString                              ; move to next digit
   mov eax, 0                                     ; THIS IS AN UPDATE -- add NULL terminator to string
   mov  [edi], eax                                ; THIS IS AN UPDATE
     push [ebp +12]
     call reverseString                           ; reverse order of string
     displayString                                ; display string
     loop printcomma                              ; loop back and print a comma
         
     pop ebp
     ret 16

writeVal ENDP

;------------------------------------------------------------------------------------
; reverseString --- USES and CHANGES EDX, ESI, EDI, AL, BL -
; reverses characters in string
; Receives: address of:  string to reverse
; Returns: a string in reverse order
;-------------------------------------------------------------------------------------


reverseString PROC
     push ebp
     mov ebp, esp

     push edx
     push esi
     push edi
     mov edx, [ebp+8]
     mov esi, [ebp+8]
     mov edi,[ebp+8]
     dec edi

keepGoing:                                        ; find end of array
     inc edi
     mov  al, [edi]
     cmp  al, 0
     jnz keepGoing
     dec edi

swap:
     cmp esi, edi                                 ; if esi and edi are not equal swap the values of both
     jge quit
     mov  al, [edi]
     mov  bl, [esi]
     mov  [esi], al
     mov  [edi], bl
     inc esi
     dec edi
     jmp swap

 quit:
     pop edi
     pop esi
     pop edx
     pop ebp

ret 4
reverseString ENDP

;------------------------------------------------------------------------------------
; clearEdi --- USES and CHANGES ECX,EAX, EDI -
; Clears value in an array of chars
; Receives: address of:  array of chars   
; Returns: an array of 0
;-------------------------------------------------------------------------------------



clearEdi PROC
    
     push ecx
     push ebp
     mov  ebp, esp
     mov  edi, [ebp+12]
     mov  ecx, 20
     mov  eax, 0
goOn:                                        ; loop through filled array elements and change value to 0
    mov [edi], eax
    inc edi
    loop  goOn
 
    pop ebp
    pop ecx
   
    ret 4
clearEdi ENDP


;------------------------------------------------------------------------------------
; findSumAve --- USES and CHANGES EBX, EAX, ESI, EDX -
; finds and prints the sum and average of an array of integers
; Receives: an array of integers
; Returns: prints the average of sum of the array of integers
;-------------------------------------------------------------------------------------

findSumAve PROC
     push ebp
     mov ebp, esp
     mov  esi, [ebp+8]
     mov  eax, 0
     mov  ecx, 10
keepAdding:                                            ; add up all numbers in array
     mov  ebx, [esi]
     add  eax, ebx
     add esi, 4
     loop keepAdding

     mov  edx, [ebp +12]                               ; print the sum
     call WriteString
     call CrLf
     call WriteDec
     call CrLf

     mov  edx, [ebp+16]                                 ; find average and print
     call WriteString
     call CrLf
     mov  edx, 0
     mov  ebx, 10
     div ebx
     call WriteDec
     pop ebp

     ret 16


findSumAve ENDP

END main