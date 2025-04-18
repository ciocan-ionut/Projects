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
    a DB 11
    b DW -3
    c DD -1
    d DQ 21
; our code starts here
segment code use32 class=code
    start:
        ; C.S. ex 7
        mov EBX, [c]
        add EBX, [c]
        add EBX, [c]
        mov AX, [b]
        CWDE
        sub EBX, EAX
        push EBX
        mov AL, [a]
        CBW
        CWDE
        CDQ
        mov EBX, [d]
        mov ECX, [d+4]
        sub EBX, EAX
        sbb ECX, EDX
        pop EAX
        CDQ
        add EAX, EBX
        adc EDX, ECX
        ; (c + c + c) - b + (d - a) = 10
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the programc