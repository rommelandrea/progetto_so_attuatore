/*
 * funzioni_frontend.c
 *
 *  Created on: Jul 23, 2012
 *      Author: rommel
 *
 * In questo file sono presenti tutte le funzioni necessarie
 * per la visualizzazione della coda di messaggi
 */

#include "header_front.h"

/**
 * stampa singola prenotazione in formato completo
 * @param p elemento della lista da stampare
 */
void stampa_prenot(coda *p) {
	printf("\n");
	printf("\tPrenotazione per processo: %d\n", p->messaggio->clientId);
	printf("\t  Tipo di servizio: %d\n", p->messaggio->kindof_service);
	printf("\t  Priorità: %d\n", p->messaggio->priority);
	printf("\t  Turno: %d\n", p->messaggio->turn);
	printf("\t  Prezzo: %d\n", p->messaggio->price);
	printf("\t.....................................\n");
}

/**
 * stampa lista delle prenotazioni in formato breve
 * @param p lista da stampare
 */
void print(lista p) {
	if (p != NULL ) {
		printf("\t Client %d, turno %d\n", p->messaggio->clientId,
				p->messaggio->turn);
		print(p->next);
	} else
		printf("\n\n");
}

/**
 * stampa la lista in maniera dettagliata
 * @param p lista da stampare
 */
void print_dettaglio(lista p){
	if (p != NULL ) {
		stampa_prenot(p);
		print_dettaglio(p->next);
	} else
		printf("\n\n");
}

/**
 * stampa una copia della coda ordinata secondo il num di pid
 * @param c coda originale
 */
void print_by_pid(lista c) {
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
void cerca_prenot(lista p, int proc_id) {
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
	printf("\n");
	printf("\tInserire l'operazione desiderata:\n");
	printf("\t  [1] ricerca\n");
	printf("\t  [2] stampa la lista in ordine di turno\n");
	printf("\t  [3] stampa la lista in ordine di pid\n");
	printf("\t  [4] stampa la lista in ordine di turno dettagliata\n");
	printf("\t  [9] uscita\n");
	printf("\n");
	printf("\t=> Scelta: ");
}
