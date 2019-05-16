#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pgList.h"
#include "inv.h"
#include "pg.h"
#include "stat.h"
#include "equipArray.h"
#include "invArray.h"

#define MAX_OGGETTI_INVENTARIO 8

typedef struct nodo* link;

struct nodo {
    pg_p pg;
    link next;
};

struct tabPg_t {
    link headPg;
    link tailPg;
    int nPg;
};

tabPg_p initTabPg_p(){
    return malloc(sizeof(struct tabPg_t));
}

void deallocaPG(tabPg_p tabPg) {

    link t, p;
    if (tabPg->headPg == NULL)
        return;

    for (t = tabPg->headPg->next, p = tabPg->headPg; t != NULL; p = t, t = t->next) {
        free(getVettEquip(getEquipPG(p->pg)));
        free(p);
    }
    free(tabPg);
}

void calcolaStatistichePersonaggio(tabPg_p tabPg) {
    link Pg = trovaPgByCodice(tabPg);
    if(Pg == NULL){
        printf("PG non trovato\n");
        return;
    }

    stat_p stat_tmp = getPgStat(Pg->pg);

    //SCORRO GLI OGGETTI NELL'INVENTARIO DEL PERSONAGGIO E CALCOLO STATISTICHE FINALI
    int i;
    for (i = 0; i < getEquipInUso(getEquipPG(Pg->pg)); ++i) {
        setHP(stat_tmp, getHP(getPgStat(Pg->pg)) + getHP(getStatOggetto(getEquipByIndice(getEquipPG(Pg->pg),i))));
        setMP(stat_tmp, getMP(getPgStat(Pg->pg)) + getMP(getStatOggetto(getEquipByIndice(getEquipPG(Pg->pg),i))));
        setATK(stat_tmp, getATK(getPgStat(Pg->pg)) + getATK(getStatOggetto(getEquipByIndice(getEquipPG(Pg->pg),i))));
        setDEF(stat_tmp, getDEF(getPgStat(Pg->pg)) + getDEF(getStatOggetto(getEquipByIndice(getEquipPG(Pg->pg),i))));
        setMAG(stat_tmp, getMAG(getPgStat(Pg->pg)) + getMAG(getStatOggetto(getEquipByIndice(getEquipPG(Pg->pg),i))));
        setSPR(stat_tmp, getSPR(getPgStat(Pg->pg)) + getSPR(getStatOggetto(getEquipByIndice(getEquipPG(Pg->pg),i))));

    }

    //SE LE STATISTICHE SONO MINORI DI UNO LE RENDO UGUALI A ZERO
    controlloStatisticheMinoriDiZero(stat_tmp);

    stampaStatistiche(stat_tmp);

}

void rimuoviOggettoAPersonaggio(tabPg_p tabPg) {

    char nomeOggettoInput[MAX_LUNGH_STR];

    link Pg = trovaPgByCodice(tabPg);
    if(Pg == NULL){
        printf("PG non trovato\n");
        return;
    }

    printf("INVENTARIO DEL PERSONAGGIO: \n");

    int i;
    for (i = 0; i < getEquipInUso(getEquipPG(Pg->pg)); ++i) {
        //stampaOggetto(*Pg->pg.equip.vettEq[i]);//DA QUI
        stampaOggetto(getEquipByIndice(getEquipPG(Pg->pg),i));//DA QUI
    }

    printf("Inserire nome oggetto da rimuovere: ");
    scanf("%s", nomeOggettoInput);

    int j;
    int equipInUso = getEquipInUso(getEquipPG(Pg->pg));

    for (i = 0; i < equipInUso; i++) {

        //Cerco l'oggetto
        if(!strcmp(getNomeOggetto(getEquipByIndice(getEquipPG(Pg->pg),i)),nomeOggettoInput )){
            //Se lo trovo, traslo tutto il vettore di uno all'indietro
            for (j = i; j < equipInUso - 1; ++j) {
                //Pg->pg.equip.vettEq[j] = Pg->pg.equip.vettEq[j +1];
                setEquipByIndice(getEquipPG(Pg->pg),getEquipByIndice(getEquipPG(Pg->pg),j+1),j);
            }

            //Diminuisco numero di oggetti
            setEquipInUso(getEquipPG(Pg->pg),equipInUso - 1);

            printf("Oggetto rimosso\n");
            return;
        }
    }

    printf("Oggetto non trovato\n");

}

void aggiungiOggettoAPersonaggio(tabPg_p tabPg, tabInv_p tabInv) {
    char nomeOggettoInput[MAX_LUNGH_STR];

    //STAMPO TUTTI GLI OGGETTI PER AIUTARE L'UTENTE
    int i;
    for (i = 0; i < getNInv(tabInv); ++i) {
        //stampaOggetto(tabInv->vettInv[i]);
        stampaOggetto(getInvByIndice(tabInv,i));
    }

    printf("Inserire nome oggetto da aggiungere a un personaggio: ");
    scanf("%s", nomeOggettoInput);

    int indiceOggetto = trovaOggettoByNome(nomeOggettoInput, tabInv);
    if(indiceOggetto == -1){
        printf("Oggetto non trovato\n");
        return;
    }

    link Pg = trovaPgByCodice(tabPg);
    if(Pg == NULL){
        printf("PG non trovato\n");
        return;
    }

    if(getEquipInUso(getEquipPG(Pg->pg)) == MAX_OGGETTI_INVENTARIO){
        printf("Il personaggio ha lo zaino pieno!");
        return;
    }

    //AGGIUNGO INVENTARIO SCELTO AL VETTORE DI INVENTARI DEL PG
    setEquipByIndice(getEquipPG(Pg->pg), getInvByIndice(tabInv,indiceOggetto), getEquipInUso(getEquipPG(Pg->pg)));
    setEquipInUso(getEquipPG(Pg->pg),getEquipInUso(getEquipPG(Pg->pg)) + 1);


    printf("Oggetto %s aggiunto a personaggio %s \n", nomeOggettoInput, getCodicePG(Pg->pg));

}

