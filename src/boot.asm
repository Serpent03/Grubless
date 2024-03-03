[ org 0x7C00 ] 
; https://www.cs.bham.ac.uk/~exr/lectures/opsys/10_11/lectures/os-dev.pdf; page 18.
; Effectively, it allows us to put an offset of 0x7c00 on the assembly addresses -
; meaning that we are clear of the BIOS vector tables/configurations in the memory.

; mov bp, 0x8000 
; mov sp, bp

jmp   _start
%include "teletype.asm"

; Moving the ah <- 0E tells the BIOS we're going to commit the 
; TELETYPE ROUTINE. Setting character into al, and then calling
; INT 0x10 lets the BIOS know to put that value at the VMEM address.

; @todo set up the stack and data segment
; @todo Get an entry into the main() C routine
; @todo Read CHS 0 to load OS(??)
; @todo Enable 32-bit protected mode
; @todo File system implementation?

_start:
  mov   eax, text
  call  printsln
  mov   eax, title
  call  prints


text  db "Hi there", 0x0
title db "this is the title", 0x0

jmp $

times 510-($-$$) db 0

db 0x55
db 0xAA
