#ifndef E03_EQUIP_ARRAY_H
#define E03_EQUIP_ARRAY_H

#define MAX_LUNGH_STR 50
#define MAX_LUNGH_CODICE 7

typedef struct tabEquip_t* tabEquip_p;
typedef struct inv_t* inv_p;

int getEquipInUso(tabEquip_p equip);
inv_p getEquipByIndice(tabEquip_p  equip, int i);
void setEquipInUso(tabEquip_p equip, int inUso);
void setEquipByIndice(tabEquip_p  equip, inv_p oggetto ,int i);
tabEquip_p initTabEquip();
void initVettEq(tabEquip_p equip, int nInv);
inv_p* getVettEquip(tabEquip_p tabEquip);

#endif
