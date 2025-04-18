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
    S1 db 1, 2, 3, 4
    l1 equ $-S1
    S2 db 5, 6, 7
    l2 equ $-S2
    D times l1+l2 db 0
; our code starts here
segment code use32 class=code
    start:
        ; ...
        mov ECX, l1
        jecxz jump_S1
        mov ESI, 0
        
        while_S1:
        mov AL, [S1+ESI]
        mov [D+ESI], AL
        inc ESI
        loop while_S1
        
        jump_S1:
        mov ECX, l2
        jecxz final
        mov EDI, l2-1
        
        while_S2:
        mov AL, [S2+EDI]
        mov [D+ESI], AL
        dec EDI
        inc ESI
        loop while_S2
        
        final:
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
