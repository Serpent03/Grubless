disk_routine:
  ; pass arguments through a stack:
  ; drive, cylinder, head, sector, num_sectors_to_read
  ; return 

  push  dx

  mov   ah, 0x02 ; bios read sector function
  mov   al, dh ; num_sectors_to_read
  mov   ch, 0 ; cylinder
  mov   cl, 3 ; sector. 1-indexed 
  mov   dh, 0 ; head. 0-indexed
  ; mov   dl, 0 ; drive address(from bios start)

  INT   0x13 ; issue the actual interrupt

  jc  .disk_error ; carry flag is issued if disk is not read

  pop   dx
  cmp   al, dh
  jne   .disk_error_ne ; if the num_bytes read are not as expected
  ret ; otherwise return!

  .disk_error:
    mov   eax, err
    call  printsln
    ret

  .disk_error_ne:
    mov   eax, err_ne
    call  printsln

  ret
  
read_disk:
  ; eax = drive address | num_sectors_to_read
  ; ebx = cylinder | head
  ; ecx = 0x0000 | sector
  ; return void
  ; @todo add functionality to pass arguments to this function

  pusha 

  mov   bx, 0
  mov   es, bx
  mov   bx, 0x9000 ; reads the data to a location referenced by es:bx

  mov   dh, 2 ; number of sectors to read
  mov   dl, [boot_addr] ; drive address as reported by BIOS on init

  call  disk_routine 

  popa
  ret

err       db "There was an error here, buddy", 0x0
err_ne    db "al and dh are not equal, buddy", 0x0

