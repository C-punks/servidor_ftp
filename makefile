servidor: mains.o  servidor.o 
	gcc -o servidor mains.o  servidor.o
mains.o: mains.c  servidor.h
	gcc -c mains.c
servidor.o: servidor.c servidor.h
	gcc -c servidor.c

clean:
	rm mains.o  servidor.o
