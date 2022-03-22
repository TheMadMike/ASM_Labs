
# number1 * number2 (nb)
mul_nums_nb:
    pop %eax # get return address
    pop %ebx # get number1 address
    pop %edx # get number2 address
    push %eax # push return address back on stack

    # get number1 length (1st iterator)
    movl (%ebx), %esi
    # get number2 length (2nd iterator)
    movl (%edx), %edi

    cmp $0, %esi
    je mul_nb_end
    outer_loop:
        
        # (re)initialize 2nd iterator
        movl (%edx), %edi

        # check if zero (then end)
        cmp $0, %edi
        je mul_nb_end
        clc
        inner_loop:
            # preserve the EDX value (because it will be a part of mull result)
            push %edx
            # multiply the words
            movl (%ebx, %esi, 4), %eax
            mull (%edx, %edi, 4)
            
            # calculate ECX = ESI + EDI - 1 (result buffer offset)
            mov %esi, %ecx
            addl %edi, %ecx
            dec %ecx

            # add the mulitiplication result to the result buffer
            
            addl %eax, result(, %ecx, 4)
            dec %ecx
            adcl %edx, result(, %ecx, 4)

            # pop preserved EDX value
            pop %edx

            # inner_loop condition check and iterator decrementation
            dec %edi
            cmp $0, %edi
            jne inner_loop   
        # outer_loop condition chceck and iterator decrementation
        dec %esi
        cmp $0, %esi
        jne outer_loop
    

mul_nb_end:
    ret
