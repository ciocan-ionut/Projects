bits 32 ; assembling for the 32 bits architecture

global _afisare

extern _printf

segment data public data use32
    format_afisare db "Numarul %u este in baza 8 egal cu %u si reprezinta caracterul '%c' in codul ASCII", 10, 0
segment code public code use32
    _afisare:
        push ebp
        mov ebp, esp
        
        mov eax, [ebp + 8]
        mov ebx, [ebp + 12]
        mov edx, eax
        
        push edx
        push ebx
        push eax
        push dword format_afisare
        call _printf
        add esp, 4*3
        
        mov esp, ebp
        pop ebp
        ret