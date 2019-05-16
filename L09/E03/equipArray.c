#include <stdio.h>
#include <stdlib.h>
#include "equipArray.h"
#include "inv.h"
#include "pg.h"



struct tabEquip_t{
    int inUso;
    inv_p* vettEq;//Vettore di puntatori a inv_t
};

int getEquipInUso(tabEquip_p equip){
    return equip->inUso;
}

inv_p* getVettEquip(tabEquip_p tabEquip){
    return tabEquip->vettEq;
}

void setEquipInUso(tabEquip_p equip, int inUso){
    equip->inUso = inUso;
}

inv_p getEquipByIndice(tabEquip_p  equip, int i){
    return equip->vettEq[i];
}

void setEquipByIndice(tabEquip_p  equip, inv_p oggetto ,int i){
    equip->vettEq[i] = oggetto;
}

tabEquip_p initTabEquip(){
    return malloc(sizeof(struct tabEquip_t));
}

void initVettEq(tabEquip_p equip, int nInv){
    equip->vettEq = malloc(sizeof(struct tabEquip_t) * nInv);
}