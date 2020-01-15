all: morpion

morpion: morpion.c
	gcc -o morpion morpion.c morpion.h

clean:
	rm morpion