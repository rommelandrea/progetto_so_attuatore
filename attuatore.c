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

	printf("sono il backend\n");

	if(arg == 0){
		printf("caso 0\n");
		mess = msgget(OPH_queue_KEY, 0);
		if (mess < 0) {
			perror("Unable to open message queue");
			exit(1);
		}
		printf("in attesa di un messaggio\n");
		msgrcv(mess, res, sizeof(reservation), TORES, 0);
		printf("ricevuto messaggio\n");
	}
	if(arg == 1){
		printf("caso 1\n");
		mess = msgget(ORT_queue_KEY, 0);
		if (mess < 0) {
			perror("Unable to open message queue");
			exit(1);
		}
		printf("in attesa di un messaggio\n");
		msgrcv(mess, res, sizeof(reservation), TORES, 0);
		printf("ricevuto messaggio\n");
	}
	if(arg == 2){
		printf("caso 2\n");
		mess = msgget(RAD_queue_KEY, 0);
		if (mess < 0) {
			perror("Unable to open message queue");
			exit(1);
		}
		printf("in attesa di un messaggio\n");
		msgrcv(mess, res, sizeof(reservation), TORES, 0);
		printf("ricevuto messaggio\n");
	}

	pthread_mutex_lock(&mutex);
	prenotazioni = inserisci(res, prenotazioni);
	pthread_mutex_unlock(&mutex);

	stampa(prenotazioni);
	return NULL ;
}

void stampa(lista p){
	if(p!= NULL){
	printf("client %d, turno %d\n", p->messaggio->clientId, p->messaggio->turn);
	stampa(p->next);
	}
}

void *thread_front(void *arg) {
	pthread_mutex_lock(&mutex);
	printf("sono il frontend\n");
	sleep(2);
	pthread_mutex_unlock(&mutex);
	return NULL ;
}

int main(int argc, char **argv) {
	pthread_t th_front, th_back;
	int argomento;

	argomento = atoi(argv[1]);

	pthread_mutex_init(&mutex, NULL );
/*
	if (pthread_create(&th_front, NULL, thread_front, NULL )) {
		printf("error creating thread.");
		abort();
	}
*/
	if (pthread_create(&th_back, NULL, thread_back, argomento )) {
		perror("error creating thread.");
		abort();
	}
/*
	if (pthread_join(th_front, NULL )) {
		printf("error joining thread.");
		abort();
	}
*/
	if (pthread_join(th_back, NULL )) {
		perror("error joining thread.");
		abort();
	}

	//stampa(prenotazioni);

	exit(0);
}
