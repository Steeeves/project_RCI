############################# Makefile ##########################
all: dki
dki: server_test.o main.o
	gcc -o dki server_test.o main.o
server_test.o: server_test.c server.h
	gcc -o server_test.o -c server_test.c
main.o: main.c server.h
	gcc -o main.o -c main.c
clean:
	rm -rf *.o
mrproper: clean
	rm -rf dki
