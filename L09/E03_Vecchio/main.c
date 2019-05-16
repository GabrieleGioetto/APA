#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "personaggi.h"
#include "inventario.h"

typedef enum{
    c_aggiungiPG, c_eliminaPG, c_aggiungiOggetto, c_rimuoviOggetto, c_calcolaStatistiche, c_fine
}comando;

comando selezionaComando();
void selezionaDati(comando c, tabInv_t *tabInv, tabPg_t *tabPg);

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


void selezionaDati(comando c, tabInv_t *tabInv, tabPg_t *tabPg) {
    switch(c){
        case c_aggiungiPG:
            aggiungiPG(tabPg ,tabInv->nInv);
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


