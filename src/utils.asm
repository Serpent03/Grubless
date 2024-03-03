debug_regs:
  ; takes no argument
  ; prints all registers to the screen
  
  push  esp
  push  edx
  push  ecx
  push  ebx
  push  eax

  mov   eax, eax_s
  call  prints
  pop   eax
  call  printwln

  mov   eax, ebx_s
  call  prints
  pop   ebx
  mov   eax, ebx
  call  printwln

  mov   eax, ecx_s
  call  prints
  pop   ecx
  mov   eax, ecx
  call  printwln

  mov   eax, edx_s
  call  prints
  pop   edx
  mov   eax, edx
  call  printwln

  mov   eax, esp_s
  call  prints
  pop   esp
  mov   eax, esp
  add   eax, 2 ; add 2 bytes; because our current function ret pointer is also occupying 2 bytes in the stack.
  call  printwln

  call  newline

  ret

eax_s   db "EAX: ", 0
ebx_s   db "EBX: ", 0
ecx_s   db "ECX: ", 0
edx_s   db "EDX: ", 0
esp_s   db "ESP: ", 0
