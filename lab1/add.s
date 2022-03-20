# nb = natural binary code
# u2 = two's complement

# number1 + number2 (nb/u2)
add_nums:
    pop %eax # get return address
    pop %ebx # get number1 address
    pop %edx # get number2 address
    push %eax # push return address back on stack

    # get number1 length
    movl (%ebx), %esi
    # get number2 length
    movl (%edx), %edi

    # copy number1 to result buffer
    mov %esi, %ecx
    add %edi, %ecx
    
    # preserve ECX and EDI values on the stack
    push %ecx
    push %edi

    push %ecx
    push %ebx
    call copy_to_result_buffer

    # add number2 to the result buffer

    # get previously stored ECX and EDI values from the stack
    pop %edi
    pop %ecx

    clc # clear carry flag

    pushf

    # store result buffer address in ESI register
    movl $result, %esi
    loop1:
        movl (%edx, %edi, 4), %eax
        popf
        adcl %eax, -4(%esi, %ecx, 4)
        pushf
    
        dec %ecx
        dec %edi
        cmp $0, %edi
        jne loop1

    # add a carry bit at the end
    popf
    adcl $0, -4(%esi, %ecx, 4)

    ret
