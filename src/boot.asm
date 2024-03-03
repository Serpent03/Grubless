[ bits 16 ]
[ org 0x7C00 ] 
; https://www.cs.bham.ac.uk/~exr/lectures/opsys/10_11/lectures/os-dev.pdf; page 18.
; Effectively, it allows us to put an offset of 0x7c00 on the assembly addresses -
; meaning that we are clear of the BIOS vector tables/configurations in the memory.

mov   [boot_addr], dl ; the BIOS stores boot drive address in dl on init.

mov   ebp, 0x8000 ; @fix enable this through the stack segment instead.
mov   esp, ebp ; @fix ebp is showing 0x0000 during printwln calls for some reason.

jmp   _start ; this is required. otherwise it will start routines in the teletype.asm file.

%include "teletype.asm"
%include "math.asm"
%include "utils.asm"
%include "disk.asm"

; @todo Enable 32-bit protected mode
; @todo Get an entry into the main() C routine
; @todo File system implementation? FAT16 please..

_start: ; this is pretty much where the bootloader logic starts.

  mov   bx, 0x9000
  mov   dh, 1 ; number of sectors to read
  mov   dl, [boot_addr] ; drive address as reported by BIOS on init
  call  read_disk

  mov   eax, 0x9000
  call  printsln


boot_addr: db 0

jmp $

times 510-($-$$) db 0

db 0x55
db 0xAA


times 512   db '!' ; for now, this is our boot drive
times 1     db "HI THERE FROM THE OS LAND!!", 0x0
times 256   dw 0xface ; since BIOS only loads the first 512 bytes
; we can verify if it read beyond that, by allocating the total file to be more than 512 bytes.
