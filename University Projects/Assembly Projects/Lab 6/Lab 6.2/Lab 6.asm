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
        s dw 2, -1, 2, 3, -7, 8, 4, 5, 6, 7, -3, -2, -1
        l equ ($-s)/2
        lung_max dd 0
        sfarsit dw 0
        d times l dw 0
    ; our code starts here
    segment code use32 class=code
        start:
            ; ...
            mov ECX, l
            jecxz final
            mov ESI, s
            
            LODSW
            mov BX, AX
            mov EDX, 1
            
            while_1:
                LODSW
                cmp BX, AX
                jg break
                inc EDX
                jmp gata
            
            break:
                cmp EDX, [lung_max]
                jle continue
                mov EDI, l
                sub EDI, ECX
                inc EDI
                mov [sfarsit], EDI
                mov [lung_max], EDX
                
                continue:
                    mov EDX, 1
            
            gata:
                mov BX, AX
                loop while_1
            
            mov ECX, [lung_max]
            jecxz final
            mov AX, [sfarsit]
            sub AX, [lung_max]
            mov BX, 2
            imul BX
            CWDE
            mov ESI, s
            add ESI, EAX
            mov EDI, d
            
            while_2:
                MOVSW
                loop while_2
            
            final:
            ; exit(0)
            push    dword 0      ; push the parameter for exit onto the stack
            call    [exit]       ; call exit to terminate the program
