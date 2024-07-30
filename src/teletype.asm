[ bits 32 ]

VMEM   equ 0xb8000 ; location of the video memory
WHITE_BLACK   equ 0x0F ; 0xFB :: Foreground color, Background color

prints:
  pusha 
  mov   esi, eax
  mov   edx, VMEM ; load the location of the video memory into ecx. we'll be using this.
  cld ; clear the direction flag.
  .loop: 
    lodsb
    cmp   al, 0
    jz    .exit 

    call  printch
    jmp   .loop

  .exit:
    popa 
  ret

printch:
  ; Moving the ah <- 0E tells the BIOS we're going to commit the 
  ; TELETYPE ROUTINE. Setting character into al, and then calling
  ; INT 0x10 lets the BIOS know to print that character on the screen.

  ; In 32-bit mode, we no longer have access to the BIOS teletype routines
  ; Instead, we must write directly to the video memory itself. 

  ; al = character to put
  ; ah = color of the character and the Background
  ; edx = address of the pixel at that video memory location

  mov   ah, WHITE_BLACK
  mov   [edx], eax ; ah => color, al => character
  add   edx, 2 ; move edx to the next pixel address.
  ret

[ bits 16 ]

prints16:
  pusha 
  mov   si, ax
  mov   ah, 0x0E

  .loop:
    lodsb
    cmp   al, 0
    jz    .exit

    INT   0x10
    jmp   .loop

  .exit:
    popa
  ret