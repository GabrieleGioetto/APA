// Created by gabriele on 02/01/19.
//

#ifndef E01_QUOTAZIONI_H
#define E01_QUOTAZIONI_H

#include "quotazioneGiornaliera.h"

typedef struct bst_t* bst;

bst BSTinit();
void BSTnewNodo(quotazione item, bst b);
quotazione BSTsearch(bst bst, data d);
void BSTvisit(bst bst);
void BSTtrovaMinimoEMassimoTraDate(bst b, data d1, data d2);
void BSTtrovaMinimoEMassimo(bst b);
void BSTBilanciamento(bst b);

#endif //E01_QUOTAZIONI_H
