[ org 0x7C00 ] 
[ BITS 16 ]
; https://www.cs.bham.ac.uk/~exr/lectures/opsys/10_11/lectures/os-dev.pdf; page 18.
; Effectively, it allows us to put an offset of 0x7c00 on the assembly addresses -
; meaning that we are clear of the BIOS vector tables/configurations in the memory.

load_addr:
jmp   loader

; bios parameter block. this is required to correctly build drivers
times 0xB - $ + load_addr db 0

bytes_per_sector:       dw 512
sectors_per_cluster:    db 1
reserved_sectors:       dw 0
number_of_fat:          db 2
root_entries:           dw 224
total_sectors:          dw 2880
media:                  db 0xF0
sectors_per_fat: 	      dw 9
sectors_per_track:  	  dw 18
heads_per_cylinder: 	  dw 2
hidden_sectors: 	      dd 0
large_sector_count:     dd 0
drive_number: 	        db 0
flags_for_nt:           db 0
ext_boot_signature: 	  db 0x29
serial_number:	        dd 0xa0a1a2a3
volume_label: 	        db "MOS FLOPPY "
file_system: 	          db "FAT12   "

loader:

KERNEL_ENTRY  equ 0x1000 ; this is where we set up the kernel entry function to be

mov   [boot_addr], dl ; the BIOS stores boot drive address in dl on startup.
mov   bp, 0x8000 ; set up the stack temporarily - this will be changed during 32-bit init
mov   sp, bp

; bx => location where the memory is read
; dh => number of sectors to read
; cl => origin sector
mov   bx, 0x1000
mov   dh, 20
mov   cl, 2
call  read_disk 
; we can utilize the BIOS read functiony ONLY before switching to protected mode -
; as switching to 32 bit makes the 16-bit BIOS routines useless. So we load our 
; kernel **before** we make the jump to 32-bit.

mov   ax, PM_INIT
call  prints16
call  init_gdt ; switch to 32-bit protected mode, by setting cr0 to 1.

%include "gdt.asm"
%include "teletype.asm"
%include "disk.asm"

[ bits 32 ]
_start:
  ; We need to confirm that the 21st+ address pin is unlocked by the BIOS,
  ; otherwise we will not able to access memory past 1MB.
  pushad
  mov   edi, 0x112345
  mov   esi, 0x012345

  mov   [esi], esi
  mov   [edi], edi

  cmpsd
  popad

  jne   .kernel

  mov   eax, A20
  call  prints
  jmp   $

.kernel:
  call  KERNEL_ENTRY ; LEROOOOOOYYYYYYYY JENKIIIIIIINS!
  jmp $ ; hang the CPU. in practice this where the kernel event loop is

PM_INIT:   db "JMP PMODE...", 0x0
A20:       db "NO A20...", 0x0
boot_addr: db 0

times 510-($-$$) db 0

db 0x55
db 0xAA