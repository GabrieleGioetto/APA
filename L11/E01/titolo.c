//
// Created by gabriele on 02/01/19.
//

#include "titolo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BSTquotazioniGiornaliere.h"

struct titolo_t{
    char codice[MAX_LUNGH_TITOLO];
    int nTansazioni;
    bst quotazioniGiornaliere;
};

titolo initTitolo(){
    titolo t = malloc(sizeof *t);
    strcpy(t->codice,"");
    t->nTansazioni = 0;
    t->quotazioniGiornaliere = BSTinit();

    return t;
}

titolo setTitolo(char codice[], int nTransazioni, bst b){
    titolo t = initTitolo();

    strcpy(t->codice,codice);
    t->nTansazioni = nTransazioni;
    t->quotazioniGiornaliere = b;

    return t;
}

char* getCodice(titolo t){
    return t->codice;
}

int getNTransazioni(titolo t){
    return t->nTansazioni;
}

bst getBSTTitolo(titolo t){
    return t->quotazioniGiornaliere;
}