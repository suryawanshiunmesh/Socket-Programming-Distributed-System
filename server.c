// main server

//header files declaration
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h> 
#include<sys/socket.h>
#include<netinet/in.h>

//error function
void error(const char *msg)
{
	perror(msg);
	exit(1);
	}

//main function
int main(int argc, char *argv[])
{
 	int sockfd, newsockfd, portno, option;
	socklen_t clilen;
	char buffer[256];
	struct sockaddr_in serv_addr, cli_addr;
	int n;

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
	     
     	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
    		error("Error..! On binding..!\n");
     
     
     	while(1)
     {
	    	listen(sockfd,5);
	     	clilen = sizeof(cli_addr);
	     	newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);	     
	     	if (newsockfd < 0) 
		  	error("Error..! On accept..!\n");
		//display the menu to select the arithmetic operation
	     	strcpy(buffer,"You are connected to Main Server..! \n\n1. Addition: \n2. Subtraction: \n3. Multiplication: \n4. Division: \n\nChoose Your Operation: ");
	     	n = write(newsockfd,buffer,strlen(buffer));
	     	if (n < 0) 
	     		error("Error..! Writing to socket..!\n");
	       
	     	bzero(buffer,256);
	     	n = read(newsockfd,buffer,255);
	     	if (n < 0) 
	     		error("Error..! Reading from socket..!\n");	     
	     	printf("Here is the message: %s\n",buffer);
	     
	     	option = atoi(buffer);
	     
	     	printf("Option Selected : %d",option);
	    	
		// provide the ip address and port number of opration server to perfrom arithmetic operation 
	     	if(option==1)
	     	{
	     		strcpy(buffer,"\nDetails of Addition Server: \n\nIP/Hostname: localhost\nPort: 6000");
	     		}	     
	     	else if(option==2)
	     	{
	     		strcpy(buffer,"\nDetails of Subtraction Server: \n\nIP/Hostname: localhost\nPort: 6500");
	     		}
	     	else if(option==3)
	     	{
	     		strcpy(buffer,"\nDetails of Multiplication Server: \n\nIP/Hostname: localhost\nPort: 7000");
	     		}
	     	else if(option==4)
	     	{
	     	strcpy(buffer,"\nDetails of Division Server: \n\nIP/Hostname: localhost\nPort: 7500");
	     		}
	     
	     	n = write(newsockfd,buffer,strlen(buffer));
	     	if (n < 0) 
	     		error("Error..! Writing to socket..!\n");
	     
	     	close(newsockfd);     
     		}
     	close(sockfd);
    	return 0; 
	}
