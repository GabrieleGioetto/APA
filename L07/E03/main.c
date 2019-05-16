#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LUNGH_STR 50
#define MAX_LUNGH_CODICE 7
#define FILE_PG "pg.txt"
#define FILE_INVENTARIO "inventario.txt"
#define MAX_OGGETTI_INVENTARIO 8

typedef struct{
    int hp;
    int mp;
    int atk;
    int def;
    int mag;
    int spr;
}stat_t;

typedef struct{
    char nome[MAX_LUNGH_STR];
    char tipo[MAX_LUNGH_STR];
    stat_t stat;
}inv_t;

typedef struct{
    inv_t* vettInv;//Vettore
    int nInv;
    int maxInv;
}tabInv_t;

typedef struct{
    int inUso;
    inv_t** vettEq;//Vettore di puntatori a inv_t
}tabEquip_t;

typedef struct{
   char codice[MAX_LUNGH_CODICE];
   char nome[MAX_LUNGH_STR];
   char classe[MAX_LUNGH_STR];
   tabEquip_t equip;
   stat_t stat;
}pg_t;

typedef struct nodo{
    pg_t pg;
    struct nodo* next;
}nodoPg_t, *link;

typedef struct {
    link headPg;
    link tailPg;
    int nPg;
}tabPg_t;

typedef enum{
    c_aggiungiPG, c_eliminaPG, c_aggiungiOggetto, c_rimuoviOggetto, c_calcolaStatistiche, c_fine
}comando;

void leggiFilePG(tabPg_t* tabPg, int nInv);
void stampaPersonaggio(pg_t personaggio);
void newNodePersonaggio(tabPg_t *tabPg, pg_t personaggio);
void leggiFileInventario(tabInv_t *tabInv);
comando selezionaComando();
void aggiungiPG(tabPg_t *tabPg);
void stampaListaPersonaggi(tabPg_t* tabPg);
void selezionaDati(comando c, tabInv_t *tabInv, tabPg_t *tabPg);
int trovaOggettoByNome(char nomeOggettoInput[], tabInv_t *tabInv );
link trovaPgByCodice(tabPg_t *tabPg);
void eliminaPG(tabPg_t *tabPg);
void stampaInventario(inv_t inventario);
void aggiungiOggettoAPersonaggio(tabPg_t *tabPg, tabInv_t *tabInv);
void rimuoviOggettoAPersonaggio(tabPg_t *tabPg);
void calcolaStatistichePersonaggio(tabPg_t *tabPg);
void stampaStatistiche(stat_t stat);
void controlloStatisticheMinoriDiZero(stat_t *stat);
void deallocaPG(tabPg_t *tabPg);
void deallocaInv(tabInv_t *tabInv);

int main() {

    //CARICO INVENTARIO
    tabInv_t* tabInv;
    tabInv = (tabInv_t*)malloc(sizeof(tabInv));
    leggiFileInventario(tabInv);

    //CARICO PERSONAGGI
    tabPg_t *tabPg;
    tabPg = (tabPg_t*)malloc(sizeof(tabPg_t));
    leggiFilePG(tabPg, tabInv->nInv);

    comando c = c_aggiungiPG;
    while(c != c_fine){
        c = selezionaComando();

        selezionaDati(c, tabInv, tabPg);
    }

    return 0;
}

void selezionaDati(comando c, tabInv_t *tabInv, tabPg_t *tabPg) {
    switch(c){
        case c_aggiungiPG:
            aggiungiPG(tabPg);
            break;
        case c_eliminaPG:
            eliminaPG(tabPg);
            stampaListaPersonaggi(tabPg);
            break;
        case c_aggiungiOggetto:
            aggiungiOggettoAPersonaggio(tabPg, tabInv);
            break;
        case c_rimuoviOggetto:
            rimuoviOggettoAPersonaggio(tabPg);
            break;
        case c_calcolaStatistiche:
            calcolaStatistichePersonaggio(tabPg);
            break;
        case c_fine:
            deallocaPG(tabPg);
            deallocaInv(tabInv);
            break;
    }
}

void deallocaInv(tabInv_t *tabInv) {
    free(tabInv->vettInv);
    free(tabInv);
}

void deallocaPG(tabPg_t *tabPg) {

    link t, p;
    if (tabPg->headPg == NULL)
        return;

    for (t = tabPg->headPg->next, p = tabPg->headPg; t != NULL; p = t, t = t->next) {
        free(p->pg.equip.vettEq);
        free(p);
    }
    free(tabPg);
}

