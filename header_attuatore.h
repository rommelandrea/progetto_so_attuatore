/*
 * header_attuatore.h
 *
 *  Created on: Jul 20, 2012
 *      Author: rommel
 */

#ifndef HEADER_ATTUATORE_H_
#define HEADER_ATTUATORE_H_

#include "header_proj.h"

typedef struct _coda{
	reservation * messaggio;
	struct _coda *next;
} coda;

typedef coda *lista;

void stampa(coda *);
coda * inserisci(coda *, reservation *);


#endif /* HEADER_ATTUATORE_H_ */
