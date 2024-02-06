[ org 0x7C00 ] 
; https://www.cs.bham.ac.uk/~exr/lectures/opsys/10_11/lectures/os-dev.pdf; page 18.
; Effectively, it allows us to put an offset of 0x7c00 on the assembly addresses -
; meaning that we are clear of the BIOS vector tables/configurations in the memory.

mov ah, 0x0E

mov al, 'H'
INT 0x10
mov al, 'e'
INT 0x10
mov al, 'l'
INT 0x10
mov al, 'l'
INT 0x10
mov al, 'o'
INT 0x10

; Moving the ah <- 0E tells the BIOS we're going to commit the 
; TELETYPE ROUTINE. Setting character into al, and then calling
; INT 0x10 lets the BIOS know to put that value at the VMEM address.

label:
  db "X"

jmp $

times 510-($-$$) db 0

db 0x55
db 0xAA
