[ bits 16 ]
[ org 0x7C00 ] 
; https://www.cs.bham.ac.uk/~exr/lectures/opsys/10_11/lectures/os-dev.pdf; page 18.
; Effectively, it allows us to put an offset of 0x7c00 on the assembly addresses -
; meaning that we are clear of the BIOS vector tables/configurations in the memory.

mov   [boot_addr], dl ; the BIOS stores boot drive address in dl on init.

mov   eax, 0x8000
mov   ebp, 0x8000 ; @fix enable this through the stack segment instead.
mov   esp, ebp ; @fix ebp is showing 0x0000 during printwln calls for some reason.

jmp   _start ; this is required. otherwise it will start routines in the teletype.asm file.

%include "teletype.asm"
%include "math.asm"
%include "utils.asm"
%include "disk.asm"

; @todo Read CHS 0 to load OS(??)
; @todo Enable 32-bit protected mode
; @todo Get an entry into the main() C routine
; @todo File system implementation? FAT16 please..

_start: ; this is pretty much where the bootloader logic starts.

  ; @todo fix the drive read errors.
  mov   dh, 5
  mov   dl, [boot_addr] ; drive address ?
  call  read_disk

  mov   eax, [0x9000]
  call  printwln


msg   db "Hi", 0x0
boot_addr: db 0

jmp $

times 510-($-$$) db 0

db 0x55
db 0xAA


times 256   dw 0xdada ; for now, this is our boot drive
times 256   dw 0xface ; since BIOS only loads the first 512 bytes
; we can verify if it read beyond that, by allocating the total file to be more than 512 bytes.
