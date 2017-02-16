#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define BUF_SIZE 3

int buffer[BUF_SIZE];
int add = 0;	// index of add element
int rem = 0;	// index of remove element
int num = 0;	// number of elements in buffer

// mutex lock for buffer
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
// consumer waits on cv
pthread_cond_t c_cons = PTHREAD_COND_INITIALIZER;
// producer waits on cv
pthread_cond_t c_prod = PTHREAD_COND_INITIALIZER;

void *producer (void *param);
void *consumer (void *param);

int main(int argc, char *argv[]) {
	pthread_t tid1, tid2;
	int i;

	if (pthread_create(&tid1, NULL, producer, NULL) != 0) {
		fprintf(stderr, "Unable to create producer thread\n");
		exit(1);
	}

	if (pthread_create(&tid2, NULL, consumer, NULL) != 0) {
		fprintf(stderr, "Unable to create consumer thread\n");
		exit(1);
	}
	pthread_join(tid1, NULL); // wait for producer to exit
	pthread_join(tid2, NULL); // wait for consumer to exit
	printf("Parent quiting\n");
}

void *producer (void *param) {
	int i;
	for (i = 1; i <= 20; i++) {
		pthread_mutex_lock (&m);
			if (num > BUF_SIZE) {
				// overflow
				exit(1);
			}
			while (num == BUF_SIZE) {
				// block if buffer is full
				pthread_cond_wait(&c_prod, &m);
			}
			// buffer not full so add element
			buffer[add] = i;
			add = (add+1) % BUF_SIZE;
			num++;
		pthread_mutex_unlock (&m);

		pthread_cond_signal (&c_cons);
		printf ("Producer: inserted %d\n", i); fflush (stdout);
	}
	printf("producer quitting\n"); fflush(stdout);
	return 0;
}
void *consumer (void *param) {
	int i;

	while (1) {
		pthread_mutex_lock(&m);
			if (num < 0) {
				// underflow
				exit (1);
			}
			while (num == 0) {
				// block if buffer empty
				pthread_cond_wait(&c_cons, &m);
			}
			i = buffer[rem];
			rem = (rem+1) % BUF_SIZE;
			num--;
		pthread_mutex_unlock(&m);

		pthread_cond_signal(&c_prod);
		printf("Consumer value %d\n", i); fflush(stdout);
	}
	return 0;
}



