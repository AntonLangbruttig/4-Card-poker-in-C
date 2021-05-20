all: client server

client: client.c
	gcc -Wall client.c -o client

server: server.c
	gcc -Wall server.c -o server

clean:
	rm server
	rm client
	rm Cards
