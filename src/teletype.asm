prints:
  pusha 
  mov   ecx, eax ; preserve the addr here incase we need it
  _loop: 
    mov   bl, [ecx]
    cmp   bl, 0
    jz    _exit 

    call  printch
    inc   ecx
    jmp   _loop

  _exit:
    popa 
  ret

printsln: ; @todo fix two new lines being printed at once
  call  prints
  push  eax

  mov   bl, 0xD ; this returns the carriage
  call  printch
  mov   bl, 0xA ; this prints a new line
  call  printch

  pop   eax

printch:
  mov   al, bl
  mov   ah, 0x0E
  INT   0x10 ; at this point, we're assuming that the chars are already loaded into al
  ret
