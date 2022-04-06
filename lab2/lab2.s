# Lab2 - Michał Gibas (259563)

SYSEXIT = 1
EXIT_SUCCESS = 0 

.data
operation_msg: .asciz "Choose: 1. addition 2. subtraction 3. multiplication 4. division \n"
rounding_msg: .asciz "Rounding: 1. Up 2. Down 3. Nearest 4. 0 \n"
precision_msg: .asciz "Precision: 1. Single 2. Double \n"

int_format: .asciz " %d"
float_format: .asciz " %f"
double_format: .asciz " %lf"
new_line: .asciz "\n"

result: .long 8 # result buffer

# rounding
round_nearest: .short 0x03F #nearest
round_down: .short 0x43F #down
round_up: .short 0x83F #up
round_zero: .short 0xC3F #zero


.bss
# scanf input buffers
operation_type: .space 1
rounding_type: .space 1
precision: .space 1
##

io_format: .space 4 # address to a selected printf/scanf format string

rounding_mask: .space 1

first: .space 8 # first operand
second: .space 8 # second operand

.text

.global main

main:
    # choose an arithmetic operation type
    pushl $operation_msg
    call printf
    addl $4, %esp

    pushl $operation_type
    push $int_format
    call scanf 
    addl $8, %esp

    # choose a rounding method
    pushl $rounding_msg
    call printf
    addl $4, %esp

    pushl $rounding_type
    push $int_format
    call scanf
    addl $8, %esp

    cmpb $1, rounding_type
    je up
    cmpb $2, rounding_type
    je down
    cmpb $3, rounding_type
    je nearest

zero:
    fldcw round_zero
    jmp read_precision
nearest:
    fldcw round_nearest
    jmp read_precision
up:
    fldcw round_up
    jmp read_precision
down:
    fldcw round_down

read_precision:

    # choose floating point precision
    pushl $precision_msg
    call printf
    addl $4, %esp

    pushl $precision
    push $int_format 
    call scanf 
    addl $8, %esp

    # determine scanf format based on precision choice
    cmpb $1, precision
    je single_precision

double_precision:
    movl $double_format, io_format
    jmp next
single_precision:
    movl $float_format, io_format
next:    

    # read the operands
    call read_operands

    # perform selected operation
    cmpb $1, operation_type
    je add
    cmpb $2, operation_type
    je subtract
    cmpb $3, operation_type
    je multiply
    cmpb $4, operation_type
    je divide


read_operands:

    pushl $first
    push io_format
    call scanf 
    addl $8, %esp

    pushl $second
    push io_format
    call scanf
    addl $8, %esp 

    ret

### addition
add:
    # precision == 1
    cmpb $1, precision
    je add_float

    add_double: # double precision
        fldl first
        faddl second

        jmp print_result

    add_float: # single precision
        flds first
        fadds second

        jmp print_result
###

### subtraction
subtract:
    cmpb $1, precision
    je sub_float

    sub_double:
        fldl first 
        fsubl second

        jmp print_result

    sub_float:    
        flds first
        fsubs second

        jmp print_result
###

### multiplication
multiply:
    cmpb $1, precision
    je mul_float

    mul_double:
        fldl first
        fmull second

    mul_float:
        flds first
        fmuls second

        jmp print_result
###

### division
divide:
    cmpb $1, precision
    je div_float

    div_double:
        fldl first
        fdivl second

        jmp print_result

    div_float:
        flds first
        fdivs second

        jmp print_result
###

print_result:

    subl $8, %esp
    fstpl (%esp)
    push io_format
    call printf
    addl $8, %esp
    
    pushl $new_line
    call printf
    addl $4, %esp

    jmp exit

exit:
    mov $SYSEXIT, %eax
    mov $EXIT_SUCCESS, %ebx
    int $0x80
