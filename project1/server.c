#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>

void error(char *msg);


int main(int argc, char* argv[]) {
	int sockfd;		// return from socket system call
	int newsockfd;	// return from accept system call
	int portno;		
	int clilen;		// size of the address of the client (needed for the accept system call)
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

	return 0;
}


void error(char *msg)
{
    perror(msg);
    exit(0);
}