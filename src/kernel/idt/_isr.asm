; this file serves as the "stub" file for handling interrupts

[ bits 32 ]

[ extern handle_interrupts ]

isr_stub:
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
    call    handle_interrupts
    add     esp, 4

    pop     eax
    mov     ds, ax
    mov     es, ax
    mov     fs, ax
    mov     gs, ax

    popad
    add     esp, 8 ; remove the 2 DWORDs added in the interrupt calls

    sti
    iret

[ global isr0 ]
isr0:
    cli
    push    0
    push    0
    jmp     isr_stub

[ global isr1 ]
isr1:
    cli
    push    0
    push    1
    jmp     isr_stub

[ global isr2 ]
isr2:
    push    0
    push    2
    jmp     isr_stub

[ global isr3 ]
isr3:
    cli
    push    0
    push    3
    jmp     isr_stub

[ global isr4 ]
isr4:
    cli
    push    0
    push    4
    jmp     isr_stub

[ global isr5 ]
isr5:
    cli
    push    5
    push    5
    jmp     isr_stub

[ global isr6 ]
isr6:
    cli
    push    0
    push    6
    jmp     isr_stub

[ global isr7 ]
isr7:
    cli
    push    0
    push    7
    jmp     isr_stub

[ global isr8 ]
isr8:
    cli
    push    byte 8
    jmp     isr_stub

[ global isr9 ]
isr9:
    cli
    push    0
    push    9
    jmp     isr_stub

[ global isr10 ]
isr10:
    cli
    push    10
    jmp     isr_stub

[ global isr11 ]
isr11:
    cli
    push    11
    jmp     isr_stub


[ global isr12 ]
isr12:
    cli
    push    12
    jmp     isr_stub

[ global isr13 ]
isr13:
    cli
    push    13
    jmp     isr_stub

[ global isr14 ]
isr14:
    cli
    push    14
    jmp     isr_stub

[ global isr15 ]
isr15:
    cli
    push    byte 0
    push    byte 15
    jmp     isr_stub

[ global isr16 ]
isr16:
    cli
    push    0
    push    16
    jmp     isr_stub

[ global isr17 ]
isr17:
    cli
    push    17
    jmp     isr_stub

[ global isr18 ]
isr18:
    cli
    push    0
    push    18
    jmp     isr_stub

[ global isr19 ]
isr19:
    cli
    push    0
    push    19
    jmp     isr_stub

[ global isr20 ]
isr20:
    cli
    push    0
    push    20
    jmp     isr_stub

[ global isr21 ]
isr21:
    cli
    push    21
    jmp     isr_stub

[ global isr28 ]
isr28:
    cli
    push    0
    push    28
    jmp     isr_stub

[ global isr29 ]
isr29:
    cli
    push    29
    jmp     isr_stub

[ global isr30 ]
isr30:
    cli
    push    30
    jmp     isr_stub
