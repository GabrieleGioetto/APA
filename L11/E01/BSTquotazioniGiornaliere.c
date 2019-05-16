//
// Created by gabriele on 02/01/19.
//

#include "BSTquotazioniGiornaliere.h"
#include "quotazioneGiornaliera.h"
#include <stdio.h>
#include "data.h"
#include <stdlib.h>
#include <limits.h>

typedef struct bstNODE_t* link;

static link NEW(quotazione item, link l, link r);
static void aggiornaNodo(link x, quotazione q);
static link insertR(link h, quotazione x, link z);
static quotazione searchR(link h, data d, link z);
static void NODEshow(link x, int livello);
static void visitBSTTrovaMaxEMinTraDate(link h, link z, data d1, data d2, float* maxQuota, float* minQuota);
static void visitBSTTrovaMaxEMin(link h, link z,float* maxQuota, float* minQuota);
static link partR(link h, int r);
int trovaPercorsoMaggiore(link h, link z);
int trovaPercorsoMinore(link h, link z);

static int contaNodiSottoalbero(link t, link z);

struct bstNODE_t{
    quotazione q;
    link l;
    link r;
    int N;
};

struct bst_t{
    link root;
    link z;
};

bst BSTinit() {
    bst b;
    b = malloc(sizeof *b) ;
    b->root= ( b->z = NEW(quotazioneNULL(), NULL, NULL));

    return b;
}

void BSTnewNodo(quotazione item, bst b){
    b->root = insertR(b->root,item,b->z);
}

static link NEW(quotazione item, link l, link r) {
    link x = malloc(sizeof(struct bstNODE_t));
    x->q = item;
    x->l = l;
    x->r = r;
    x->N = 0;
    return x;
}

static quotazione searchR(link h, data d, link z) {
    if (h == z)
        return quotazioneNULL();
    if (dataCMP(d, h->q.data) == 0)
        return h->q;
    if (dataCMP(d, h->q.data) == -1)
        return searchR(h->l, d, z);
    else
        return searchR(h->r, d, z);
}

quotazione BSTsearch(bst bst, data d) {
    return searchR(bst->root, d, bst->z);
}

static link insertR(link h, quotazione x, link z) {
    if (h == z)
        return NEW(x, z, z);
    if (quotazioneCMP(x, h->q)==-1)
        h->l = insertR(h->l, x, z);
    else if(quotazioneCMP(x, h->q)== 1)
        h->r = insertR(h->r, x, z);
    else{//Data già presente
        aggiornaNodo(h,x);
    }
    return h;
}

static void treePrintR(link h, link z, int livello) {
    if (h == z)
        return;

    treePrintR(h->l, z, livello + 1);
    NODEshow(h, livello);
    treePrintR(h->r, z, livello + 1);
}

static void NODEshow(link x, int livello){
    printf("Livello: %d\n", livello);
    printf("Quotazione giornaliera data %d/%d/%d\n", x->q.data.anno, x->q.data.mese,x->q.data.giorno);
    printf("Quotazione: %.2f nValori: %d\n", x->q.quota, x->q.nValori);
}

void BSTvisit(bst bst) {
    if (bst->root == bst->z) return;
    treePrintR(bst->root, bst->z, 0);
}

static void aggiornaNodo(link x, quotazione q){
    x->q.nValori += q.nValori;
    x->q.sommaValori += q.quota;
    x->q.quota = x->q.sommaValori/(float)x->q.nValori;
}

void BSTtrovaMinimoEMassimoTraDate(bst b, data d1, data d2){
    float maxQuota = INT_MIN;
    float minQuota = INT_MAX;

    visitBSTTrovaMaxEMinTraDate(b->root, b->z, d1,d2, &maxQuota, &minQuota);

    printf("Massimo: %.2f\n", maxQuota);
    printf("Minimo: %.2f\n", minQuota);
}

static void visitBSTTrovaMaxEMinTraDate(link h, link z, data d1, data d2, float* maxQuota, float* minQuota){
    if(h == z)
        return;

    if(dataCMP(h->q.data,d1) >= 0 && dataCMP(h->q.data, d2) <= 0){
        if(h->q.quota > *maxQuota)
            *maxQuota = h->q.quota;
        if(h->q.quota < *minQuota)
            *minQuota = h->q.quota;
    }

    if(dataCMP(h->q.data,d1) > 0)//Taglio sottoalberi
        visitBSTTrovaMaxEMinTraDate(h->l,z,d1,d2,maxQuota,minQuota);
    if(dataCMP(h->q.data, d2) < 0)
        visitBSTTrovaMaxEMinTraDate(h->r,z,d1,d2,maxQuota,minQuota);

}

void BSTtrovaMinimoEMassimo(bst b){
    float maxQuota = INT_MIN;
    float minQuota = INT_MAX;

    visitBSTTrovaMaxEMin(b->root, b->z,&maxQuota, &minQuota);

    printf("Massimo: %.2f\n", maxQuota);
    printf("Minimo: %.2f\n", minQuota);
}

static void visitBSTTrovaMaxEMin(link h, link z,float* maxQuota, float* minQuota){
    if(h == z)
        return;

    if(h->q.quota > *maxQuota)
        *maxQuota = h->q.quota;
    if(h->q.quota < *minQuota)
        *minQuota = h->q.quota;

    visitBSTTrovaMaxEMin(h->l,z,maxQuota,minQuota);
    visitBSTTrovaMaxEMin(h->r,z,maxQuota,minQuota);

}

void BSTBilanciamento(bst b){
    BSTvisit(b);

    int s;
    printf("Inserisci soglia S: ");
    scanf("%d", &s);

    if(s > trovaPercorsoMaggiore(b->root,b->z)/trovaPercorsoMinore(b->root, b->z)){
        printf("Albero rispetta la soglia\n");
        return;
    }

    contaNodiSottoalbero(b->root, b->z);

    int mediana = b->root->N / 2;
    b->root = partR(b->root, mediana);

    printf("\n\n");
    BSTvisit(b);
}

int trovaPercorsoMaggiore(link h, link z){
    if(h == z)
        return 0;

    int l1 = trovaPercorsoMaggiore(h->l,z) + 1;
    int l2 = trovaPercorsoMaggiore(h->r,z) + 1;

    return l1 > l2 ? l1 : l2;
}

int trovaPercorsoMinore(link h, link z){
    if(h == z)
        return 0;

    int l1 = trovaPercorsoMinore(h->l,z) + 1;
    int l2 = trovaPercorsoMinore(h->r,z) + 1;

    return l1 < l2 ? l1 : l2;
}


link rotR(link h) {
    link x = h->l;
    h->l = x->r;
    x->r = h;
    x->N = h->N;
    h->N = h->r->N + h->l->N +1;
    return x;
}

link rotL(link h) {
    link x = h->r;
    h->r = x->l;
    x->l = h;
    x->N = h->N;
    h->N = h->l->N + h->r->N +1;
    return x;
}

int contaNodiSottoalbero(link t, link z) {
    if(t == z)
        return 0;

    t->N = contaNodiSottoalbero(t->l,z) + contaNodiSottoalbero(t->r,z) + 1;

    return t->N;
}

link partR(link h, int r) {
    int t = h->l->N;
    if (t > r) {
        h->l = partR(h->l, r);
        h = rotR(h);
    }
    if (t < r) {
        h->r = partR(h->r, r-t-1);
        h = rotL(h);
    }
    return h;
}

