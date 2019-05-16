//
// Created by gabriele on 02/01/19.
//

#include "ListTitoli.h"
#include "titolo.h"
#include "data.h"
#include "BSTquotazioniGiornaliere.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NOME_FILE "F3.txt"
typedef struct TitoloNode* link;

static link sortListIns(titolo pTitolo, link head);
static link NewTitolo(titolo pTitolo, link next);
static titolo getTitoloByNome(listTitoli lista);

struct TitoloNode{
    titolo t;
    link next;
};

struct tabTitoli_t{
    link head;
    int nTitoli;
};

static link NewTitolo(titolo t, link head);

listTitoli leggiFile(){

    FILE* fp = fopen(NOME_FILE, "r");
    if(fp == NULL){
        printf("Errore apertura %s", NOME_FILE);
        exit(-1);
    }

    listTitoli listaTitoli = malloc(sizeof *listaTitoli);
    listaTitoli->head = NULL;
    listaTitoli->nTitoli = 0;

    //fscanf(fp, "%d", &listaTitoli->nTitoli);

    titolo t;

    char codice[MAX_LUNGH_TITOLO];
    int nTransazioni;
    data d;
    float valore;
    int numero, minuti, ora;
    quotazione q;

    int j;
    while(fscanf(fp,"%s %d", codice, &nTransazioni) == 2){

        listaTitoli->nTitoli++;

        bst b = BSTinit();

        for (j = 0; j < nTransazioni; ++j) {
            fscanf(fp, "%d/%d/%d %d:%d %f %d",&d.anno,&d.mese, &d.giorno, &ora, &minuti, &valore, &numero);

            //Gestito internamente a funzione newQuotazione() se un nodo con la stessa data è già presente(Aggiorna)
            q = newQuotazione(valore * numero, numero, valore * numero, d);
            BSTnewNodo(q,b);
        }

        t = setTitolo(codice, nTransazioni, b);

        //BSTvisit(b);
        //printf("\n\n");

        listaTitoli->head = sortListIns(t,listaTitoli->head);

    }

    return listaTitoli;
}

float ricercaQuotazioneByData(listTitoli lista){

    titolo t = getTitoloByNome(lista);

    if(t == NULL){
        printf("Titolo non trovato");
        return -1;
    }

    data d;
    printf("Inserire anno: ");
    scanf("%d",&d.anno);
    printf("Inserire mese: ");
    scanf("%d",&d.mese);
    printf("Inserire giorno: ");
    scanf("%d",&d.giorno);


    bst b = getBSTTitolo(t);
    quotazione q = BSTsearch(b,d);

    return q.quota;
}

void bilanciaBstTitolo(listTitoli lista) {
    titolo t = getTitoloByNome(lista);

    if (t == NULL) {
        printf("Titolo non trovato");
        return;
    }

    bst b = getBSTTitolo(t);

    BSTBilanciamento(b);
}

void ricercaQuotazioneMinimaEMassimaTraDate(listTitoli lista){

    titolo t = getTitoloByNome(lista);

    if(t == NULL){
        printf("Titolo non trovato");
        return;
    }

    data d1, d2;
    printf("Inserire anno: ");
    scanf("%d",&d1.anno);
    printf("Inserire mese: ");
    scanf("%d",&d1.mese);
    printf("Inserire giorno: ");
    scanf("%d",&d1.giorno);
    printf("Inserire anno: ");
    scanf("%d",&d2.anno);
    printf("Inserire mese: ");
    scanf("%d",&d2.mese);
    printf("Inserire giorno: ");
    scanf("%d",&d2.giorno);

    bst b = getBSTTitolo(t);

    BSTtrovaMinimoEMassimoTraDate(b,d1,d2);
}

void ricercaQuotazioneMinimaEMassima(listTitoli lista){

    titolo t = getTitoloByNome(lista);

    if(t == NULL){
        printf("Titolo non trovato");
        return;
    }


    bst b = getBSTTitolo(t);

    BSTtrovaMinimoEMassimo(b);
}


static titolo getTitoloByNome(listTitoli lista){
    char nomeTitolo[MAX_LUNGH_TITOLO];
    printf("Inserisci nome titolo: ");
    scanf("%s", nomeTitolo);

    link l;
    if(lista == NULL)
        return NULL;

    for (l = lista->head; l != NULL && strcmp(getCodice(l->t), nomeTitolo) <= 0; l = l->next) {
        if(!strcmp(getCodice(l->t), nomeTitolo))
            return l->t;
    }

    return NULL;
}

static link sortListIns(titolo pTitolo, link head){
    if(head == NULL || strcmp(getCodice(head->t),getCodice(pTitolo)) > 0){
        return NewTitolo(pTitolo,head);
    }
    else{
        link l,p;
        for(l = head, p = NULL; l != NULL && strcmp(getCodice(l->t), getCodice(pTitolo)) < 0 ; p = l, l=l->next);
        p->next = NewTitolo(pTitolo, l);
    }
    return head;

}

static link NewTitolo(titolo pTitolo, link next) {

    link x = malloc(sizeof *x);
    x->t = pTitolo;
    x->next = next;

    return x;
}
