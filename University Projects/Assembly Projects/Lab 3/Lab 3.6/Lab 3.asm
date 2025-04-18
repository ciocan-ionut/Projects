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
    a DB -1
    b DB 0
    c DW -3
    e DD 12
    x DQ 8
; our code starts here
segment code use32 class=code
    start:
        ; C.S. p2 ex 7
        mov AL, [a]
        sub AL, 2
        CBW
        CWDE
        push EAX
        mov AL, [b]
        CBW
        add AX, [c]
        mov BX, AX
        pop AX
        pop DX
        idiv BX
        CWDE
        mov EBX, EAX
        mov AL, [a]
        CBW
        imul word[c]
        push DX
        push AX
        pop EAX
        add EAX, EBX
        add EAX, [e]
        CDQ
        mov EBX, [x]
        mov ECX, [x+4]
        sub EAX, EBX
        sbb EDX, ECX
        ; (a - 2) / (b + c) + a * c + e - x = 8
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
