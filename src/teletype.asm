prints:
  pusha 
  mov   ecx, eax ; @todo see if only eax can be used for the whole op.
  .loop: 
    mov   bl, [ecx]
    cmp   bl, 0
    jz    .exit 

    call  printch
    inc   ecx
    jmp   .loop

  .exit:
    popa 
  ret

printsln:
  call  prints
  call  newline
  ret 


newline:
  mov   bl, 0xA
  call  printch
  mov   bl, 0xD
  call  printch
  ret

printch:
  ; Moving the ah <- 0E tells the BIOS we're going to commit the 
  ; TELETYPE ROUTINE. Setting character into al, and then calling
  ; INT 0x10 lets the BIOS know to print that character on the screen.
  mov   al, bl
  mov   ah, 0x0E
  INT   0x10 ; at this point, we're assuming that the chars are already loaded into al
  ret

printwln:
  ; takes eax as a word
  ; returns null, prints a word and a new line
  push  eax

  mov   bl, '0'
  call  printch
  mov   bl, 'x'
  call  printch

  pop   eax ; because ah and al get manipulated by printch

  call  printw
  call  newline
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
  ; returns char in ebx 
  mov   ebx, 0x10
  call  modulo ; returns the modulus in eax

  mov   ebx, eax
  cmp   ebx, 9
  jg    .above_ten ; if the mod is above 10, then we append alphabets

  .below_ten:
    add   ebx, '0'
    ret ; return

  .above_ten:
    mov   ebx, 10 ; this will return a range from 0 to 5 <= [(10 to 15) % 10]
    call  modulo
    mov   ebx, eax

    add   ebx, 'A' ; this results in it becoming from 'A' to 'F'
  ret
    
