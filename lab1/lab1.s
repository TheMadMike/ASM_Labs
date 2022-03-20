# Lab1 - Michał Gibas (259563)
# Arithmetic operations on large numbers

SYSEXIT = 1
EXIT_SUCCESS = 0
MAX_RESULT_SIZE = 128

.data

# sample large numbers

number1:
    .long 5, 0x10304008, 0x701100FF, 0x45100020, 0x08570030, 0xF0CCAA00
# format: ^ first word = number length in words (4 bytes)

number1_bytes = . - number1 - 4 # number of bytes of number2

number2:
    .long 4, 0xF040500C, 0x00220026, 0x321000CB, 0x04520031

number2_bytes = . - number2 - 4 # number of bytes of number2

.bss

# max space = space required for multiplication result (n1 + n2)
result:
    .space (number1_bytes + number2_bytes)

.text

.global _start
_start:
    
    push $number2
    push $number1
    call add_nums

    jmp exit_success

exit_success:
    mov $SYSEXIT, %eax
    mov $EXIT_SUCCESS, %ebx
    int $0x80

.include "util.s"
.include "add.s"
