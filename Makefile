############################# Makefile ##########################
all: server_test
server_test: server_test.o main.o
	# O compilador faz a ligação entre os dois objetos
	gcc -o server_test server_test.o main.o
#-----> Distancia com o botão TAB ### e não com espaços
server_test.o: server_test.c server_test.h
	gcc -o server_test.o -c server_test.c
main.o: main.c server_test.h
	gcc -o main.o -c main.c
clean:
	rm -rf *.o
mrproper: clean
	rm -rf server_test
