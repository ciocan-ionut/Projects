bits 32
global start        

; declare external functions needed by our program
extern exit, scanf, fopen, fprintf, fclose
import exit msvcrt.dll
import scanf msvcrt.dll
import fopen msvcrt.dll
import fprintf msvcrt.dll
import fclose msvcrt.dll

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    n dd 0
    numar dd 0
    format db "%d", 0
    nume_fisier db "numere2.txt", 0
    descriptor dd 0
    mod_acces db "w", 0
; our code starts here
segment code use32 class=code
    start:
        ; ...
        push dword mod_acces
        push dword nume_fisier
        call [fopen]
        add esp, 8
        
        cmp eax, 0
        je final
        mov [descriptor], eax
        
        push dword n
        push dword format
        call [scanf]
        add esp, 8
        
        citeste:
        push dword numar
        push dword format
        call [scanf]
        add esp, 8
        
        
        mov eax, [numar]
        cmp eax, '$'
        je final
        
        cmp eax, 0
        jge urmatorul
        
        neg eax
        xor edx, edx
        mov ecx, 10
        div ecx
        xor edx, edx
        div ecx
        cmp dl, [n]
        jne urmatorul
        
        push dword [numar]
        push dword format
        push dword [descriptor]
        call [fprintf]
        add esp, 12
        
        urmatorul:
        jmp citeste
        
        final:
        push dword [descriptor]
        call [fclose]
        add esp, 4
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
