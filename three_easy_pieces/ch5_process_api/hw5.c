#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
	printf("main process running... (pid:%d)\n", (int) getpid());

	int rc = fork();
	if (rc < 0) {
		fprintf(stderr, "fork failed\n");
	} else if (rc == 0) {
		// child
		printf("hello i am in child (pid:%d)\n", (int) getpid());
	} else {
		// parent
		int wc = wait(NULL);
		printf("hello i am in parent of %d (pid:%d)\n", rc, (int) getpid());
		printf("return value from wait = %d\n", wc);
	}
	return 0;
}

// return value from wait is the child process id



