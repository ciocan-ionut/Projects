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
    a DB -4
    b DW 2
    e DD 7
    x DQ -5
; our code starts here
segment code use32 class=code
    start:
        ; C.S. p2 ex 21
        mov AL, [a]
        imul byte[a]
        CWD
        idiv word[b]
        mov CX, AX
        mov AX, [b]
        imul word[b]
        push DX
        push AX
        pop EBX
        mov AX, CX
        CWDE
        add EAX, EBX
        mov BX, [b]
        add BX, 2
        push EAX
        pop AX
        pop DX
        idiv BX
        CWDE
        add EAX, [e]
        CDQ
        mov EBX, [x]
        mov ECX, [x+4]
        sub EAX, EBX
        sbb EDX, ECX
        ; (a * a / b + b * b) / (2 + b) + e - x = 15
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
