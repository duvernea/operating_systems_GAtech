#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <fcntl.h>



int main(int argc, char *argv[]) {
	int fd = open("file", O_WRONLY | O_CREAT, 0777 | O_TRUNC);
	assert(fd > -1);
	// close(fd);
	printf("main process running... (pid:%d)\n", (int) getpid());


	int rc = fork();
	if (rc < 0) {
		fprintf(stderr, "fork failed\n");
	} else if (rc == 0) {
		// child
		char* childMsg = "Child process writing to file\n";
		int len = 0;
		while (childMsg[len] != '\0') {
    		len++;
		}
		int w = write(fd, childMsg, len);
		assert(w == len);
	} else {
		// parent
		char* parentMsg = "Parent process writing to file\n";
		int len = 0;
		while (parentMsg[len] != '\0') {
    		len++;
		}
		int w = write(fd, parentMsg, len);
		assert(w == len);
	}
	return 0;
}

// Both parent and child appear to write to file successfully
// Parent always writing first out of 10 trials



