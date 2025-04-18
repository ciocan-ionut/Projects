bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, fopen, fprintf, fclose ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
import fopen msvcrt.dll   ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
import fprintf msvcrt.dll
import fclose msvcrt.dll

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    nume_fisier db "laborator 8.txt", 0
    modalitate db "w", 0
    format db "%s", 0
    text db "Ana, are. 7? MERE:"
    l equ $-text
    d times l+1 db 0
    descriptor dd 0
; our code starts here
segment code use32 class=code
    start:
        ; Se dau un nume de fisier si un text (definite in segmentul de date). Textul contine litere mici, litere mari, cifre si caractere speciale. Sa se inlocuiasca toate caracterele speciale din textul dat cu caracterul 'X'. Sa se creeze un fisier cu numele dat si sa se scrie textul obtinut in fisier.
        mov ECX, l
        jecxz final
        
        mov ESI, text
        mov EDI, d
        while_text:
            lodsb
            cmp AL, '0'
            jge is_digit
            
            pune_x:
                mov AL, 'X'
                stosb
                jmp gata
                
            is_digit:
                cmp AL, '9'
                jg is_big_letter
                stosb
                jmp gata
                
            is_big_letter:
                cmp AL, 'A'
                jl pune_x
                cmp AL, 'Z'
                jg is_small_letter
                stosb
                jmp gata
                
            is_small_letter:
                cmp AL, 'a'
                jl pune_x
                cmp AL, 'z'
                jg pune_x
                stosb
                
            gata:
        loop while_text
        
        push dword modalitate
        push dword nume_fisier
        call [fopen]
        add ESP, 4 * 2
        cmp EAX, 0
        je final
        mov [descriptor], EAX
        
        push dword d
        push dword format
        push dword [descriptor]
        call [fprintf]
        add ESP, 4 * 3
        cmp EAX, 0
        je final
        
        push dword [descriptor]
        call [fclose]
        final:
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
