TITLE Composite Numbers     (Assignment4.asm)

; Author: Vijay Kumar
; Course / Project ID CS 271 - Assignment 4                Date: 5/2/16
; Description: Program asks user to choose a specific amount of composite numbers to be printed
; then prints the alloted amount of composite numbers, 10 per row.

INCLUDE Irvine32.inc

; (insert constant definitions here)
UPPERLIMIT = 400

.data

; (insert variable definitions here)
programTitle   BYTE "Program: Composite Numbers",0
myName         BYTE "Programmer: Vijay Kumar",0
prompt1        BYTE "Hi there. My name is Vijay. What's your name?",0
prompt2        BYTE "Great to meet you, ", 0
prompt3        BYTE "How many Composite numbers would you like to see? Please enter a number between 1 and 400",0
goodBye        BYTE "Here are your composite numbers. Thanks for playing. Good-Bye, ",0
period         BYTE ".",0
userName       BYTE 50   DUP(0)                        ; stores user name
firstNum       DWORD      3                            ; stores user selected first number
spaces         BYTE "   ",0
secondNum      DWORD      1                            ;stores user selected second number
counter        WORD      0                             ; counts number of printed lines
outOfRangeMess BYTE      "Please enter a number between 1 and 400. Thanks!",0
tempVar        DWORD ?


.code
main PROC

; (introduction)
;//////////////////////////////////////////////////////////////////////////////////////
; Program introduction - display program title, extra credit and programmer's name
; This section print all details about program
;////////////////////////////////////////////////////////////////////////////////////

     mov  edx, OFFSET    programTitle                  ;write program title
     call WriteString
     call CrLf
     mov  edx, OFFSET    myName                        ;write my name
     call WriteString
     call CrLf

;///////////////////////////////////////////////////////////////////////////////
; Ask the user for name then greet user with name
; This section prompts the user for their name then greets them using their name
;///////////////////////////////////////////////////////////////////////////////

     mov  edx, OFFSET    prompt1                       ;greet user
     call WriteString
     call CrLf
     mov  edx, OFFSET    userName                      ;point to the buffer
     mov  ecx, SIZEOF    userName                      ;set max characters
     call ReadSTring                                   ;get input
     mov  edx, OFFSET prompt2                          ;say hello using user name
     call WriteString
     mov  edx, OFFSET userName                    
     call WriteString
     mov  edx, OFFSET period
     call WriteString
     call CrLf



;//////////////////////////////////////////////////////////////////////////////////////
; Prompt user to enter the number of Composite numbers to be displayed including the nth term
; This section prompts the user to enter a number. We jump back here if user enters 
; an out of range number
;//////////////////////////////////////////////////////////////////////////////////////

; ask user for numbers

     mov  edx, OFFSET    prompt3                       ;ask for numbers
     call WriteString
     call CrLf

; get user input and validate to ensure number is between 1 and 400
   
UserEntry:
     call ReadInt                                      
     mov  secondNum, eax                               
     cmp eax, 1                                        
     jl RetryUserNum
     cmp eax, UPPERLIMIT
     jg RetryUserNum
     jmp MoveOn

; if user entered number out of range
  
RetryUserNum:                                          
     mov  edx, OFFSET    outOfRangeMess                
     call WriteString
     call CrLf
     jmp UserEntry


;//////////////////////////////////////////////////////////////////////////////////////
;Use isComposite process to show the specific amount of composite numbers
;//////////////////////////////////////////////////////////////////////////////////////


MoveOn:
     call isComposite



;//////////////////////////////////////////////////////////////////////////////////////
; Say Goodbye
;//////////////////////////////////////////////////////////////////////////////////////
bye:
    call CrLf
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

isComposite PROC
     
; set first number and loop counter

     mov  ecx, secondNum                         
     mov  eax,  firstNum                         
     jmp  NewDividendProcess                      

LoopStart:
 
; increment the dividend

NextDividendNum:                                     
     mov eax, tempVar                             
     inc eax                                      
     jmp NewDividendProcess                      

; increment the divisor

NextDivisorNum:                                   
     mov  eax, tempVar                            
     inc ebx                                      
     cmp eax, ebx
     je  NextDividendNum                          
     jmp  contProcess                             
 
; start the dividing process anew and reset divisor to 2

NewDividendProcess:                              
     
     mov  ebx,  2                                
    
; continue the dividing process without resetting the divisor

contProcess:
     mov  tempVar, eax                            
     xor edx, edx                                 
     cdq
     div  ebx                                    
     cmp  edx, 0                                  
     jne  NextDivisorNum                          

; return the eax register to previous dividend and print

     mul  ebx                                                         
     call WriteDec                                
     mov  edx,      OFFSET    spaces              
     call WriteString  
     inc  counter                                 
     cmp counter, 10                              
     jne loopMe
     call CrLf
     mov  counter, 0                              

loopMe:

     loop LoopStart                               


ret                                               

isComposite ENDP



END main