#include<stdio.h>
#include<string.h>    //strlen
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include<unistd.h>    //write
#include <time.h>
int main(int argc , char *argv[])
{
int socket_desc , new_socket , c;
struct sockaddr_in server , client;
char *message,client_message[2000];
//Create socket
socket_desc = socket(AF_INET , SOCK_STREAM , 0);
if (socket_desc == -1)
{
printf("Could not create socket");
}
//Prepare the sockaddr_in structure
server.sin_family = AF_INET;
server.sin_addr.s_addr = INADDR_ANY;
server.sin_port = htons( 8888 );
if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
{
puts("bind failed");
return 1;
}
puts("bind done");
listen(socket_desc , 3);
//Accept and incoming connection
puts("Waiting for incoming connections...");
c = sizeof(struct sockaddr_in);
new_socket = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
if (new_socket<0)
{
perror("accept failed");
return 1;
}
puts("Connection accepted");

//Receive a message
int read_size;
memset(client_message,0,sizeof(client_message));
while( (read_size = recv(new_socket , client_message , 2000 , 0)) > 0 )
{
//Send the message
write(new_socket , client_message , strlen(client_message));
memset(client_message,0,sizeof(client_message));
}
if(read_size == 0)
{
puts("Client disconnected");
fflush(stdout);
}
else if(read_size == -1)
{
perror("recv failed");
}
//Free the socket
free(socket_desc);
return 0;
}
