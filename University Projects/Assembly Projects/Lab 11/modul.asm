bits 32 ; assembling for the 32 bits architecture
global baza8
segment data use32 class=data
    numar resb 10
segment code use32 class=code
    baza8:
        mov eax, [esp+4]
        mov ebx, 8
        lea edi, [numar + 9]
        mov byte [edi], 0
        repeta:
            xor edx, edx
            div ebx
            add dl, '0'
            dec edi
            mov [edi], dl
            cmp eax, 0
            jnz repeta
        ret 4