/*
 * funzioni_frontend.c
 *
 *  Created on: Jul 23, 2012
 *      Author: rommel
 */
#include "header_attuatore.h"

void print(lista p) {
	if (p != NULL ) {
		printf("client %d, turno %d\n", p->messaggio->clientId,
				p->messaggio->turn);
		stampa(p->next);
	}else
		printf("\n\n");
}


/**
 * crea un nuovo elemento nella coda e ci inserisce il messaggio r
 * @param r messaggio da inserire
 * @return ritorna l'elemento creato
 */
coda * crea_nuovo(reservation *r) {
	coda *c;
	c = calloc(1, sizeof(coda));
	c->messaggio = calloc(1, sizeof(reservation));
	c->messaggio = r;
	c->next = NULL;

	return c;
}

/**
 * inserisce un pessaggio r sulla coda c
 * @param c coda sul quale fare l'inserimento
 * @param r messaggio da inserire
 * @return return della coda
 */
coda * insert_by_pid(coda *c, reservation *r) {
	if (c == NULL ) {
		return crea_nuovo(r);
	} else {
		if (c->next == NULL ) {
			c->next = crea_nuovo(r);
		} else {
			if (c->messaggio->clientId > r->clientId) {
				coda *tmp = crea_nuovo(r);
				tmp->next = c;
				return tmp;
			} else {
				if (c->next->messaggio->clientId < r->clientId)
					inserisci(c->next, r);
				else {
					coda *tmp;
					tmp = c->next;
					c->next = crea_nuovo(r);
					c->next->next = tmp;
				}
			}
		}
	}
	return c;
}

/**
 * stampa una copia della coda ordinata secondo il num di pid
 * @param c coda originale
 */
void print_by_pid(coda * c){
	coda * tmp = NULL;
	while(c){
		tmp = calloc(1, sizeof(coda));
		tmp->messaggio = calloc(1, sizeof(reservation));
		tmp = insert_by_pid(tmp, c->messaggio);
		c = c->next;
	}

	stampa(tmp);
}

void menu(){
	printf("premere 1 per fare la ricerca\n");
	printf("premere 2 per stamapare la lista in ordine di turno\n");
	printf("premere 3 per stamapare la lista in ordine di pid\n");
	printf("premere 4 per uscire\n");
}
