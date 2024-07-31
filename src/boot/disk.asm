[ bits 16 ]
disk_routine:
  ; pass arguments through a stack:
  ; drive, cylinder, head, sector, num_sectors_to_read
  ; return 

  push  dx

  mov   ah, 0x02 ; bios read sector function
  mov   al, dh ; num_sectors_to_read
  mov   ch, 0 ; cylinder
  ; mov   cl, 2 ; sector. 1-indexed 
  mov   dh, 0 ; head. 0-indexed

  INT   0x13 ; issue the actual interrupt

  jc  .disk_error ; carry flag is issued if disk is not read

  pop   dx
  cmp   al, dh
  jne   .disk_error_ne ; if the num_bytes read are not as expected
  ret ; otherwise return!

  .disk_error:
    mov   ax, err
    call  prints16
    ret

  .disk_error_ne:
    mov   ax, err_ne
    call  prints16
  ret
  
read_disk:
  ; bx => location where the memory is read
  ; dh => number of sectors to read
  ; cl => origin sector

  pusha 
  push  bx

  mov   bx, 0
  mov   es, bx
  pop   bx
  ; mov   bx, 0x9000 ; reads the data to a location referenced by es:bx

  ; mov   dh, 3 ; number of sectors to read
  mov   dl, [boot_addr] ; drive address as reported by BIOS on init

  call  disk_routine 

  popa
  ret

err       db "DSKRTN: OUT_BOUNDS", 0x0
err_ne    db "DSKRTN: READ_UNEQL", 0x0

