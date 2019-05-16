
#ifndef E03_PERSONAGGI_H
#define E03_PERSONAGGI_H

#define MAX_LUNGH_STR 50
#define MAX_LUNGH_CODICE 7

typedef struct pg_t* pg_p;
typedef struct stat_t* stat_p;
typedef struct tabEquip_t* tabEquip_p;

void stampaPersonaggio(pg_p personaggio);
stat_p getPgStat(pg_p pg);
tabEquip_p getEquipPG(pg_p pg);
char* getCodicePG(pg_p pg);
pg_p initPersonaggio();
void setEquipPG(pg_p pg, tabEquip_p equip);
void setPersonaggio(pg_p pg,char* codice, char* nome, char* classe, int hp, int mp,int atk,int def,int mag,int spr);

#endif
