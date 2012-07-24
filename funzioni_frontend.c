/*
 * funzioni_frontend.c
 *
 *  Created on: Jul 23, 2012
 *      Author: rommel
 */
#include "header_attuatore.h"

void stampa(lista p) {
	if (p != NULL ) {
		printf("client %d, turno %d\n", p->messaggio->clientId,
				p->messaggio->turn);
		stampa(p->next);
	}else
		printf("\n\n");
}
