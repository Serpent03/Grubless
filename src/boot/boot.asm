[ org 0x7C00 ] 
[ BITS 16 ]
; https://www.cs.bham.ac.uk/~exr/lectures/opsys/10_11/lectures/os-dev.pdf; page 18.
; Effectively, it allows us to put an offset of 0x7c00 on the assembly addresses -
; meaning that we are clear of the BIOS vector tables/configurations in the memory.

; load_addr:
jmp   short loader
nop

; times 0xB - $ + load_addr db 0
; bios parameter block. this defines the FAT12 "meta-metadata" for drivers/programs.
oem:                    db "MSWIN4.1" ; keep for compatibility
bytes_per_sector:       dw 512
sectors_per_cluster:    db 1
reserved_sectors:       dw 1
number_of_fat:          db 2
root_entries:           dw 224
total_sectors:          dw 2880
media:                  db 0xF0
sectors_per_fat: 	      dw 9
sectors_per_track:      dw 18
heads_per_cylinder:     dw 2
hidden_sectors:         dd 0
large_sector_count:     dd 0

; extended boot record. 
drive_number:           db 0
flags_for_nt:           db 0
ext_boot_signature:     db 0x29
serial_number:          dd 0x01020304
volume_label:           db "GRUBLESS   "
file_system:            db "FAT12   "

; This is the bootsector - when we create a fresh FAT12 storage image with dd adn mkfs,
; the bootsector of that image is, by default, not customized with this bootloader code.
; Thus, we have to overwrite that sector with ours using dd again, and then using some
; linux magic, mount that image onto a loop, and put the rest of the compiled kernel into it.
; This would mean that the FAT12 image will actually respect the FAT12 standards, and we could
; then proceed to write an accurate driver/VFS for the disk.

loader:

KERNEL_ENTRY  equ 0x10000 ; this is where we set up the kernel entry function to be

mov   [boot_addr], dl ; the BIOS stores boot drive address in dl on startup.
mov   bp, 0x8000 ; set up the stack temporarily - this will be changed during 32-bit init
mov   sp, bp

; es:bx => location where the memory is read
; dh => number of sectors to read
; cl => origin sector
mov   bx, 0x1000
mov   es, bx
mov   bx, 0x0
mov   dh, 30 ; kernel code is about 10kB. 1 sector = 512B, 20 = 10kB. Read 30 for safety.
mov   cl, 34 
call  read_disk 

; phase 2 of the bootloader is stored at sector 33 of the disk by FAT12.
; since BIOS read disk function is 1-indexed, we have to make it sector 34 and put
; it into cl. Also, this is hardcoded to load contents at sector 33 of the disk
; so it will only work for FAT12 formatted drives for the moment. A more sophisticated
; method would be to either look up the actual location from the allocation tables,
; or to always load the data stored at the first cluster of the data area.

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
[ global _start ]
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

  mov   eax, dword [KERNEL_ENTRY]
  cmp   eax, 0x03fffff0 ; I wonder why this value is produced at 0x1000.
  je    .hang

  call  KERNEL_ENTRY ; LEROOOOOOYYYYYYYY JENKIIIIIIINS!
  jmp   $ ; hang the CPU. in practice this where the kernel event loop is

.hang:
  mov   eax, NO_KERN
  call  prints
  jmp   $

PM_INIT:    db "JMP PMODE...", 0x0
NO_KERN:    db "NO KERNEL...", 0x0
A20:        db "NO A20...", 0x0
boot_addr:  db 0

times 510-($-$$) db 0

db 0x55
db 0xAA