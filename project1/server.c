#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>


void error(char *msg);
void toUpperCase(char bufferin[]);

int main(int argc, char* argv[]) {

	int set_reuse_addr = 1; // ON == 1  
	int sockfd;		// return from socket system call
	int newsockfd;	// return from accept system call
	int portno;		
	// int clilen;		// size of the address of the client (needed for the accept system call)
	socklen_t clilen;
	int n;			// return value from read() and write(). #chars read or writen
	
    char buffer[256];
	// The server reads characters from the socket connection into this buffer.
	// The server code has a server and client sockaddr_in:
	struct sockaddr_in serv_addr, cli_addr;

	// The user needs to pass in the port number on which the server 
	// will accept connections as an argument. 
	// This code displays an error message if the user fails to do this.
	if (argc < 2) {
		fprintf(stderr,"ERROR, no port provided\n");
		exit(1);
     }

	sockfd = socket(AF_INET, SOCK_STREAM, 0); 
	if (sockfd < 0) {
		error("ERROR opening socket");
	}

	// set all values to zero
	bzero((char *) &serv_addr, sizeof(serv_addr));
	// the port number on which the server will listen for connections
	// atoi - converts string of digits to an integer
	portno = atoi(argv[1]);

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(portno);
	serv_addr.sin_addr.s_addr = INADDR_ANY;

	// bind socket to address
	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
		error("ERROR on binding");
	}
	// 5 = size of the backlog queue, #connections that can be waiting 
	// while the process is handling a particular connection. 5=max size permitted by most systems
	listen(sockfd,5);

	clilen = sizeof(cli_addr);
	// The accept() system call causes the process to block until a client 
	// connects to the server. Thus, it wakes up the process when a connection 
	// from a client has been successfully established. It returns a new file
	// descriptor, and all communication on this connection should be done 
	// using the new file descriptor. The second argument is a reference 
	// pointer to the address of the client on the other end of the connection, 
	// and the third argument is the size of this structure.
	newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
	if (newsockfd < 0) {
		error("ERROR on accept");
	}
	bzero(buffer,256);
	n = read(newsockfd,buffer,255);
	if (n < 0) error("ERROR reading from socket");

	toUpperCase(buffer);

	printf("Here is the message in uppercase: %s\n",buffer);

	n = write(newsockfd,"I got your message",18);

	if (n < 0) error("ERROR writing to socket");

	close(newsockfd);
	close(sockfd);
	return 0;
}


void toUpperCase(char buffer[]) {
	int i = 0;
	while(buffer[i])
	{
	  buffer[i] = toupper(buffer[i]);
	  i++;
	}
}

void error(char *msg)
{
    perror(msg);
    exit(0);
}