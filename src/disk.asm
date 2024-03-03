read_disk:
  ; pass arguments through a stack:
  ; drive, cylinder, head, sector, num_sectors_to_read
  ; return 

  push  dx

  mov   ah, 0x02 ; bios read sector function
  mov   al, dh ; num_sectors_to_read
  mov   ch, 0 ; cylinder
  mov   dh, 0 ; head. 0-indexed
  ; mov   dl, 0 ; drive
  mov   cl, 2 ; sector. 1-indexed 

  ; push  al ; preserve this for later

  ; mov   bx, 0x0000
  ; mov   es, bx
  ; mov   bx, 0x9000
  mov   bx, 0
  mov   es, bx
  mov   bx, 0x9000
  ; BIOS will read this data into the address es:bx

  INT   0x13 ; issue the actual interrupt

  jc  .disk_error ; carry flag is issued if disk is not read

  pop   dx
  cmp   al, dh
  jne   .disk_error ; if the num_bytes read are not as expected
  ret ; otherwise return!

  .disk_error:
    mov   eax, err
    call  printsln
    ret

  .disk_error_ne:
    mov   eax, err_ne
    call  printsln

  ret
  

err   db "There was an error here, buddy", 0x0
err_ne   db "al and dh are not equal, buddy", 0x0

