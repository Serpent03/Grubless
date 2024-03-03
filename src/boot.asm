[ bits 16 ]
[ org 0x7C00 ] 
; https://www.cs.bham.ac.uk/~exr/lectures/opsys/10_11/lectures/os-dev.pdf; page 18.
; Effectively, it allows us to put an offset of 0x7c00 on the assembly addresses -
; meaning that we are clear of the BIOS vector tables/configurations in the memory.

jmp   _start ; this is required. otherwise it will start routines in the teletype.asm file.

%include "teletype.asm"
%include "math.asm"
%include "utils.asm"

mov   ebp, 0x8000 ; @fix enable this through the stack segment instead.
mov   esp, ebp

; @todo Enable 32-bit protected mode
; @todo Get an entry into the main() C routine
; @todo Read CHS 0 to load OS(??)
; @todo File system implementation? FAT16 please..

_start: ; this is pretty much where the bootloader logic starts.
  call  debug_regs

  push  0xFFFFFFFF
  call  debug_regs

text  db "Hi there", 0x0
title db "this is the title", 0x0

jmp $

times 510-($-$$) db 0

db 0x55
db 0xAA
