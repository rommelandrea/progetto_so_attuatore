/*
 * thread.c
 *
 *  Created on: Jul 21, 2012
 *      Author: rommel
 */

#include <stdio.h>
#include <pthread.h>
#include <linux/stddef.h>
#include <stdlib.h>

typedef struct _node {
	int value;
	struct _node * next;
} nodo;

typedef nodo * lista;

nodo * crea_nuovo(int val) {
	nodo *new = malloc(sizeof(nodo));

	new->value = val;
	new->next = NULL;

	return new;
}

void inserisci(int val, nodo * n) {

	if (val > n->value && n->next != NULL ) {
		inserisci(val, n->next);
	} else {
		if (n->next == NULL )
			n->next = crea_nuovo(val);
		else {
			nodo *tmp = n->next;
			n->next = crea_nuovo(val);
			n->next->next = tmp;
		}
	}
}

void stampa(lista l) {
	printf("%d --> ", l->value);
	if (l->next != NULL )
		stampa(l->next);
	else
		printf("\n\n");
}

void * thread1() {
	int i = 0;
	while (i < 10) {
		printf("Hello!!\n");
		sleep(1);
		i++;
	}
}

void * thread2() {
	int i = 0;
	while (i < 10) {
		printf("How are you?\n");
		sleep(1);
		i++;
	}
}

int main() {
	int status;
	pthread_t tid1, tid2;

	lista c;
	c = crea_nuovo(10);

	stampa(c);

	inserisci(20, c);
	stampa(c);

	inserisci(30, c);
	stampa(c);

	inserisci(25, c);
	stampa(c);

	//pthread_create(&tid1, NULL, thread1, NULL );
	//pthread_create(&tid2, NULL, thread2, NULL );

	//pthread_join(tid1, NULL );
	//pthread_join(tid2, NULL );

	return 0;
}
