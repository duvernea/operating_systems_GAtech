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
	
	/* 
		A sockaddr_in is a structure containing an internet address. This structure is defined in netinet/in.h.

		Here is the definition:

		struct sockaddr_in
		{
		  short   sin_family; // must be AF_INET 
		  u_short sin_port;
		  struct  in_addr sin_addr;
		  char    sin_zero[8]; // Not used, must be zero 
		};
	*/
	struct sockaddr_in serv_addr;
	/*		The variable server is a pointer to a structure of type hostent. This structure is defined in the header file netdb.h as follows:

			struct  hostent {
			    char    *h_name;        // official name of host 
			    char    **h_aliases;    // alias list 
			    int     h_addrtype;     // host address type 
			    int     h_length;       // length of address 
			    char    **h_addr_list;  // list of addresses from name server 
			#define h_addr  h_addr_list[0]  // address, for backward compatiblity 
			};
			It defines a host computer on the Internet. The members of this structure are:
			h_name       Official name of the host.

			h_aliases    A zero  terminated  array  of  alternate
			         names for the host.

			h_addrtype   The  type  of  address  being  returned;
			         currently always AF_INET.

			h_length     The length, in bytes, of the address.

			h_addr_list  A pointer to a list of network addresses
			         for the named host.  Host addresses are
			         returned in network byte order.
			Note that h_addr is an alias for the first address in the array of network addresses. */
	struct hostent *server;

	// create a new socket
	// address domain of socket: AF_INET = internet domain for any two hosts on the internet
	// SOCK_STREAM = stream socket. characters are read in a continuous stream as if from a file or pipe
	// 0: TCP, if stream socket

	char buffer[256];
	if (argc < 3) {
		fprintf(stderr, "usage %s hostname port\n", argv[0]);
		exit(0);
	}
	portno = atoi(argv[2]);



	sockfd = socket(AF_INET, SOCK_STREAM, 0); 
	if (sockfd < 0) {
		error("ERROR opening socket");
	}
	// argv[1] is a host on the internet, eg cs.rpi.edu
	// returns pointer to hostent, containing info about the host
	server = gethostbyname(argv[1]);
	if (server == NULL) {
		fprintf(stderr, "ERROR, no such host\n");
		exit(0);
	}
	// bzero - sets all values in buffer to zero
	bzero((char *) &serv_addr, sizeof(serv_addr));
	// The variable serv_addr is a structure of type struct sockaddr_in. 
	// This structure has four fields. The first field is short sin_family, 
	// which contains a code for the address family. 
	// It should always be set to the symbolic constant AF_INET.
	serv_addr.sin_family = AF_INET;

	bcopy((char *)server->h_addr,
	      (char *)&serv_addr.sin_addr.s_addr,
	      server->h_length);
	// The second field of serv_addr is unsigned short sin_port, 
	// which contain the port number. However, instead of simply copying 
	// the port number to this field, it is necessary to convert this to 
	// network byte order using the function htons() which converts a 
	// port number in host byte order to a port number in network byte order.
	serv_addr.sin_port = htons(portno);

	// The connect function is called by the client to establish a 
	// connection to the server. It takes three arguments, the socket 
	// file descriptor, the address of the host to which it wants to connect 
	// (including the port number), and the size of this address. 
	// This function returns 0 on success and -1 if it fails.   
	// Notice that the client needs to know the port number of the server, 
	// but it does not need to know its own port number. 
	// This is typically assigned by the system when connect is called.
	if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");
    printf("Please enter the message: ");
    bzero(buffer,256);
    fgets(buffer,255,stdin);
}

void error(char *msg)
{
    perror(msg);
    exit(0);
}