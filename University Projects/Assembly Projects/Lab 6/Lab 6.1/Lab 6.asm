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
    A dd 12343210h, 67891234h, 0123FEDCh
    l equ ($-A)/4
    B1 times l db 0
    B2 times l db 0
; our code starts here
segment code use32 class=code
    start:
        ; ...
        mov ECX, l
        jecxz final
        mov ESI, A
        mov EDI, B1
        
        while_1:
        MOVSB
        add ESI, 3
        loop while_1
        
        mov ECX, l
        mov ESI, A
        mov EDI, B2
        
        while_2:
        add ESI, 3
        MOVSB
        loop while_2
        
        final
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
