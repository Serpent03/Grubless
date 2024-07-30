[ org 0x7C00 ] 
[ BITS 16 ]
; https://www.cs.bham.ac.uk/~exr/lectures/opsys/10_11/lectures/os-dev.pdf; page 18.
; Effectively, it allows us to put an offset of 0x7c00 on the assembly addresses -
; meaning that we are clear of the BIOS vector tables/configurations in the memory.

mov   [boot_addr], dl ; the BIOS stores boot drive address in dl on init.
mov   bp, 0x8000 ; @fix enable this through the stack segment instead.
mov   sp, bp ; @fix ebp is showing 0x0000 during printwln calls for some reason.

call  read_disk
call  init_gdt

%include "gdt.asm"
%include "teletype.asm"
%include "disk.asm"

[ bits 32 ]
_start:
  ; mov   ax, 0x9000
  ; call  prints16

  mov   eax, 0x9000
  call  prints

  jmp $ ; hang the CPU. in practice this where the kernel event loop is

PM_INIT:   db "Hello world from the 32-bit OS!", 0x0
boot_addr: db 0

times 510-($-$$) db 0

db 0x55
db 0xAA


times 512   db '!' ; 2nd sector
times 256   dw 0xface ; 3rd sector
times 1     db "HI THERE FROM THE OS LAND!!", 0x0 ; 4th sector

; for now, this is our boot drive
; since BIOS only loads the first 512 bytes
; we can verify if it read beyond that, by allocating the total file to be more than 512 bytes.