void calcolaStatistichePersonaggio(tabPg_t *tabPg) {
    link Pg = trovaPgByCodice(tabPg);
    if(Pg == NULL){
        printf("PG non trovato\n");
        return;
    }

    stat_t stat_tmp = Pg->pg.stat;

    //SCORRO GLI OGGETTI NELL'INVENTARIO DEL PERSONAGGIO E CALCOLO STATISTICHE FINALI
    int i;
    for (i = 0; i < Pg->pg.equip.inUso; ++i) {
        stat_tmp.hp += Pg->pg.equip.vettEq[i]->stat.hp;
        stat_tmp.mp += Pg->pg.equip.vettEq[i]->stat.mp;
        stat_tmp.atk += Pg->pg.equip.vettEq[i]->stat.atk;
        stat_tmp.def += Pg->pg.equip.vettEq[i]->stat.def;
        stat_tmp.mag += Pg->pg.equip.vettEq[i]->stat.mag;
        stat_tmp.spr += Pg->pg.equip.vettEq[i]->stat.spr;
    }

    //SE LE STATISTICHE SONO MINORI DI UNO LE RENDO UGUALI A ZERO
    controlloStatisticheMinoriDiZero(&stat_tmp);

    stampaStatistiche(stat_tmp);

}

void controlloStatisticheMinoriDiZero(stat_t *stat) {
    if(stat->hp < 1)
        stat->hp  = 1;
    if(stat->mp  < 1)
        stat->mp  = 1;
    if(stat->atk < 1)
        stat->atk = 1;
    if(stat->def < 1)
        stat->def = 1;
    if(stat->mag < 1)
        stat->mag = 1;
    if(stat->spr < 1)
        stat->spr = 1;
}

void stampaStatistiche(stat_t stat) {
    printf("%d ", stat.hp);
    printf("%d ", stat.atk);
    printf("%d ", stat.def);
    printf("%d ", stat.mag);
    printf("%d ", stat.mp);
    printf("%d ", stat.spr);
    printf("\n");
}

void rimuoviOggettoAPersonaggio(tabPg_t *tabPg) {

    char nomeOggettoInput[MAX_LUNGH_STR];

    link Pg = trovaPgByCodice(tabPg);
    if(Pg == NULL){
        printf("PG non trovato\n");
        return;
    }

    printf("INVENTARIO DEL PERSONAGGIO: \n");

    int i;
    for (i = 0; i < Pg->pg.equip.inUso; ++i) {
        stampaInventario(*Pg->pg.equip.vettEq[i]);
    }

    printf("Inserire nome oggetto da rimuovere: ");
    scanf("%s", nomeOggettoInput);

    int j;
    for (i = 0; i < Pg->pg.equip.inUso; i++) {

        //Cerco l'oggetto
        if(!strcmp(Pg->pg.equip.vettEq[i]->nome,nomeOggettoInput )){
            //Se lo trovo, traslo tutto il vettore di uno all'indietro
            for (j = i; j < Pg->pg.equip.inUso - 1; ++j) {
                Pg->pg.equip.vettEq[j] = Pg->pg.equip.vettEq[j +1];
            }

            //Diminuisco numero di oggetti
            Pg->pg.equip.inUso--;

            printf("Oggetto rimosso\n");
            return;
        }
    }

    printf("Oggetto non trovato\n");

}

