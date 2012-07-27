/*
 * header_attuatore.h
 *
 *  Created on: Jul 20, 2012
 *      Author: rommel
 */

#include "header_proj.h"

#ifndef HEADER_ATTUATORE_H_
#define HEADER_ATTUATORE_H_

typedef struct _coda{
	reservation * messaggio;
	struct _coda *next;
} coda;

typedef coda *lista;

#endif /* HEADER_ATTUATORE_H_ */
