bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    a DB 1
    b DB 1
    c DB 3
    d DW 4
; our code starts here
segment code use32 class=code
    start:
        ; ...
        mov AL, [b]
        sub AL, [a]
        add AL, 2
        mov CL, 20
        mul CL
        mov BL, AL
        mov CL, 10
        mov AL, [c]
        mul CL
        sub BL, AL
        mov AL, BL
        mov CL, 3
        mul CL
        mov BL, AL
        mov AL, [d]
        sub AL, 3
        mov CL, 2
        mul CL
        add BL, AL
        ; 3 * [20 * (b - a + 2) - 10 * c] + 2 * (d - 3) = 32
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
