
#ifndef E03_INVENTARIO_H
#define E03_INVENTARIO_H

#define MAX_LUNGH_STR 50
#define MAX_LUNGH_CODICE 7

typedef struct inv_t* inv_p;
typedef struct stat_t* stat_p;

char* getNomeOggetto(inv_p inv);
char* getTipoOggetto(inv_p inv);
stat_p getStatOggetto(inv_p inv);
void setNomeOggetto(inv_p inv, char* nome);
void setTipoOggetto(inv_p inv, char* tipo);
void setOggetto(inv_p inv, char* nome, char* tipo, int hp, int mp,int atk,int def,int mag,int spr);
void stampaOggetto(inv_p inventario);
inv_p initInv_p();

#endif
