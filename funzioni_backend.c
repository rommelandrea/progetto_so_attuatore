#include "header_attuatore.h"

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
