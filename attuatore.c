/*
 * attuatore.c
 *
 *      Author: Andrea Romanello
 */

#include "header_attuatore.h"
#include "header_back.h"
#include "header_front.h"
#include <pthread.h>

pthread_mutex_t mutex;
coda * prenotazioni = NULL;
int loop;

/**
 * la funzione thread_back e' il backend dell'attuatore
 * si mette in ascolto sulla coda passata come argomento
 * preleva i messaggi e li inserisci in ordine di turno sulla coda
 *
 * @param arg parametro per sapere su che coda ascoltare
 */
void * thread_back(void * a) {
	int mess;
	int *arg;
	reservation *res;

	arg =(int *) a;
	res = NULL;

	/*
	printf("\nargomento %d\n", arg);
	*/

	if (*arg == 0) {
		/*printf("coda 0\n");*/
		mess = msgget(OPH_queue_KEY, 0);
		if (mess < 0) {
			perror("Unable to open message queue");
			exit(1);
		}
	}
	if (*arg == 1) {
		/*printf("coda 1\n");*/
		mess = msgget(ORT_queue_KEY, 0);
		if (mess < 0) {
			perror("Unable to open message queue");
			exit(1);
		}
	}

	if (*arg == 2) {
		/*printf("coda 2\n");*/
		mess = msgget(RAD_queue_KEY, 0);
		if (mess < 0) {
			perror("Unable to open message queue");
			exit(1);
		}
	}

	/*
	printf("sono il backend\n");
	*/

	while (loop) {
		/*printf("in attesa di un messaggio\n");*/

		res = calloc(1, sizeof(reservation));
		msgrcv(mess, res, sizeof(reservation), TORES, 0);
		/*printf("ricevuto messaggio\n");*/

		pthread_mutex_lock(&mutex);
		prenotazioni = inserisci(prenotazioni, res);
		pthread_mutex_unlock(&mutex);
	}
	printf("esco dal thread backend\n");

	pthread_exit(NULL );
}

void * thread_front(void *arg) {
	int scelta;
	int pid;
	do{

		menu();

		scanf("%d", &scelta);

		switch(scelta){
		case 1:

			printf("inserire il pid da cercare: ");
			scanf("%d", &pid);
			pthread_mutex_lock(&mutex);
			cerca_prenot(prenotazioni, pid);
			pthread_mutex_unlock(&mutex);
			break;
		case 2:
			pthread_mutex_lock(&mutex);
			print(prenotazioni);
			pthread_mutex_unlock(&mutex);
			break;
		case 3:
			pthread_mutex_lock(&mutex);
			print_by_pid(prenotazioni);
			pthread_mutex_unlock(&mutex);
			break;
		case 4:
			pthread_mutex_lock(&mutex);
			print_dettaglio(prenotazioni);
			pthread_mutex_unlock(&mutex);
			break;
		case 0:
			loop = 0;
			break;

		default:
			printf("scelta errata\n\n\n");
			break;
		}

	}while(scelta != 0);

	printf("esco dal frontend\n");

	pthread_exit((void *)NULL);
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
	int argomento;

	pthread_t THR_QUEUE;
	pthread_t THR_INPUT;
	loop = 1;

	if (argc < 2) {
		perror("Miss argument");
		exit(EXIT_FAILURE);
	}

	if (sscanf(argv[1], "%d", &argomento) <= 0) {
		printf("First parameter must be an integer \n");
		exit(EXIT_FAILURE);
	}

	pthread_mutex_init(&mutex, NULL );

	if (pthread_create(&THR_QUEUE, NULL, thread_back, (void *)&argomento)) {
		perror("error creating thread.");
		exit(EXIT_FAILURE);
	}

	if (pthread_create(&THR_INPUT, NULL, thread_front, NULL )) {
		perror("error creating thread.");
		exit(EXIT_FAILURE);
	}
/*
	if (pthread_join(THR_QUEUE, NULL )) {
		perror("error joining thread.");
		exit(EXIT_FAILURE);
	}
*/
	if (pthread_join(THR_INPUT, NULL )) {
		perror("error joining thread.");
		exit(EXIT_FAILURE);
	}

	printf("\n\nATTUATORE TERMINATO\n");

	exit(EXIT_SUCCESS);
}
