TITLE CS271 Assignment 5 - Passing Parameters     (Assignment 5.asm)

; Author: Vijay Kumar
; Course / Project ID CS 271 Assignment #5                Date: 5/10/16
; Description: Create array with random integers then print in unsorted and sorted order. 

INCLUDE Irvine32.inc

; (insert constant definitions here)

LO = 100
HI = 999
MIN =  10
MAX = 200

.data

programTitle   BYTE "Program: Sorting Random Integers",0
programDesc    BYTE "This program generates random numbers in the range [100...999], displays the original list, sorts the list, and calculates the median value. Finally , it display the list sorted in descending order.", 0

myName         BYTE "Programmer: Vijay Kumar",0
prompt1        BYTE "How many numbers should be generated? [10...200].",0
invInput       BYTE "Invalid Input. Let's try again.", 0
unsorted       BYTE "Our unsorted array is: ", 0
sorted         BYTE "Our sorted array is: ", 0
median         BYTE "The median is:  ", 0
spaces         BYTE "   ", 0
userInput      DWORD ?;
list           DWORD     190 DUP(?)
count          DWORD ?;
range          DWORD ?;

.code
main PROC
    call Randomize                                               ; seed random number generator

; Introduce Program

     call intro
     jmp L2

; Get Data From User
L1:
     mov  edx, OFFSET    invInput                                ; invalid input
     call WriteString
     call CrLf

L2:
     push OFFSET userInput                                       ; get user input
     call getUserInput
     call CrLf

; validate user input

     mov  eax, userInput                                         ; validate user input
     cmp eax, MIN
     jl L1
     cmp eax, MAX
     jg L1

; Fill array with Random Numbers
     mov  eax, HI                                                ; calculate the range for random numbers
     sub  eax, LO
     add  eax, 1
     mov  range, eax

     push range
     push OFFSET list
     push userInput
     call fillArray

; display unsorted list
     
     push OFFSET    unsorted
     push OFFSET    list
     push userInput
     push OFFSET    spaces
     call displayList
     call CrLf

; Sort array
     push OFFSET list
     push userInput
     call bubbleSortArray

; Display median value

     push OFFSET    median
     push OFFSET    list
     push userInput
     call displayMedian
     call CrLf
 

; display list Sorted list

     push OFFSET    sorted
     push OFFSET list
     push userInput
     push OFFSET spaces
     call displayList

     mov eax, 10000                                         ;delaying program from closing screen so we can read results.
     call Delay

	exit	; exit to operating system
main ENDP

; (insert additional procedures here)
;-----------------------------------------------------------------------
; intro 
; introduces program to user 
;-----------------------------------------------------------------------


intro PROC
     mov  edx, OFFSET    programTitle                  ;write program title
     call WriteString
     call CrLf
     mov  edx, OFFSET    programDesc                   ;write program title
     call WriteString
     call CrLf
     mov  edx, OFFSET    myName                        ;write my name
     call WriteString
     call CrLf

ret

intro ENDP

;-----------------------------------------------------------------------
; getUserInput --- USES and CHANGES EBX, EDX, EAX -
; gets input from user and stores it in userInput variable
; Receives: address of userInput variable
; Returns: userInput variable is set with user selected value
;-----------------------------------------------------------------------

getUserInput PROC

     push ebp                                          ; set up stack frame
     mov  ebp, esp
     ; get an integer from user
     mov  edx, OFFSET    prompt1                       ;ask user for input
     call WriteString
     call CrLf
     call ReadInt
     mov ebx,  [ebp+8]
     mov [ebx],  eax
     pop ebp
     ret 4
getUserInput ENDP


;-----------------------------------------------------------------------
; fillArray --- USES and CHANGES ECX, EAX, ESI-
; fills array with random numbers within a specified range
; Receives: Int Range, address of array
; Returns: array is filled with random numbers within a certain range
;-----------------------------------------------------------------------

