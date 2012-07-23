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
	reservation messaggio;
	struct _coda *next;
} coda;

coda inizializza_coda();
coda aggiungi_elem();

#endif /* HEADER_ATTUATORE_H_ */
