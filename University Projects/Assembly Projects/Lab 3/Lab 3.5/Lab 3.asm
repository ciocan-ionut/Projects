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
    a DB 8
    b DB 1
    c DW 2
    e DD 12
    x DQ 8
; our code starts here
segment code use32 class=code
    start:
        ; F.S. p2 ex 7
        mov AX, 0
        mov DX, 0
        mov AL, [a]
        sub AL, 2
        mov BX, 0
        mov BL, [b]
        add BX, [c]
        div BX
        mov EBX, 0
        mov BX, AX
        mov AX, 0
        mov AL, [a]
        mov CX, [c]
        mul CX
        push DX
        push AX
        pop EAX
        add EAX, EBX
        add EAX, [e]
        mov EDX, 0
        mov EBX, [x]
        mov ECX, [x+4]
        sub EAX, EBX
        sbb EDX, ECX
        ; (a - 2) / (b + c) + a * c + e - x = 22
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
