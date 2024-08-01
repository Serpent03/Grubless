; we'll end up here after coming from the idt_install() function call.

[ bits 32 ]
[ global load_idt ]
load_idt:
    push    ebp
    mov     ebp, esp
    ; all my homies hate the motherfucking stack.
    ; The IDT table argument was at ebp + 8 **after** pushing the stack.
    ; I was trying to access it at ebp + 8 without pushing the stack...

    mov     eax, [ebp + 8] 
    lidt    [eax]
    mov     esp, ebp
    pop     ebp
    ret


