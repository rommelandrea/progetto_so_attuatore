#include "header_attuatore.h"

coda * crea_nuovo(reservation *r) {
	coda *c;
	c = calloc(1, sizeof(coda));
	c->messaggio = r;
	c->next = NULL;

	return c;
}

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

/*
coda * crea_nuovo(reservation *r) {
	coda *new = malloc(sizeof(coda));

	new->messaggio = r;
	new->next = NULL;

	return new;
}

coda * inserisci(reservation *r, coda * n) {
	if (n == NULL || n->messaggio->turn > r->turn) {
		coda *new = crea_nuovo(r);
		new->next = n;
		return new;
	} else {
		coda *primo = n;
		if (n->next != NULL ) {
			if (r->turn > n->next->messaggio->turn)
				inserisci(r, n->next);
			else {
				coda *tmp = n->next;
				n->next = crea_nuovo(r);
				n->next->next = tmp;
			}
		} else {
			if (n->next == NULL )
				n->next = crea_nuovo(r);
			else {

			}
		}
		return primo;
	}
}
*/
