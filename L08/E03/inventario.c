//
// Created by gabriele on 07/12/18.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inventario.h"

void stampaInventario(inv_t inventario){

    printf("%s ", inventario.nome);
    printf("%s ", inventario.tipo);
    stampaStatistiche(inventario.stat);
}

void leggiFileInventario(tabInv_t *tabInv) {

    FILE* fp = fopen(FILE_INVENTARIO, "r");

    if(fp == NULL){
        printf("Errore apertura file %s" , FILE_INVENTARIO);
        exit(-1);
    }

    //LETTURA NUMERO OGGETTI E ALLOCAMENTO INVENTARIO
    fscanf(fp,"%d", &(tabInv->nInv));stampaIn

    tabInv->vettInv = (inv_t*)malloc(sizeof(inv_t) * tabInv->nInv);

    int i;
    for (i = 0; i < tabInv->nInv; ++i) {

        fscanf(fp,"%s", tabInv->vettInv[i].nome);
        fscanf(fp,"%s", tabInv->vettInv[i].tipo);
        fscanf(fp,"%d", &tabInv->vettInv[i].stat.hp);
        fscanf(fp,"%d", &tabInv->vettInv[i].stat.mp);
        fscanf(fp,"%d", &tabInv->vettInv[i].stat.atk);
        fscanf(fp,"%d", &tabInv->vettInv[i].stat.def);
        fscanf(fp,"%d", &tabInv->vettInv[i].stat.mag);
        fscanf(fp,"%d", &tabInv->vettInv[i].stat.spr);
    }

    fclose(fp);
}


int trovaOggettoByNome(char nomeOggettoInput[], tabInv_t *tabInv ){
    int i;
    for (i = 0; i < tabInv->nInv; ++i) {
        if(!strcmp(tabInv->vettInv[i].nome, nomeOggettoInput))
            return i;
    }
    return -1;
}

void deallocaInv(tabInv_t *tabInv) {
    free(tabInv->vettInv);
    free(tabInv);
}
