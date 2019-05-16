//
// Created by gabriele on 07/12/18.
//

#ifndef E03_INVENTARIO_H

#define E03_INVENTARIO_H
#define FILE_INVENTARIO "inventario.txt"
#define MAX_LUNGH_STR 50


typedef struct{
    int hp;
    int mp;
    int atk;
    int def;
    int mag;
    int spr;
}stat_t;

typedef struct{
    char nome[MAX_LUNGH_STR];
    char tipo[MAX_LUNGH_STR];
    stat_t stat;
}inv_t;

typedef struct{
    inv_t* vettInv;//Vettore
    int nInv;
    int maxInv;
}tabInv_t;

void leggiFileInventario(tabInv_t *tabInv);
int trovaOggettoByNome(char nomeOggettoInput[], tabInv_t *tabInv );
void stampaInventario(inv_t inventario);
void deallocaInv(tabInv_t *tabInv);

#endif //E03_INVENTARIO_H
