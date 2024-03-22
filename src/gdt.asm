; Start of the global descriptor tables

gdt_start:
  
gdt_null:
  dd  0x0 ; dd => 4 bytes
  dd  0x0 ; we initialize two 4-byte regions in the memory. this is the null descriptor.
  


