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
    A db 12
    B dw 269
; our code starts here
segment code use32 class=code
    start:
        ; ...
        xor EAX, EAX
        xor ECX, ECX
        mov CL, [A]
        shl ECX, 24
        or EAX, ECX
        
        xor ECX, ECX
        mov BX, [B]
        mov CL, BL
        not CL
        shl ECX, 16
        or EAX, ECX
        
        xor ECX, ECX
        mov ECX, 00111111b
        shl ECX, 10
        or EAX, ECX
        
        xor ECX, ECX
        mov CL, BH
        shl ECX, 2
        or EAX, ECX
        
        xor ECX, ECX
        mov CL, [A]
        shr CL, 7
        or EAX, ECX
        
        ; EAX = C
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
