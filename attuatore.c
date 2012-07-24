/*
 * attuatore.c
 *
 *      Author: Andrea Romanello
 */

#include "header_attuatore.h"
#include <pthread.h>

pthread_mutex_t mutex;
lista prenotazioni = NULL;

void *thread_back(int arg) {
	int mess;
	reservation * res = NULL;
	res = malloc(sizeof(reservation));

	printf("\nargomento %d\n", arg);

	if (arg == 0) {
		printf("caso 0\n");
		mess = msgget(OPH_queue_KEY, 0);
		if (mess < 0) {
			perror("Unable to open message queue");
			exit(1);
		}
	}
	if (arg == 1) {
		printf("caso 1\n");
		mess = msgget(ORT_queue_KEY, 0);
		if (mess < 0) {
			perror("Unable to open message queue");
			exit(1);
		}
	}

	if (arg == 2) {
		printf("caso 2\n");
		mess = msgget(RAD_queue_KEY, 0);
		if (mess < 0) {
			perror("Unable to open message queue");
			exit(1);
		}
	}
	printf("sono il backend\n");

	while (TRUE) {
		printf("in attesa di un messaggio\n");
		msgrcv(mess, res, sizeof(reservation), TORES, 0);
		printf("ricevuto messaggio\n");

		pthread_mutex_lock(&mutex);
		prenotazioni = inserisci(prenotazioni, res);
		pthread_mutex_unlock(&mutex);

		stampa(prenotazioni);
	}
	printf("esco dal thread backend\n");
	pthread_exit(NULL );
}

void *thread_front(void *arg) {
	while (TRUE) {
		pthread_mutex_lock(&mutex);
		printf("stampo le prenotazioni\n");
		stampa(prenotazioni);
		sleep(5);
		pthread_mutex_unlock(&mutex);
	}
	pthread_exit(NULL );
}

int main(int argc, char **argv) {
	if (argc < 2) {
		perror("Miss argument");
		exit(1);
	}

	pthread_t th_front, th_back;
	int argomento;

	argomento = atoi(argv[1]);

	pthread_mutex_init(&mutex, NULL );

//	if (pthread_create(&th_front, NULL, thread_front, NULL )) {
//		perror("error creating thread.");
//		abort();
//	}

	if (pthread_create(&th_back, NULL, thread_back, (void *) argomento)) {
		perror("error creating thread.");
		abort();
	}

//	if (pthread_join(th_front, NULL )) {
//		perror("error joining thread.");
//		abort();
//	}

	if (pthread_join(th_back, NULL )) {
		perror("error joining thread.");
		abort();
	}

	exit(0);
}
