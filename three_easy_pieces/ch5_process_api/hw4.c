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
		char *args1[] = {"ls", "-la", NULL};
		execvp("/bin/ls", args1);
	} else {
		// parent
		char *args1[] = {"ls", "-la", NULL};
		execvp("/bin/ls", args1);
	}
	return 0;
}

// ls does not appear to run in both parent and child processes



