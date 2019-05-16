//
// Created by gabriele on 07/12/18.
//

#ifndef E03_PERSONAGGI_H
#define E03_PERSONAGGI_H

#define MAX_LUNGH_STR 50
#define MAX_LUNGH_CODICE 7
#define FILE_PG "pg.txt"

#include "inventario.h"

typedef struct{
    int inUso;
    inv_t** vettEq;//Vettore di puntatori a inv_t
}tabEquip_t;

typedef struct{
    char codice[MAX_LUNGH_CODICE];
    char nome[MAX_LUNGH_STR];
    char classe[MAX_LUNGH_STR];
    tabEquip_t equip;
    stat_t stat;
}pg_t;

typedef struct nodo{
    pg_t pg;
    struct nodo* next;
}nodoPg_t, *link;

typedef struct {
    link headPg;
    link tailPg;
    int nPg;
}tabPg_t;

void leggiFilePG(tabPg_t* tabPg, int nInv);
void stampaPersonaggio(pg_t personaggio);
void newNodePersonaggio(tabPg_t *tabPg, pg_t personaggio);
void aggiungiPG(tabPg_t *tabPg, int nInv);
void stampaListaPersonaggi(tabPg_t* tabPg);
link trovaPgByCodice(tabPg_t *tabPg);
void eliminaPG(tabPg_t *tabPg);
void aggiungiOggettoAPersonaggio(tabPg_t *tabPg, tabInv_t *tabInv);
void rimuoviOggettoAPersonaggio(tabPg_t *tabPg);
void calcolaStatistichePersonaggio(tabPg_t *tabPg);
void stampaStatistiche(stat_t stat);
void controlloStatisticheMinoriDiZero(stat_t *stat);
void deallocaPG(tabPg_t *tabPg);

#endif
