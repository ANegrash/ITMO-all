ASM=nasm
ASMFLAGS=-f elf64
LD=ld

run: clean main

main: main.o dict.o lib.o
	$(LD) -o $@ $^

%.o: %.asm
	nasm -felf64 -o $@ $<

clean:
	rm -rf *.o main

.PHONY: clean run