link trovaPgByCodice(tabPg_p tabPg){
    char codicePGInput[MAX_LUNGH_CODICE];

    printf("Inserire codice PG: ");
    scanf("%s", codicePGInput);

    if(tabPg->headPg == NULL)
        return NULL;
    link t;
    //CICLO PER TROVARE PG CON IL CODICE DATO IN INPUT
    for (t = tabPg->headPg; t != NULL;t = t->next) {
        if (!strcmp(getCodicePG(t->pg), codicePGInput)) {
            return t;
        }
    }

    return NULL;
}

void eliminaPG(tabPg_p tabPg) {
    char codiceInput[MAX_LUNGH_CODICE];
    printf("Inserire codice di personaggio che vuoi eliminare: ");
    scanf("%s", codiceInput);

    //CICLO PER TROVARE PG CON IL CODICE DATO IN INPUT
    link t, prec;
    for (t = tabPg->headPg, prec = NULL; t != NULL; prec = t, t = t->next) {
        if (!strcmp(getCodicePG(t->pg), codiceInput)) {

            //CANCELLAZIONE NODO
            prec->next = t->next;
            free(t);
            printf("Personaggio eliminato\n");
            return;
        }
    }

    printf("Personaggio non trovato\n");
}

void aggiungiPG(tabPg_p tabPg){

    char codice[MAX_LUNGH_CODICE], nome[MAX_LUNGH_STR],classe[MAX_LUNGH_STR];
    int hp, mp, atk, def, mag, spr ,i;

    printf("Inserire codice: ");
    scanf("%s", codice);
    printf("Inserire nome: ");
    scanf("%s", nome);
    printf("Inserire classe: ");
    scanf("%s", classe);
    printf("Inserire hp: ");
    scanf("%d", &hp);
    printf("Inserire mp: ");
    scanf("%d", &mp);
    printf("Inserire atk: ");
    scanf("%d", &atk);
    printf("Inserire def: ");
    scanf("%d", &def);
    printf("Inserire mag: ");
    scanf("%d", &mag);
    printf("Inserire spr: ");
    scanf("%d", &spr);

    pg_p personaggio = initPersonaggio();

    setPersonaggio(personaggio,codice,nome,classe,hp,mp,atk,def,mag,spr);

    setEquipPG(personaggio,initTabEquip());
    setEquipInUso(getEquipPG(personaggio),0);

    initVettEq(getEquipPG(personaggio),MAX_OGGETTI_INVENTARIO);
    //personaggio.equip.vettEq = (inv_t **) malloc(sizeof(inv_t *) * nInv);
    newNodePersonaggio(tabPg, personaggio);
    tabPg->tailPg->next = NULL;

    printf("Personaggio aggiunto!\n");
}


void leggiFilePG(tabPg_p tabPg) {

    tabPg->headPg = NULL;
    tabPg->tailPg = NULL;
    tabPg->nPg = 0;

    FILE *fp = fopen(FILE_PG, "r");

    if (fp == NULL) {
        printf("Errore apertura file %s", FILE_PG);
        exit(-1);
    }

    pg_p personaggio_tmp;
    char codice[MAX_LUNGH_CODICE], nome[MAX_LUNGH_STR],classe[MAX_LUNGH_STR];
    int hp, mp, atk, def, mag, spr ,i;

    while (fscanf(fp, "%s %s %s %d %d %d %d %d %d", codice, nome, classe, &hp, &mp, &atk, &def, &mag, &spr) != EOF) {

        setPersonaggio(personaggio_tmp,codice,nome,classe,hp,mp,atk,def,mag,spr);

        setEquipPG(personaggio_tmp,initTabEquip());
        setEquipInUso(getEquipPG(personaggio_tmp),0);

        initVettEq(getEquipPG(personaggio_tmp),MAX_OGGETTI_INVENTARIO);

        newNodePersonaggio(tabPg, personaggio_tmp);
    }
    tabPg->tailPg->next = NULL;//Faccio puntare ultimo inserito a NULL

    stampaListaPersonaggi(tabPg);
    //printf("%s\n\n\n",tabPg->headPg->pg.classe);

    fclose(fp);
}

void stampaListaPersonaggi(tabPg_p tabPg){
    link t;
    for(t = tabPg->headPg; t != NULL;t = t->next){
        stampaPersonaggio(t->pg);
    }
}


void newNodePersonaggio(tabPg_p tabPg, pg_p personaggio) {

    //INSERIMENTO PRIMO ELEMENTO
    if(tabPg->headPg == NULL){
        tabPg->headPg = (link)malloc(sizeof(struct nodo));
        tabPg->headPg->pg = personaggio;
        return;
    }
    //INSERIMENTO SECONDO ELEMENTO
    if(tabPg->tailPg == NULL){
        tabPg->tailPg = (link)malloc(sizeof(struct nodo));
        tabPg->tailPg->pg = personaggio;
        tabPg->headPg->next = tabPg->tailPg;
        return;
    }

    //CREO NUOVO ELEMENTO E AGGIORNO CODA
    tabPg->tailPg->next = (link)malloc(sizeof(struct nodo));
    tabPg->tailPg->next->pg = personaggio;
    tabPg->tailPg = tabPg->tailPg->next;

};
