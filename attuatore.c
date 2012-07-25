/*
 * attuatore.c
 *
 *      Author: Andrea Romanello
 */

#include "header_attuatore.h"
#include <pthread.h>

pthread_mutex_t mutex;
coda * prenotazioni = NULL;

/**
 * la funzione thread_back è il backend dell'attuatore
 * si mette in ascolto sulla coda passata come argomento
 * preleva i messaggi e li inserisci in ordine di turno sulla coda
 *
 * @param arg parametro per sapere su che coda ascoltare
 */
void *thread_back(int arg) {
	int n = 0;
	int mess;
	reservation * res = NULL;

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

	while (n < 3) {
		printf("in attesa di un messaggio\n");

		res = calloc(1, sizeof(reservation));
		msgrcv(mess, res, sizeof(reservation), TORES, 0);
		printf("ricevuto messaggio\n");

		pthread_mutex_lock(&mutex);
		prenotazioni = inserisci(prenotazioni, res);
		pthread_mutex_unlock(&mutex);

		n++;
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

/**
 * main dell'attuatore
 * riceve in ingresso il numero di coda sul quale mettersi in ascolto
 * crea due thread, uno per il frontend e l'altro sul backend che procedono in parallelo
 *
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char **argv) {
	if (argc < 2) {
		perror("Miss argument");
		exit(EXIT_FAILURE);
	}

	int argomento;

	if (sscanf(argv[1], "%d", &argomento) <= 0) {
		printf("First parameter must be an integer \n");
		exit(EXIT_FAILURE);
	}

	pthread_t THR_QUEUE;
	pthread_t THR_INPUT;

	pthread_mutex_init(&mutex, NULL );

	if (pthread_create(&THR_QUEUE, NULL, thread_back, argomento)) {
		perror("error creating thread.");
		exit(EXIT_FAILURE);
	}

	if (pthread_create(&THR_INPUT, NULL, thread_front, NULL )) {
		perror("error creating thread.");
		exit(EXIT_FAILURE);
	}

	if (pthread_join(THR_INPUT, NULL )) {
		perror("error joining thread.");
		exit(EXIT_FAILURE);
	}

	if (pthread_join(THR_QUEUE, NULL )) {
		perror("error joining thread.");
		exit(EXIT_FAILURE);
	}

	exit(EXIT_SUCCESS);
}