void aggiungiOggettoAPersonaggio(tabPg_t *tabPg, tabInv_t *tabInv) {
    char nomeOggettoInput[MAX_LUNGH_STR];

    //STAMPO TUTTI GLI OGGETTI PER AIUTARE L'UTENTE
    int i;
    for (i = 0; i < tabInv->nInv; ++i) {
        stampaInventario(tabInv->vettInv[i]);
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

    if(Pg->pg.equip.inUso == MAX_OGGETTI_INVENTARIO){
        printf("Il personaggio ha il numero massimo di oggetti!");
        return;
    }

    //AGGIUNGO INVENTARIO SCELTO AL VETTORE DI INVENTARI DEL PG
    Pg->pg.equip.vettEq[Pg->pg.equip.inUso++] = &tabInv->vettInv[indiceOggetto];

    printf("Oggetto %s aggiunto a personaggio %s", nomeOggettoInput, Pg->pg.codice);

}

link trovaPgByCodice(tabPg_t *tabPg){
    char codicePGInput[MAX_LUNGH_CODICE];

    printf("Inserire codice PG: ");
    scanf("%s", codicePGInput);

    if(tabPg->headPg == NULL)
        return NULL;
    link t;
    //CICLO PER TROVARE PG CON IL CODICE DATO IN INPUT
    for (t = tabPg->headPg; t != NULL;t = t->next) {
        if (!strcmp(t->pg.codice, codicePGInput)) {
            return t;
        }
    }

    return NULL;
}

int trovaOggettoByNome(char nomeOggettoInput[], tabInv_t *tabInv ){
    int i;
    for (i = 0; i < tabInv->nInv; ++i) {
        if(!strcmp(tabInv->vettInv[i].nome, nomeOggettoInput))
            return i;
    }
    return -1;
}

void eliminaPG(tabPg_t *tabPg) {
    char codiceInput[MAX_LUNGH_CODICE];
    printf("Inserire codice di personaggio che vuoi eliminare: ");
    scanf("%s", codiceInput);

    //CICLO PER TROVARE PG CON IL CODICE DATO IN INPUT
    link t, prec;
    for (t = tabPg->headPg, prec = NULL; t != NULL; prec = t, t = t->next) {
        if (!strcmp(t->pg.codice, codiceInput)) {

            //CANCELLAZIONE NODO
            prec->next = t->next;
            free(t);
            printf("Personaggio eliminato\n");
            return;
        }
    }

    printf("Personaggio non trovato\n");
}

void aggiungiPG(tabPg_t *tabPg){

    pg_t personaggio;
    printf("Inserire codice: ");
    scanf("%s", personaggio.codice);
    printf("Inserire nome: ");
    scanf("%s", personaggio.nome);
    printf("Inserire classe: ");
    scanf("%s", personaggio.classe);
    printf("Inserire hp: ");
    scanf("%d", &personaggio.stat.hp);
    printf("Inserire mp: ");
    scanf("%d", &personaggio.stat.mp);
    printf("Inserire atk: ");
    scanf("%d", &personaggio.stat.atk);
    printf("Inserire def: ");
    scanf("%d", &personaggio.stat.def);
    printf("Inserire mag: ");
    scanf("%d", &personaggio.stat.mag);
    printf("Inserire spr: ");
    scanf("%d", &personaggio.stat.spr);

    personaggio.equip.inUso = 0;//Inizializzo equipaggiamenti in uso a zero
    personaggio.equip.vettEq = (inv_t **) malloc(sizeof(inv_t *) * MAX_OGGETTI_INVENTARIO);
    newNodePersonaggio(tabPg, personaggio);
    tabPg->tailPg->next = NULL;

    printf("Personaggio aggiunto!\n");
}

comando selezionaComando(){
    char tabella[5][50]={"AggiungiPG","EliminaPG","AggiungiOggetto","RimuoviOggetto","CalcolaStatistiche"};

    char comandoScelto[50];
    printf("Scegli comando: ( AggiungiPG | EliminaPG | AggiungiOggetto | RimuoviOggetto | CalcolaStatistiche | Fine) : ");
    scanf("%s", comandoScelto);

    comando c = c_aggiungiPG;
    while(c < c_fine && strcmp(comandoScelto,tabella[c]))
        c++;

    return c;
}

void leggiFileInventario(tabInv_t *tabInv) {

    FILE* fp = fopen(FILE_INVENTARIO, "r");

    if(fp == NULL){
        printf("Errore apertura file %s" , FILE_INVENTARIO);
        exit(-1);
    }

    //LETTURA NUMERO OGGETTI E ALLOCAMENTO INVENTARIO
    fscanf(fp,"%d", &(tabInv->nInv));

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

void leggiFilePG(tabPg_t* tabPg, int nInv) {

    tabPg->headPg = NULL;
    tabPg->tailPg = NULL;
    tabPg->nPg = 0;

    FILE *fp = fopen(FILE_PG, "r");

    if (fp == NULL) {
        printf("Errore apertura file %s", FILE_PG);
        exit(-1);
    }

    pg_t personaggio_tmp;

    while (fscanf(fp, "%s %s %s %d %d %d %d %d %d", personaggio_tmp.codice, personaggio_tmp.nome,
                  personaggio_tmp.classe, &personaggio_tmp.stat.hp, &personaggio_tmp.stat.mp, &personaggio_tmp.stat.atk,
                  &personaggio_tmp.stat.def, &personaggio_tmp.stat.mag, &personaggio_tmp.stat.spr) != EOF) {

        personaggio_tmp.equip.inUso = 0;//Inizializzo equipaggiamenti in uso a zero
        personaggio_tmp.equip.vettEq = (inv_t **) malloc(sizeof(inv_t *) * nInv);
        newNodePersonaggio(tabPg, personaggio_tmp);
    }
    tabPg->tailPg->next = NULL;//Faccio puntare ultimo inserito a NULL

    stampaListaPersonaggi(tabPg);

    fclose(fp);
}

void stampaListaPersonaggi(tabPg_t* tabPg){
    link t;
    for(t = tabPg->headPg; t != NULL;t = t->next){
        stampaPersonaggio(t->pg);
    }
}

void stampaInventario(inv_t inventario){

    printf("%s ", inventario.nome);
    printf("%s ", inventario.tipo);
    stampaStatistiche(inventario.stat);
}


void stampaPersonaggio(pg_t personaggio){

    printf("%s ", personaggio.codice);
    printf("%s ", personaggio.nome);
    printf("%s ", personaggio.classe);
    stampaStatistiche(personaggio.stat);
}

void newNodePersonaggio(tabPg_t *tabPg, pg_t personaggio) {

    //INSERIMENTO PRIMO ELEMENTO
    if(tabPg->headPg == NULL){
        tabPg->headPg = (link)malloc(sizeof(nodoPg_t));
        tabPg->headPg->pg = personaggio;
        return;
    }
    //INSERIMENTO SECONDO ELEMENTO
    if(tabPg->tailPg == NULL){
        tabPg->tailPg = (link)malloc(sizeof(nodoPg_t));
        tabPg->tailPg->pg = personaggio;
        tabPg->headPg->next = tabPg->tailPg;
        return;
    }

    //CREO NUOVO ELEMENTO E AGGIORNO CODA
    tabPg->tailPg->next = (link)malloc(sizeof(nodoPg_t));
    tabPg->tailPg->next->pg = personaggio;
    tabPg->tailPg = tabPg->tailPg->next;

};
