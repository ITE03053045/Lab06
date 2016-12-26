server client: server.c client.c
	gcc -o server server.c
	gcc -o client client.c
server.o client.o: server.c client.c
	gcc -c server.c
	gcc -c client.c
clean:
	rm *.o server client
