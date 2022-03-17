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

    push %ecx
    push %edi

    loop0:
        movl (%ebx, %esi, 4), %eax
        movl $result, %edi  
        movl %eax, -4(%edi, %ecx, 4)
        
        dec %ecx
        dec %esi
        cmp $0, %esi
        jne loop0

    # add number2 to the result buffer
    pop %edi
    pop %ecx

    clc # clear carry flag

    pushf

    loop1:
        movl (%edx, %edi, 4), %eax
        movl $result, %esi
        popf
        adcl %eax, -4(%esi, %ecx, 4)
        pushf
    
        dec %ecx
        dec %edi
        cmp $0, %edi
        jne loop1

    popf
    jc add_last_carry_bit

    ret

    add_last_carry_bit:
        mov $result, %eax
        addl $1, (%eax, %ecx, 4)
        ret