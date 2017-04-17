#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	printf("location of code: %p\n", (void *) main);
	float *a = malloc(1);
	float *b = malloc(100);
	printf("location of heap: %p\n", (void *) &a);
	printf("location of heap 1 byte later: %p\n", (void *) &b);

	int x = 3;
	int y = 6;
	printf("location of stack: %p\n", (void *) &x);
	printf("location of stack 2 bytes later: %p\n", (void *) &y);

	return x;
}