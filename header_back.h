/*
 * header_back.h
 *
 *  Created on: Jul 27, 2012
 *      Author: Andrea Romanello, Amir Curic
 */

#ifndef HEADER_BACK_H_
#define HEADER_BACK_H_

coda * inserisci(coda *, reservation *);
coda * insert_by_pid(coda *, reservation *);
void free_list(coda *);
int check(char *);

#endif /* HEADER_BACK_H_ */
