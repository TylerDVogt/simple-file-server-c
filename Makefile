all: server client

server: server.o
	gcc -o server server.o

client: client.o
	gcc -o client client.o

server.o: server.c server.h
	gcc -c server.c

client.o: client.c client.h
	gcc -c client.c

.PHONY: clean all

clean: 
	rm -f *.o server client
