//
// Created by gabriele on 02/01/19.
//

#ifndef E01_TITOLO_H
#define E01_TITOLO_H
#define MAX_LUNGH_TITOLO 20
#include "BSTquotazioniGiornaliere.h"

typedef struct titolo_t* titolo;

titolo initTitolo();
titolo setTitolo(char codice[], int nTransazioni, bst b);
char* getCodice(titolo t);
int getNTransazioni(titolo t);
bst getBSTTitolo(titolo t);

#endif //E01_TITOLO_H
