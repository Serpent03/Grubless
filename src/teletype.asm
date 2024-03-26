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

printsln:
  call  prints
  call  newline
  ret 

newline:
  ; @todo newline instead has to move the cursor
  mov   al, 0xA
  call  printch
  mov   al, 0xD
  call  printch
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

printdwln:
  ; @todo re-write for protected mode
  ; takes eax as a DWORD
  ; returns null, prints a DWORD and a new line

  push  eax

  mov   al, '0'
  call  printch
  mov   al, 'x'  
  call  printch

  pop   eax

  call  printdw
  call  newline
  ret

printdw:
  ; takes eax as a double word(DWORD)
  ; returns null, prints a DWORD(32-bit / 4 bytes)
  push  eax

  shr   eax, 16
  call  printw

  pop   eax
  call  printw
  
  ret


printw:
  ; takes eax as a word
  ; returns null, prints a word(16-bit / 2 bytes)
  push  eax ; @fix Storing variable in another register brings garbage value to screen..

  shr   eax, 8
  call  printb

  pop   eax
  call  printb

  ret

printb:
  ; takes eax as a byte
  ; returns null, prints a byte(8-bit)
  push  eax

  shr   eax, 4 
  call  nibble2chr ; print the MSB nibble
  call  printch
  
  pop   eax
  call  nibble2chr ; print the LSB nibble
  call  printch

  ret
  

nibble2chr:
  ; takes eax as a nibble(4 bits, only up from 0 to 15)
  ; returns char in eax 
  mov   ebx, 0x10
  call  modulo ; returns the modulus in eax

  mov   ebx, eax
  cmp   ebx, 9
  jg    .above_ten ; if the mod is above 10, then we append alphabets

  .below_ten:
    add   ebx, '0'
    mov   eax, ebx
    ret ; return

  .above_ten:
    mov   ebx, 10 ; this will return a range from 0 to 5 <= [(10 to 15) % 10]
    call  modulo
    mov   ebx, eax
    add   ebx, 'A' ; this results in it becoming from 'A' to 'F'

  mov   eax, ebx
  ret
    
