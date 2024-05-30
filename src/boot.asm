[ org 0x7C00 ] 
[ BITS 16 ]
; https://www.cs.bham.ac.uk/~exr/lectures/opsys/10_11/lectures/os-dev.pdf; page 18.
; Effectively, it allows us to put an offset of 0x7c00 on the assembly addresses -
; meaning that we are clear of the BIOS vector tables/configurations in the memory.

; @todo figure out how to read a mounted device(in this case, /hd0)
mov   [boot_addr], dl ; the BIOS stores boot drive address in dl on init.
mov   ebp, 0x8000 ; @fix enable this through the stack segment instead.
mov   esp, ebp ; @fix ebp is showing 0x0000 during printwln calls for some reason.

jmp   _load_protected_mode ; this is required. otherwise it will start routines in the teletype.asm file.
jmp $

[ BITS 32 ]
%include "teletype.asm"
%include "math.asm"
; %include "utils.asm"
; %include "disk.asm"
%include "gdt.asm"

; @todo translate all 16-bit routines to 32-bit.
; @todo Get an entry into the main() C routine
; @todo get address of secondary drives
; @todo File system implementation? FAT16 please..

_load_protected_mode:
  ; this calls the init_gdt routine, which calls the 
  ; _start routine. in between, the GDT table is installed,
  ; and we switch to the protected memory mode(32-bit).
  call  init_gdt

_start:
  mov   eax, data
  call  prints
  jmp $ ; this infinite loops need to be here, otherwise the CPU bugs out and restarts.

data:   db "Hello world from the 32-bit OS!", 0x0
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
