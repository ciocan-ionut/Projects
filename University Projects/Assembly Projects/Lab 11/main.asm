bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, printf, baza8
import exit msvcrt.dll
import printf msvcrt.dll

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    format_afisare db "Numarul %u este in baza 8 egal cu %s si reprezinta caracterul '%c' in codul ASCII", 10, 0
; our code starts here
segment code use32 class=code
    start:
        ; ...
        mov ecx, 32
        repeta:
            mov eax, ecx
            push eax
            call baza8
            
            mov ebx, ecx
            push ecx
            push edi
            push ecx
            push dword format_afisare
            call [printf]
            add esp, 16
            
            mov ecx, ebx
            inc ecx
            cmp ecx, 126
            jbe repeta
            
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
