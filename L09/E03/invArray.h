
#ifndef E03_INVENTARIO_ARRAY_H
#define E03_INVENTARIO_ARRAY_H

#define MAX_LUNGH_STR 50
#define MAX_LUNGH_CODICE 7
#define FILE_INVENTARIO "inventario.txt"

typedef struct tabInv_t* tabInv_p;
typedef struct inv_t* inv_p;

void leggiFileInventario(tabInv_p tabInv);
int trovaOggettoByNome(char nomeOggettoInput[], tabInv_p tabInv );
void deallocaInv(tabInv_p tabInv);
int getNInv(tabInv_p inventario);
void setNInv(tabInv_p inventario, int nInv);
inv_p getInvByIndice(tabInv_p inventario, int i);
tabInv_p initTabInv_p();
void initVettEquip(tabInv_p  tabInv);

#endif

