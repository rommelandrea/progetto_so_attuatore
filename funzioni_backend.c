#include "header_attuatore.h"


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
coda * inserisci(coda *c, reservation *r) {
	if (c == NULL ) {
		return crea_nuovo(r);
	} else {
		if (c->next == NULL ) {
			c->next = crea_nuovo(r);
		} else {
			if (c->messaggio->turn > r->turn) {
				coda *tmp = crea_nuovo(r);
				tmp->next = c;
				return tmp;
			} else {
				if (c->next->messaggio->turn < r->turn)
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
