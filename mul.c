//multiplication server

//header files declaration
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

//error function
void error(const char *msg)
{
    	perror(msg);
    	exit(1);
	}

//main function
int main(int argc, char *argv[])
{
   	int sockfd, newsockfd, portno;
     	socklen_t clilen;
    	char buffer[256];
     	struct sockaddr_in serv_addr, cli_addr;
     	const char sym[2] = "*";
     	char *token;
     	int n;
	float num1, num2;
 
	//checking whether the port no. is provided or not
    	if(argc<2)
	{
     		fprintf(stderr,"Error..! No port provided..!\n");
         	exit(1);
     		}
	//opening socket
     	sockfd = socket(AF_INET, SOCK_STREAM, 0);
     	if(sockfd<0) 
       	error("Error..! Opening socket..!\n");
	//binding socket
     	bzero((char *) &serv_addr, sizeof(serv_addr));
    	portno = atoi(argv[1]);
     	serv_addr.sin_family = AF_INET;
     	serv_addr.sin_addr.s_addr = INADDR_ANY;
     	serv_addr.sin_port = htons(portno);
     	if(bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
     		error("Error..! On binding..!\n");
              
     while(1)
	{              
	     	listen(sockfd,5);
	     	clilen=sizeof(cli_addr);
	     	newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
	     	if(newsockfd<0) 
		  error("Error..! On accept..!\n");
		//display the connection message and ask to for the input		  
	     	strcpy(buffer,"\nYou are connected to Multiplication Server..!\n\nInput the Equatopn in the form : Num1*Num2\n");
	     	n=write(newsockfd,buffer,strlen(buffer));
	     	if(n<0) 
	     		error("Error..! Writing to socket..!\n");
	       
	     	bzero(buffer,256);
	     	n=read(newsockfd,buffer,255);
	     	if(n<0) 
	     		error("Error..! Reading from socket..!\n");	     
	     	printf("Here is the message: %s\n",buffer);
	     
	     	token=strtok(buffer, sym);
	     
	     	num1=atof(token);
    		token=strtok(NULL, sym);
      	num2=atof(token);
      	printf("\nSolution: %3.2f * %3.2f = %3.2f\n", num1, num2, num1*num2);
	     	num2 = num1*num2;
		//display the final output
	     	sprintf(buffer, "%3.2f", num2);
	     
	     	n=write(newsockfd,buffer,strlen(buffer));
	     	if(n<0) 
	     		error("Error..! Writing to socket..!\n");
	     	
	     	close(newsockfd);     
     		}
     	close(sockfd);
    	return 0; 
	}
