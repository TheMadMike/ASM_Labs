ASM = as -g --32
LD = ld -m elf_i386

TARGET_NAME = lab1.bin
SOURCE_FILES = lab1.s

all: assemble link clear

assemble:
	$(ASM) $(SOURCE_FILES) -o $(TARGET_NAME).o

link:
	$(LD) $(TARGET_NAME).o -o $(TARGET_NAME)

clear:
	rm *.o