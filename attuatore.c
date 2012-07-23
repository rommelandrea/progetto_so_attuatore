/*
 * attuatore.c
 *
 *  Created on: Jul 10, 2012
 *      Author: rommel
 */

#include "header_proj.h"
#include "header_attuatore.h"
#include <pthread.h>

coda *coda_messaggi;

void *thread_back(void *arg) {
	printf("sono il backend\n");
	return NULL ;
}

void *thread_front(void *arg) {
	printf("sono il frontend\n");
	return NULL ;
}

int main(void) {
	pthread_t mythread, mythread2;

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

	//printf("\nmyglobal equals %d\n", myglobal);

	exit(0);
}
