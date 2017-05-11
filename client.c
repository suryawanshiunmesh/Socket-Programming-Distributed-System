// client

//header files declaration
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h> 

//error function
void error(const char *msg)
{
   	perror(msg);
    	exit(0);
	}

//main function
int main(int argc, char *argv[])
{
    	int sockfd, portno, n;
    	struct sockaddr_in serv_addr;
    	struct hostent *server;
    	char buffer[256], hostname[256];
    
    	while(1)
	{
    		printf("\nEnter Server's IP/Hostname: ");
    		scanf("%s",hostname);
    		printf("\nEnter Server's Port Number: ");
   		scanf("%d", &portno);
    		sockfd = socket(AF_INET, SOCK_STREAM, 0);
    		if(sockfd<0) 
        		error("Error..! Opening socket..!\n");
    		server = gethostbyname(hostname);
    		if(server==NULL)
		{
        		fprintf(stderr,"Error..! No such host..!\n");
        		exit(0);
    			}
    		//connection of socket
		bzero((char *) &serv_addr, sizeof(serv_addr));
    		serv_addr.sin_family = AF_INET;
    		bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    		serv_addr.sin_port = htons(portno);
    		if(connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        	error("Error..! Connecting..!\n");
    
    		bzero(buffer,256);
    		n=read(sockfd,buffer,255);
    		if(n<0) 
         	error("Error..! Reading from socket..!\n");
    		printf("%s\n",buffer);            
        
    		printf("Please enter the message: ");
    		bzero(buffer,256);
    		fseek(stdin,0,SEEK_END);
    		scanf("%s",buffer);

    		n=write(sockfd,buffer,strlen(buffer));
    		if(n<0) 
         		error("Error..! Writing to socket..!\n");
    		bzero(buffer,256);
    		n=read(sockfd,buffer,255);
    		if(n<0) 
         		error("Error..! Reading from socket..!\n");
   		// final result
		printf("\nAnswer: %s\n",buffer);
    		close(sockfd);
    
    		printf("\nConnection closed..!\n\n");
    		}
    
    	return 0;
	}
