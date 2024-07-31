; this file is a placeholder. when we call the kernel offset address 
; in the bootsector file, we call this file(which is at the start of the
; kernel structure) to ensure that we **only** enter main(), instead of 
; some other function that per-chance got inserted into memory before main().

[ bits 32 ]
[ extern kernel_setup ]
call    kernel_setup
jmp     $