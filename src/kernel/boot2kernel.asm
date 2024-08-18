; this file is a placeholder. when we call the kernel offset address 
; in the bootsector file, we call this file(which is at the start of the
; kernel structure) to ensure that we **only** enter main(), instead of 
; some other function that per-chance got inserted into memory before main().

[ bits 32 ]
[ extern kernel_setup ]
[ extern k_main ]
nop     ; these two NOPs are padding
nop     ; we use them to see if we have actually loaded the kernel instructions or not
call    kernel_setup
call    k_main ; this saves me a lot of stack space.
jmp     $