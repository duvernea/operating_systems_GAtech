#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>



int main(int argc, char *argv[]) {
	int a = 100;
	printf("main process running... (pid:%d)\n int a = %d\n", (int) getpid(), a);


	int rc = fork();
	if (rc < 0) {
		fprintf(stderr, "fork failed\n");
	} else if (rc == 0) {
		a = 50;
		printf("hello, I am child (pid:%d)\n int a = %d\n", (int) getpid(), a);
		// child
	} else {
		// parent
		// a = 75;
		printf("hello, I am parent of child %d (pid:%d)\n int a = %d\n", rc, (int) getpid(), a);
	}
	return 0;
}

// Note: Parent and child process have initial value set in main, 
// but, will have independent memory in parent in child once fork is called



