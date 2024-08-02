; this file serves as stub for handling irq from PIC

[ bits 32 ]

[ extern irq_handler ]
irq_stub:
    pushad
    
    xor     eax, eax
    mov     ax, ds
    push    eax ; store ds. we will restore it later

    mov     ax, 0x10
    mov     ds, ax
    mov     es, ax
    mov     fs, ax
    mov     gs, ax

    push    esp
    call    irq_handler
    add     esp, 4

    pop     eax
    mov     ds, ax
    mov     es, ax
    mov     fs, ax
    mov     gs, ax

    popad
    add     esp, 8 ; remove the 2 DWORDs added in the interrupt calls

    iret

[ global irq0 ]
irq0:
    cli
    push    0
    push    0
    jmp     irq_stub

[ global irq1 ]
irq1:
    cli
    push     0
    push     1
    jmp     irq_stub

[ global irq2 ]
irq2:
    cli
    push     0
    push     2
    jmp     irq_stub

[ global irq3 ]
irq3:
    cli
    push     0
    push     3
    jmp     irq_stub

[ global irq4 ]
irq4:
    cli
    push     0
    push     4
    jmp     irq_stub

[ global irq5 ]
irq5:
    cli
    push     0
    push     5
    jmp     irq_stub

[ global irq6 ]
irq6:
    cli
    push     0
    push     6
    jmp     irq_stub

[ global irq7 ]
irq7:
    cli
    push     0
    push     7
    jmp     irq_stub
[ global irq8 ]
irq8:
    cli
    push     0
    push     8
    jmp     irq_stub

[ global irq9 ]
irq9:
    cli
    push     0
    push     9
    jmp     irq_stub

[ global irq10 ]
irq10:
    cli
    push     0
    push     10
    jmp     irq_stub

[ global irq11 ]
irq11:
    cli
    push     0
    push     11
    jmp     irq_stub

[ global irq12 ]
irq12:
    cli
    push     0
    push     12
    jmp     irq_stub

[ global irq13 ]
irq13:
    cli
    push     0
    push     13
    jmp     irq_stub

[ global irq14 ]
irq14:
    cli
    push     0
    push     14
    jmp     irq_stub


[ global irq15 ]
irq15:
    cli
    push    0
    push    15
    jmp     irq_stub