//
// Created by gabriele on 31/12/18.
//

#ifndef E03_ST_H
#define E03_ST_H

#define MAX_LUNGH_STRINGA 30

typedef struct{
    char nome[MAX_LUNGH_STRINGA];
    char rete[MAX_LUNGH_STRINGA];
}Item;

typedef struct{
    Item* a;
    int maxN;
    int size;
}ST;

int aggiungiRete(ST* st,Item item);
int getIndiceByNome(ST st,char* nome);
char* getNomeByIndice(ST st,int indice);


#endif //E03_ST_H
