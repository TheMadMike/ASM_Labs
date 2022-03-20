copy_to_result_buffer:
    pop %eax # get return address
    pop %ebx # get number address
    pop %ecx # get result buffer size
    push %eax # push return address back on stack

    # get number length
    movl (%ebx), %esi

    loop0:
        movl (%ebx, %esi, 4), %eax
        movl $result, %edi  
        movl %eax, -4(%edi, %ecx, 4)
        
        dec %ecx
        dec %esi
        cmp $0, %esi
        jne loop0
    
    ret

convert_to_negative_u2:
    