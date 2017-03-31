#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>

void error(char *msg);

int main(int argc, char* argv[]) {
	int sockfd;		// return from socket system call
	int newsockfd;	// return from accept system call
	int portno;		
	int clilen;		// size of the address of the client (needed for the accept system call)
	int n;			// return value from read() and write(). #chars read or writen


	// create a new socket
	// address domain of socket: AF_INET = internet domain for any two hosts on the internet
	// SOCK_STREAM = stream socket. characters are read in a continuous stream as if from a file or pipe
	// 0: TCP, if stream socket
	sockfd = socket(AF_INET, SOCK_STREAM, 0); 
	if (sockfd < 0) {
		error("ERROR opening socket");
	}
}

void error(char *msg)
{
    perror(msg);
    exit(0);
}