fillArray PROC

     push ebp
     mov  ebp, esp
     mov  esi, [ebp+12]                                ; point esi at first element of array
     mov  ecx, [ebp+8]                                 ; initialize ecx with number of elements to be added

moreInput:
     mov  eax, [ebp+16]                                ; move the range to eax
     call RandomRange
     add  eax, LO
     mov [esi], eax                                    ; add random number to array
     add  esi, 4                                       ; increment to next element
     loop moreInput

     pop ebp
     ret 12

fillArray ENDP

;-----------------------------------------------------------------------
; displayList --- USES and CHANGES EBX, EDX, ECX, ESI, EAX -
; displays the current contents of array in rows of 10
; Receives: address of array,number of elements in the array, and display title
; Returns: prints numbers in an array in rows of 10, returns nothing
;-----------------------------------------------------------------------


displayList PROC
     
     push ebp
     mov  ebp, esp
     mov  edx, [ebp+20]
     call WriteString
     call CrLf
     mov  esi, [ebp+16]                                ; point esi at first element of array
     mov  ecx, [ebp+12]                                ; intialize counter
     mov  edx, [ebp+8]                                 ; assign 'spaces' string to edx
     mov  ebx, 0                                       ; intialize ebx to count number of elements printed
printNum:
     mov  eax, [esi]                                   ; print 10 numbers per line
     call WriteDec
     call WriteString
     add  esi, 4
     inc ebx
     cmp ebx, 10
     jge newLine                                       ; if 10 elements have been printed print new line then loop
     loop printNum
     jmp getOuttaHere
     newLine:
          call CrLf
          mov  ebx, 0
          loop printNum

getOuttaHere:
     call CrLf
     pop ebp
     ret 16

displayList ENDP


;-----------------------------------------------------------------------
; bubbleSortArray --- USES and CHANGES ECX, ESI, EAX -
; sorts the agrument array in descending order
; Receives: address of array, size of array
; Returns: array in descending sorted order
; Reference/Cite: Bubble sort from Assembly Language Text, page 375
;-----------------------------------------------------------------------


bubbleSortArray PROC

     push ebp
     mov  ebp, esp
     mov  ecx, [ebp+8]
     dec ecx        
L1:                                                    ; outer loop of bubble sort
     push ecx
     mov  esi, [ebp+12]                                ; start loop at beginning of array

L2:
     mov  eax, [esi]                                   ; swap numbers if out of order
     cmp  [esi+4], eax
     jl L3
     xchg eax, [esi+4]
     mov  [esi], eax
L3:
     add  esi, 4                                       ; increment esi then loop    
     loop L2

     pop ecx
     loop L1
L4: 
     pop ebp
     ret 8

bubbleSortArray ENDP


;-----------------------------------------------------------------------
; displayMedian --- USES and CHANGES EBX, EDX, ECX, ESI, EAX -
; finds the median value of a sorted array
; Receives: address of array, size of array, and display title
; Returns: prints the median number in the array
;-----------------------------------------------------------------------


displayMedian PROC

     push ebp
     mov  ebp, esp
     mov  edx, [ebp+16]
     call WriteString
     call CrLf
     mov eax, [ebp+8]                        ; move the number of elements in array to eax
     mov esi, [ebp+12]                       ; point esi to first element of array
     mov ebx, 2                              ; find if number of elements in array is even
     cdq
     div ebx
     cmp edx, 0
     jz useTwo                               

     mov ecx, 4                              ; print middle index of array
     mul ecx
     add esi, eax
     mov eax, [esi]
     call WriteDec
     jmp closeItUp

useTwo: 
     mov ecx, 4                              ; print the rounded average of the two middle-most numbers in the array
     mul ecx
     add  esi, eax
     mov  ebx, [esi]
     add esi, 4
     mov eax, [esi]
     add  eax, ebx
     mov  ebx, 2
     cdq
     div  ebx
     call WriteDec

closeItUp:
     call CrLf
     pop ebp
     ret 12

displayMedian ENDP

END main