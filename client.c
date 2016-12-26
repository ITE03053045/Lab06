#include<stdio.h>
#include<string.h>    
#include<sys/socket.h>
#include<string.h>
#include<arpa/inet.h> 
int main(int argc , char *argv[])
{
int socket_desc;
struct sockaddr_in server;
char server_reply[2000], message[2000];
//Create socket
socket_desc = socket(AF_INET , SOCK_STREAM , 0);
if (socket_desc == -1)
{
printf("Could not create socket");
}
if(argc!=3)
{
   printf("usage: a.out <IPaddress> <ProtNumber>\n");
   return -1;
}
int ProtNum;
sscanf(argv[2],"%d",&ProtNum);

server.sin_addr.s_addr = inet_addr(argv[1]);
server.sin_family = AF_INET;
server.sin_port = htons( ProtNum );
//Connect to remote server
if (connect(socket_desc , (struct sockaddr *)&server , sizeof(server)) < 0)
{
puts("connect error");
return 1;
}
puts("Connected\n");
//Send
 memset(server_reply,0,sizeof(server_reply));
while(1)
{
   gets(message);
   if( send(socket_desc , message , strlen(message) , 0) < 0)
   {
      puts("Send failed");
      return 1;
   }
   puts("Data Send\n");
   //Receive
   if( recv(socket_desc, server_reply , 2000 , 0) < 0)
   {
      puts("recv failed");
   }
   puts("Reply received\n");
   puts(server_reply);
   fflush(stdin);
   memset(message, 0, sizeof(message));
   memset(server_reply,0,sizeof(server_reply));
}
return 0;
}
