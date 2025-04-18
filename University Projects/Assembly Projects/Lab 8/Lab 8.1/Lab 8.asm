bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
extern scanf              ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
import scanf msvcrt.dll
extern printf
import printf msvcrt.dll

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    a dd 0
    b dd 0
    format_scan db "%d", "%d", 0
    format_print db "%x", 0
; our code starts here
segment code use32 class=code
    start:
        ; Sa se citeasca de la tastatura doua numere a si b (in baza 10) si sa se calculeze a+b. Sa se afiseze rezultatul adunarii in baza 16.
        push dword b
        push dword a
        push dword format_scan
        call [scanf]
        add ESP, 4 * 3
        
        mov EBX, [a]
        add EBX, [b]
        
        push EBX
        push dword format_print
        call [printf]
        add ESP, 4 * 2
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
