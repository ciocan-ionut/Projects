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
    a DB 3
    b DW 1
    c DD 8
    d DQ 2
; our code starts here
segment code use32 class=code
    start:
        ; F.S. ex 7
        mov EBX, [c]
        mov ECX, 0
        mov EAX, [d]
        mov EDX, [d+4]
        add EAX, [d]
        adc EDX, [d+4]
        add EAX, [d]
        adc EAX, [d+4]
        sub EBX, EAX
        sbb ECX, EDX 
        mov EAX, 0
        mov AL, [a]
        sub AX, [b]
        mov EDX, 0
        add EBX, EAX
        adc ECX, EDX
        ; c - (d + d + d) + (a - b) = 4
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
