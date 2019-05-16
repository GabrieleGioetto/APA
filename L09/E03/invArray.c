#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inv.h"
#include "invArray.h"
#include "stat.h"

struct tabInv_t{
    inv_p* vettInv;//Vettore
    int nInv;
    int maxInv;
};

int getNInv(tabInv_p inventario){
    return inventario->nInv;
}

tabInv_p initTabInv_p(){
    return malloc(sizeof(struct tabInv_t));
}

void initVettEquip(tabInv_p  tabInv){
    tabInv->vettInv = (inv_p*)malloc(sizeof(inv_p) * tabInv->nInv);

    int j;
    for (j = 0; j < tabInv->nInv; ++j) {
        tabInv->vettInv[j] = initInv_p();
    }
}

void setNInv(tabInv_p inventario, int nInv){
    inventario->nInv = nInv;
}

inv_p getInvByIndice(tabInv_p inventario, int i){
    return inventario->vettInv[i];
}

void leggiFileInventario(tabInv_p tabInv) {

    FILE* fp = fopen(FILE_INVENTARIO, "r");

    if(fp == NULL){
        printf("Errore apertura file %s" , FILE_INVENTARIO);
        exit(-1);
    }

    //LETTURA NUMERO OGGETTI E ALLOCAMENTO INVENTARIO
    int nInv;
    fscanf(fp,"%d", &nInv);
    setNInv(tabInv,nInv);

    initVettEquip(tabInv);

    char nome[MAX_LUNGH_STR], tipo[MAX_LUNGH_STR];
    int hp, mp, atk, def, mag, spr ,i;

    for (i = 0; i < tabInv->nInv; ++i) {

        fscanf(fp,"%s",nome);
        fscanf(fp,"%s", tipo);
        fscanf(fp,"%d", &hp);
        fscanf(fp,"%d", &mp);
        fscanf(fp,"%d", &atk);
        fscanf(fp,"%d", &def);
        fscanf(fp,"%d", &mag);
        fscanf(fp,"%d", &spr);

        setOggetto(tabInv->vettInv[i], nome, tipo, hp, mp, atk, def, mag, spr);

    }

    fclose(fp);
}


int trovaOggettoByNome(char nomeOggettoInput[], tabInv_p tabInv ){
    int i;
    for (i = 0; i < tabInv->nInv; ++i) {
        if(!strcmp(getNomeOggetto(tabInv->vettInv[i]), nomeOggettoInput))
            return i;
    }
    return -1;
}

void deallocaInv(tabInv_p tabInv) {
    free(tabInv->vettInv);
    free(tabInv);
}