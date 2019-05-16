#ifndef E03_PERSONAGGI_LIST_H
#define E03_PERSONAGGI_LIST_H

#define MAX_LUNGH_STR 50
#define MAX_LUNGH_CODICE 7
#define FILE_PG "pg.txt"

typedef struct tabPg_t* tabPg_p;
typedef struct tabInv_t* tabInv_p;
typedef struct pg_t* pg_p;
typedef struct nodo* link;

void leggiFilePG(tabPg_p tabPg);
void newNodePersonaggio(tabPg_p tabPg, pg_p personaggio);
void aggiungiPG(tabPg_p tabPg );
void stampaListaPersonaggi(tabPg_p tabPg);
link trovaPgByCodice(tabPg_p tabPg);
void eliminaPG(tabPg_p tabPg);
void aggiungiOggettoAPersonaggio(tabPg_p tabPg,tabInv_p tabInv);
void rimuoviOggettoAPersonaggio(tabPg_p tabPg);
void calcolaStatistichePersonaggio(tabPg_p tabPg);
void deallocaPG(tabPg_p tabPg);
tabPg_p initTabPg_p();

#endif

