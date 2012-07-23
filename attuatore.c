/*
 * attuatore.c
 *
 *  Created on: Jul 10, 2012
 *      Author: rommel
 */

//#include "header_proj.h"
#include "header_attuatore.h"
#include <pthread.h>

pthread_mutex_t mutex;
lista prenotazioni = NULL;

void *thread_back(void *arg) {
	pthread_mutex_lock(&mutex);
	printf("sono il backend\n");
	sleep(2);
	pthread_mutex_unlock(&mutex);
	return NULL ;
}

void *thread_front(void *arg) {
	pthread_mutex_lock(&mutex);
	printf("sono il frontend\n");
	sleep(2);
	pthread_mutex_unlock(&mutex);
	return NULL ;
}

int main(int argc, char **argv) {
	pthread_t mythread, mythread2;

	pthread_mutex_init(&mutex, NULL );

	if (pthread_create(&mythread, NULL, thread_front, NULL )) {
		printf("error creating thread.");
		abort();
	}

	if (pthread_create(&mythread2, NULL, thread_back, NULL )) {
		printf("error creating thread.");
		abort();
	}

	if (pthread_join(mythread, NULL )) {
		printf("error joining thread.");
		abort();
	}

	if (pthread_join(mythread2, NULL )) {
		printf("error joining thread.");
		abort();
	}

	exit(0);
}
