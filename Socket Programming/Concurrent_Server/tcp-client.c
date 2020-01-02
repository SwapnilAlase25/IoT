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


pid_t cpid;
char recvbuffer[1024];
char traxbuffer[1024];

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


cpid = fork();

if(cpid==0){                                //child context----tx


        while(1){

        bzero(&traxbuffer,sizeof(traxbuffer));
        printf("\nEnter Text ");
        fgets(traxbuffer,sizeof(traxbuffer),stdin);

    send(sockfd,traxbuffer,strlen(traxbuffer)+1,0);
    printf("Msg sent successfull");
}

close(sockfd);


}
else{                                           //parents context-----rx
    while(1){

    bzero(&recvbuffer,sizeof(recvbuffer));

    recv(sockfd,recvbuffer,sizeof(recvbuffer),0);

    printf("Server: %s",recvbuffer);


}
    close(sockfd);


}


close(sockfd);
return 0;
}

