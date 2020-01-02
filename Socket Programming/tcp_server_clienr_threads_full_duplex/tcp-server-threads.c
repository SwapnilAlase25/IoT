// while compiling use -pthread

#include<stdio.h>
#include<stdlib.h>
///socket headern files
#include<sys/types.h>
#include<sys/socket.h>
#include<strings.h>
#include<string.h>
#include<netinet/in.h>
//threads
#include<pthread.h>
#include<unistd.h>

pthread_t t1,t2;

//void *th1(void *arg);
//void *th2(void *arg);
//char recvbuffer[1024];
//char traxbuffer[1024];
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
 char traxbuffer[1024];
 char recvbuffer[1024];
///////////////////threads methods/////////////////////////////////////////

void *th1(void *arg)
{
                 //thread1----rx

        while(1){

    bzero(&recvbuffer,sizeof(recvbuffer));

    recv(connfd,recvbuffer,sizeof(recvbuffer),0);

    printf("Client: %s",recvbuffer);


}
    close(sockfd);
	
}


void *th2(void *arg)
{
	    //thread2-----tx

        while(1){

        bzero(&traxbuffer,sizeof(traxbuffer));
        printf("\nEnter Text ");
        fgets(traxbuffer,sizeof(traxbuffer),stdin);

    send(connfd,traxbuffer,strlen(traxbuffer)+1,0);
    //printf("Msg sent successfull");
}

close(sockfd);	
}


///////////////////////////////////////////////////////////////////////////
    
	
	
//condition check for command line
 	if(argc<2)
	{
	error("error in port number\n");
	exit(1);	
	}
//creation for master socket  to bind,listen and accept system call
//REFER MAN 2 SOCKET FOR DETAILS AF)INET-IPv4 PROTOCOLS
//SOCK_STREAM FOR SELECTING TCP PROTOCOL
//0- PROTOCOL (DECIDED BY SYSTEM/KERNEL/OS)
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
        printf("Server is Created !!\n");
    }

//listen to max backlog connection 
	int backlog = 5;
	int ret1 = listen(sockfd,backlog);
	if(ret1<0)
	{
	error("listen failed to accept request");
	exit(1);
	}

 	clilen = sizeof(cli_addr);

//accept system call to fetch pending request from the queue
	connfd = accept(sockfd,(struct sockaddr *)&cli_addr,&clilen);
	if(connfd<0)
	{	
	error("error in accepting the request");
	exit(1);
	} 


////////////////////////thread 1////////////////////////////
 
	
    int t_stat = pthread_create(&t1, NULL, th1, NULL);
   
    if(t_stat){
		perror("Thread creation failure!");
		exit(1);
	}
	else
	{
		printf("Thread_1 created successfully\n");
	}
	
//////////////////////thread 2//////////////////////////////
  t_stat = pthread_create(&t2, NULL, th2, NULL);

    if(t_stat){
		perror("Thread creation failure!");
		exit(1);
	}
	else
	{
		printf("Thread_2 created successfully\n");
	}
	
////////////////////////////////////////////////////////////
	void *stat;
	pthread_join(t1, stat);
    pthread_join(t2, stat);




 //while(1);

return 0;
}


