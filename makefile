server client:server.c client.c
	g++ server.c -o server
	g++ client.c -o client
server.o client.o:server.c client.c
	g++ server.c
	g++ client.c
clean:
	rm *.server client
