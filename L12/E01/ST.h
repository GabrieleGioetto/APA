//
// Created by gabriele on 19/01/19.
//

#ifndef E01_ST_H
#define E01_ST_H

#define MAX_LUNGH_STRINGA 30

typedef struct{
    char nome[MAX_LUNGH_STRINGA];
}Item;

typedef struct{
    Item* a;
    int maxN;
    int size;
}ST;

int getIndiceByNome(ST st,char* nome);
char* getNomeByIndice(ST st,int indice);
Item ITEMSetNULL();


#endif //E01_ST_H
