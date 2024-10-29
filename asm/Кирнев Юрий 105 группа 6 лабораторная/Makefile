all: prog

prog: main.o f1.o f2.o f3.o
	gcc -o prog main.o f1.o f2.o f3.o -m32 -lm
main.o: main.c
	gcc -c -o main.o main.c -m32
f1.o: f1.asm
	nasm -f elf32 -o f1.o f1.asm
f2.o: f2.asm
	nasm -f elf32 -o f2.o f2.asm
f3.o: f3.asm
	nasm -f elf32 -o f3.o f3.asm
	
clean:
	rm *.o prog
