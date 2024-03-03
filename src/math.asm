modulo:
  ; eax % ebx
  ; return eax
  xor   edx, edx
  mov   ecx, ebx
  div   ecx
  mov   eax, edx
  ret



