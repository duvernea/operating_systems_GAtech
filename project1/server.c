#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>

void error(char *msg);


int main(int argc, char* argv[]) {
	return 0;
}


void error(char *msg)
{
    perror(msg);
    exit(0);
}