[ org 0x7C00 ] 
[ BITS 16 ]
; https://www.cs.bham.ac.uk/~exr/lectures/opsys/10_11/lectures/os-dev.pdf; page 18.
; Effectively, it allows us to put an offset of 0x7c00 on the assembly addresses -
; meaning that we are clear of the BIOS vector tables/configurations in the memory.

KERNEL_ENTRY  equ 0x1000 ; this is where we set up the kernel entry function to be

mov   [boot_addr], dl ; the BIOS stores boot drive address in dl on startup.
mov   bp, 0x8000 ; set up the stack temporarily - this will be changed during 32-bit init
mov   sp, bp

; bx => location where the memory is read
; dh => number of sectors to read
; cl => origin sector
mov   bx, 0x1000
mov   dh, 19
mov   cl, 2
call  read_disk 
; we can utilize the BIOS read functiony ONLY before switching to protected mode -
; as switching to 32 bit makes the 16-bit BIOS routines useless. So we load our 
; kernel **before** we make the jump to 32-bit.

mov   ax, PM_INIT
call  prints16
call  init_gdt ; switch to 32-bit protected mode, by setting cr0 to 1.

%include "gdt.asm"
%include "teletype.asm"
%include "disk.asm"

[ bits 32 ]
_start:
  call  KERNEL_ENTRY ; LEROOOOOOYYYYYYYY JENKIIIIIIINS!
  jmp $ ; hang the CPU. in practice this where the kernel event loop is

PM_INIT:   db "Jumping into protected mode...", 0x0
boot_addr: db 0

times 510-($-$$) db 0

db 0x55
db 0xAA