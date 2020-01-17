all: morpion.exe

morpion.exe: morpion.c
	gcc -o morpion.exe morpion.c morpion.h

clean:
	rm morpion