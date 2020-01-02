#include<stdio.h>
#define BUFFER_SIZE 1024
#define PORT 4000
#include<strings.h>
#include <string.h>
#include<stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include<unistd.h>



//erroe handler
void error(char *msg)
{
perror(msg);
exit(1);
}

int main(int argc,char *argv[])
{
	int sockfd; ///acceptfd;
	struct sockaddr_in serv_addr,cli_addr;
	char buffer[BUFFER_SIZE];
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(sockfd<0)
	{
	error("socket creation failed");	
	}

	else
	{
	printf("socket created succesfully\n");
	}
	

	bzero(&serv_addr,sizeof(serv_addr));
	
	serv_addr.sin_family = AF_INET;
	
	serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	serv_addr.sin_port = htons(PORT);

	int retcon = connect(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));

	if(retcon<0)
	{
	error("connection to socket server failled");
	}
	else
	{
	printf("conneted to server successfully\n");
	}	
char bye[]="bye\n";
while(1)
{
bzero(buffer,sizeof(buffer));
printf("enter the message to server:");
int buffer_count = 0;
while((buffer[buffer_count++] = getchar())!='\n');

	write(sockfd,buffer,sizeof(buffer));
	bzero(buffer,sizeof(buffer));
	
	read(sockfd,buffer,sizeof(buffer));
	printf("data from server : %s \n",buffer);

        
    if(strcmp(buffer,bye)==0){
        printf("client is exiting\n");        
        break;
        }
}

close(sockfd);
return 0;
}

