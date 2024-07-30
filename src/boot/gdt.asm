; Start of the global descriptor tables
; Page 40: https://www.cs.bham.ac.uk/~exr/lectures/opsys/10_11/lectures/os-dev.pdf
; description of the GDT tables along with the GDT data structure.

gdt_start: ; start of the GDT data structure.
  
gdt_null:
  dd  0x0 ; dd => 4 bytes
  dd  0x0 ; we initialize two 4-byte regions in the memory. this is the null descriptor.
  
gdt_code_segment_descriptor:
  dw  0xffff
  dw  0x0
  db  0x0
  db  0b10011010
  db  0b11001111
  db  0x0

gdt_data_segment_descriptor:
  dw  0xffff
  dw  0x0
  db  0x0
  db  0b10010010
  db  0b11001111
  db  0x0
  

gdt_end: ; we put this label here so we can calculate the size of the GDT data structure.

gdt_descriptor:
  dw  gdt_end - gdt_start - 1
  dd  gdt_start

ADDR_CODE_SEG equ   gdt_code_segment_descriptor - gdt_start
ADDR_DATA_SEG equ   gdt_data_segment_descriptor - gdt_start

[ bits 16 ]
init_gdt:
  cli ; stop the interrupts until we have transitioned into the 32-bit mode
  lgdt  [gdt_descriptor] ; load the GDT address
  mov   eax, cr0
  or    eax, 0x1 ; enable 32-bit protected mode in the control reg 0
  mov   cr0, eax
  jmp   ADDR_CODE_SEG:init_seg ; we far jump into another segment to clear the prefetch cache of the CPU

[ bits 32 ]
init_seg:
  mov   ax, ADDR_DATA_SEG
  mov   ds, ax
  mov   fs, ax
  mov   gs, ax
  mov   ss, ax
  mov   es, ax

  mov   ebp, 0x90000
  mov   esp, ebp
  ; set up the segments and the stack position

  call  _start

