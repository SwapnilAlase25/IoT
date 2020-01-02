/*
to check the status of port
sudo netstat -naltp | grep 4000
sudo kill -9 <pid>
*/


#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<strings.h>
#include<string.h>
#include<netinet/in.h>

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
	int connfd; //socket descrypter for accept system call
	int portnumber,clilen; //server port number and client address length declaration
	char buffer[1024]; //buffer to read and write data
	struct sockaddr_in serv_addr,cli_addr; ///client/server structure declaration
	int readbytes; //read bytes from server
	
//condition check for command line
 	if(argc<2)
	{
	error("error in port number\n");
	exit(1);	
	}


	sockfd=socket(AF_INET,SOCK_STREAM,0);
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
	serv_addr.sin_port = htons(portnumber);

//bind the socket with server address with bind system call
	int ret= bind(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
	if(ret<0)
	{
	error("error in binding");
	exit(1);
	}

//listen to max backlog connection 
	int backlog = 5;
	int ret1 = listen(sockfd,backlog);
	if(ret1<0)
	{
	error("listen failed to accept request");
	exit(1);
	}
    else
	{
	printf("Server created succesfully\n");
	}

 	clilen = sizeof(cli_addr);

//accept system call to fetch pending request from the queue
	connfd = accept(sockfd,(struct sockaddr *)&cli_addr,&clilen);
	if(connfd<0)
	{	
	error("error in accepting the request");
	exit(1);
	}  


char exitbuffer[10];
char bye[10]="bye\n";
while(1){
///clear buffer 
	bzero(buffer,sizeof(buffer));

//read data from the server end
	readbytes = read(connfd,buffer,sizeof(buffer));
	if(readbytes<0)
	{
	error("no data is read froom the server");	
	exit(1);
	}

	printf("the Client msg is  %s \n",buffer);
	
	//char successmsg[1024] = "Cheers!! message received \n";
	strcpy(exitbuffer,buffer);
    
    bzero(buffer,sizeof(buffer));
    printf("enter the message to client :");
    int buffer_count = 0;
    while((buffer[buffer_count++] = getchar())!='\n');

	int writebytes = write(connfd,buffer,sizeof(buffer));
	if(writebytes<0)
	{
	error("error in write");
	}

    if(strcmp(exitbuffer,bye)==0){
           printf("server is exiting\n");
        break;
        }

}
close(sockfd);
return 0;
}


