#include <pthread.h>
#include <stdio.h>

void *foo (void *arg) { /* thread main */
	printf("Foobar!\n");
	pthread_exit(NULL);
}

int main(void) {

	int i;
	pthread_t tid;
	pthread_attr_t attr;

	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	// share resources equally with other threads in system
	pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);
	
	pthread_create(&tid, &attr, foo, NULL);

	return 0;

}


// pthread_attr_t - can define stack size, scheduling policy, priority
// can set scope - system / process
// joinable
// has default behavior with NULL in pthread_create

// pthread_attr_init or destroy - create and initialize the attribute structure
// set get 

// joinable - 
// Detatching pthreads
// Default - Joinable threads - parent thread creates threads and can join them at later points in time
// children can turn into zombies if parent exits early

// in pthreads, threads can be detatched from parents, children are free

// pthread_detatch() - 
// detatched threads can be created

// int pthread_create(pthread_t *thread,
// 	const pthread_attr_t *attr,
// 	void * (*start_routine)(void *),
// 	void *arg);

// int pthread_join(pthread_t thread,
// 	void **status);




