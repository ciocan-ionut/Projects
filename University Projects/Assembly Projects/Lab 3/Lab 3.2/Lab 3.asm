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
    a DB 5
    b DW 17
    c DD 7
    d DQ 13
; our code starts here
segment code use32 class=code
    start:
        ; F.S. ex 21
        mov ECX, [c]
        mov EBX, 0
        mov BL, [a]
        sub ECX, EBX
        push ECX
        mov ECX, 0
        mov BX, [b]
        mov EAX, [d]
        mov EDX, [d+4]
        sub EBX, EAX
        sbb ECX, EDX
        add EBX, EAX
        adc ECX, EDX
        pop EAX
        mov EDX, 0
        add EAX, EBX
        adc EDX, ECX
        ; (c - a) + (b - d) + d = 19
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
