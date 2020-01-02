   //UDP SERVER

#include<stdio.h>
#include<stdlib.h>
///socket headern files
#include<sys/types.h>
#include<sys/socket.h>
#include<strings.h>
#include<string.h>
#include<netinet/in.h>

#define MAX_SIZE 1024
//erroe handler
void error(char *msg)
{
perror(msg);
exit(1);
}

///main function
int main(int argc,char *argv[])
{
	int sockfd; ///master socket descrypter
	//int connfd; //socket descrypter for accept system call
	int portnumber,clilen; //server port number and client address length declaration
	char buffer[MAX_SIZE]; //buffer to read and write data
	struct sockaddr_in serv_addr,cli_addr; ///client/server structure declaration
	int rxbytes; //read bytes from server
	
//condition check for command line
 	if(argc<2)
	{
	error("error in port number\n");
	exit(1);	
	}
//creation for master socket  to bind,listen and accept system call
//REFER MAN 2 SOCKET FOR DETAILS AF)INET-IPv4 PROTOCOLS
//SOCK_STREAM FOR SELECTING TCP PROTOCOL
//SOCK_DGRAM FOR UDP
//0- PROTOCOL (DECIDED BY SYSTEM/KERNEL/OS)
	sockfd=socket(AF_INET,SOCK_DGRAM,0);
 	if(sockfd<0)
	{
	perror("socket is not created");
	exit(1);
	}

///clear the structure buffer with either bzero or memset
bzero((char *)&serv_addr,sizeof(serv_addr));

//port number - integer - atoi()(ASCII TO INTEGER CONVERSION)
	portnumber=atoi(argv[1]);

//initialize the structure member
	serv_addr.sin_family=AF_INET; //ipV4 internet family
	serv_addr.sin_addr.s_addr = INADDR_ANY;	//INADDR_ANY - BINDS TO ALL THE AVAILABLE INTERFACE OF HOST MACHINE/WORKSTATION 
///ELSE SPECIFIC INTERFACE CAN BE INTIALIZED LIKE:localhost(127.0.0.1)
//wifi - interface - eg "192.168.75.1"
//layman terminology client can connect to server with all interfaces of server

//htons  - host to neterk byte orde(short) netwrk byte order - bigindian
	serv_addr.sin_port = htons(portnumber);

//bind the socket with server address with bind system call
	int ret= bind(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
	if(ret<0)
	{
	error("error in binding");
	exit(1);
	}
    else{
    
    printf("Server created !!!\n");
}


while(1){

clilen=sizeof(cli_addr);

recvfrom(sockfd,buffer,MAX_SIZE,0,(struct sockaddr*)&cli_addr,&clilen);

printf("Client: %s ",buffer);


sendto(sockfd,buffer,MAX_SIZE,0,(struct sockaddr*)&cli_addr,sizeof(cli_addr));


}
close(sockfd);
return 0;
}


