; @todo fix the prints function. Apparently not getting the mem address for char..
prints:
  pusha 
  mov al, cl
  call printch
  popa 
  ret

printch:
  pusha
  mov ah, 0x0E
  INT 0x10 ; at this point, we're assuming that the chars are already loaded into al
  popa
  ret
