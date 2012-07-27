/*
 * funzioni_frontend.c
 *
 *  Created on: Jul 23, 2012
 *      Author: rommel
 */
#include "header_attuatore.h"

/**
 * stampa singola prenotazione in formato completo
 * @param p
 */
void stampa_prenot(coda *p) {
	printf("\n");
	printf("\tPrenotazione per processo: %d", p->messaggio->clientId);
	printf("\tTipo di servizio: %d", p->messaggio->kindof_service);
	printf("\tPriorità: %d", p->messaggio->priority);
	printf("\tTurno: %d", p->messaggio->turn);
	printf("\tPrezzo: %d", p->messaggio->price);
	printf("\n");
}

/**
 * stampa lista delle prenotazioni in formato breve
 * @param p
 */
void print(lista p) {
	if (p != NULL ) {
		printf("client %d, turno %d\n", p->messaggio->clientId,
				p->messaggio->turn);
		print(p->next);
	} else
		printf("\n\n");
}

void print_dettaglio(lista p){
	if (p != NULL ) {
		stampa_prenot(p);
		print(p->next);
	} else
		printf("\n\n");
}

/**
 * crea un nuovo elemento nella coda e ci inserisce il messaggio r
 * @param r messaggio da inserire
 * @return ritorna l'elemento creato
 */
coda * crea_nuovo1(reservation *r) {
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
		return crea_nuovo1(r);
	} else {
		if (c->next == NULL ) {
			c->next = crea_nuovo1(r);
		} else {
			if (c->messaggio->clientId > r->clientId) {
				coda *tmp = crea_nuovo1(r);
				tmp->next = c;
				return tmp;
			} else {
				if (c->next->messaggio->clientId < r->clientId)
					insert_by_pid(c->next, r);
				else {
					coda *tmp;
					tmp = c->next;
					c->next = crea_nuovo1(r);
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
void print_by_pid(coda * c) {
	coda * tmp = NULL;
	while (c) {
		tmp = insert_by_pid(tmp, c->messaggio);
		c = c->next;
	}

	print(tmp);
}

/**
 *Cerca la prenotazione con ID processo passato come parametro, stampa se trovata
 *altrimenti stampa prenotazione non trovata
 */
void cerca_prenot(coda *p, int proc_id) {
	if (p != NULL ) {
		if (p->messaggio->clientId == proc_id) {
			stampa_prenot(p);
		} else if (p->messaggio->clientId != proc_id && p->next != NULL ) {
			cerca_prenot(p->next, proc_id);
		} else{
			printf("\nPrenotazione non trovata\n\n");
		}
	} else {
		printf("\nAl momento non ci sono prenotazioni\n\n");
	}
}

/**
 * menu del forntend
 */
void menu() {
	printf("premere 1 per fare la ricerca\n");
	printf("premere 2 per stampare la lista in ordine di turno\n");
	printf("premere 3 per stampare la lista in ordine di pid\n");
	printf("premere 4 per stampare la lista in ordine di turno dettagliata");
	printf("premere 0 per uscire\n");
}
