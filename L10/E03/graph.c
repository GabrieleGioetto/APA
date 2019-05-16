//
// Created by gabriele on 31/12/18.
//

#include "graph.h"
#include "ST.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node* link;

struct node{
    Item* v;
    int wt;
    link next;
};

struct Graph_t{
    int V;
    int E;
    int** mAdj;
    link* lAdj;
    link z;
    ST tab;
};

//link newNode(int j, Item *a, int wt);
link NEW(Item* a,int wt, link next);

Graph initGrafo(char* nomeFile){
    Graph grafo = malloc(sizeof(struct Graph_t));

    FILE* fp = fopen(nomeFile, "r");

    if(fp == NULL){
        printf("Errore apertura file %s", nomeFile);
        exit(-1);
    }

    char riga[250];
    int nRighe = 0;
    while(fgets(riga,250,fp) != NULL){
        nRighe++;
    }

    int i;
    grafo->V = 0;
    grafo->E = 0;
    grafo->tab.maxN = nRighe * 2;
    grafo->tab.size = 0;
    grafo->tab.a = (Item*)malloc(sizeof(Item) * grafo->tab.maxN);
    grafo->mAdj = (int**)malloc(sizeof(int*) * grafo->tab.maxN);
    for (i = 0; i < grafo->tab.maxN; ++i) {
        grafo->mAdj[i] = (int*)malloc(sizeof(int) * grafo->tab.maxN);
    }

    return grafo;
}

void generaListaAdiacenza(Graph g){
    int i,j;
    link t,p;

    g->lAdj = (link*)malloc(sizeof(link) * g->V);
    g->z = NEW(NULL, 0, NULL);
    for (i = 0; i < g->V; i++)
        g->lAdj[i] = g->z;

    for (i = 0; i < g->V; ++i) {
        for (j = 0; j < g->V; ++j) {
            if(g->mAdj[i][j] > 0){
                g->lAdj[i] = NEW(&g->tab.a[j],g->mAdj[i][j], g->lAdj[i]);
            }
        }
    }
}

link NEW(Item *a,int wt, link next) {
    link x = malloc(sizeof *x);

    x->v = a;
    x->wt = wt;
    x->next = next;
    return x;
}

void verticiAdiacenti(Graph g){

    int nVerticiAdiacenti = 3;
    char nomiVertici[nVerticiAdiacenti][MAX_LUNGH_STRINGA];
    int i;
    for (i = 0; i < nVerticiAdiacenti; ++i) {
        printf("Inserire vertice n° %d: ", i + 1);
        scanf("%s", nomiVertici[i]);
    }

    int indiciReti[nVerticiAdiacenti];
    for (i = 0; i < nVerticiAdiacenti; ++i) {
        indiciReti[i] = getIndiceByNome(g->tab,nomiVertici[i]);
        if(indiciReti[i] < 0){
            printf("Vertice non esistente\n");
            return;
        }
    }


    printf("Vertici %sadiacenti", verticiAdiacentiMatrice(g, indiciReti, nVerticiAdiacenti, nomiVertici) == 1 ? " " : "non ");
    //printf("Vertici %sadiacenti", verticiAdiacentiLista(g, indiciReti, nVerticiAdiacenti, nomiVertici) == 1 ? " " : "non ");

}

int verticiAdiacentiMatrice(Graph g, int indiciReti[],int nVerticiAdiacenti, char nomiVertici[][30]) {
    int i;

    if(g->mAdj[indiciReti[0]][indiciReti[1]] == 0)
        return 0;
    if(g->mAdj[indiciReti[1]][indiciReti[2]] == 0)
        return 0;
    if(g->mAdj[indiciReti[2]][indiciReti[0]] == 0)
        return 0;

    return 1;
}

int verticiAdiacentiLista(Graph g,int indiciReti[],int nVerticiAdiacenti, char nomiVertici[][30]) {
    int i;
    link t;

    if(!controlloReteCollegata(g, indiciReti[0], 1, nomiVertici))
        return 0;
    if(!controlloReteCollegata(g, indiciReti[1], 2, nomiVertici))
        return 0;
    if(!controlloReteCollegata(g, indiciReti[2], 0, nomiVertici))
        return 0;

    return 1;
}

int controlloReteCollegata(Graph g, int indiceRete1, int indiceRete2, char nomiVertici[][30]) {
    link t;
    int controllo = 0;
    for (t = g->lAdj[indiceRete1];!controllo && t != g->z; t = t->next){
        if(!strcmp(t->v->nome,nomiVertici[indiceRete2]))
            controllo = 1;
    }
    if(!controllo)
        return 0;
    return 1;
}

void setGrafo(Graph grafo, char* nomeFile){

    FILE* fp = fopen(nomeFile, "r");

    if(fp == NULL){
        printf("Errore apertura file %s", nomeFile);
        exit(-1);
    }

    Item item1, item2;
    int peso;
    int indiceRete1;
    int indiceRete2;

    while(fscanf(fp,"%s %s %s %s %d",item1.nome, item1.rete, item2.nome, item2.rete, &peso) == 5){

        if((indiceRete1 = getIndiceByNome(grafo->tab,item1.nome)) == -1){//IF RETE NON PRESENTE NELLA ST
            indiceRete1 = aggiungiRete(&grafo->tab, item1);
            grafo->V++;
        }
        if((indiceRete2 = getIndiceByNome(grafo->tab,item2.nome)) == -1){//IF RETE NON PRESENTE NELLA ST
            indiceRete2 = aggiungiRete(&grafo->tab, item2);
            grafo->V++;

        }

        grafo->mAdj[indiceRete1][indiceRete2] = peso;
        grafo->mAdj[indiceRete2][indiceRete1] = peso;
        grafo->E++;
    }
}

void printSortedVertex(Graph g){

    int i,j;
    char** nomiReti = (char**)malloc(sizeof(char*) * g->V);
    for (i = 0; i < g->V; ++i) {
        nomiReti[i] =  (char*)malloc(sizeof(char)* MAX_LUNGH_STRINGA);
        strcpy(nomiReti[i],g->tab.a[i].nome);
    }

    MergeSort(nomiReti, g->V);

    int indice1, indice2;

    for (i = 0; i < g->V; ++i) {
        printf("%s\n", nomiReti[i]);
        indice1 = getIndiceByNome(g->tab,nomiReti[i]);
        for (j = 0; j < g->tab.size; ++j) {
            indice2 = getIndiceByNome(g->tab,nomiReti[j]);
            if(g->mAdj[indice1][indice2] > 0)
                printf("\t%s %s %d \n",nomiReti[i], nomiReti[j], g->mAdj[indice1][indice2]);
        }
    }
}

void MergeSort(char** A, int N) {
    int l = 0, r = N - 1;
    char** B = (char**) malloc(N * sizeof(char*));
    int i;
    for (i = 0; i < N; ++i) {
        B[i] = (char*)malloc(sizeof(char)* MAX_LUNGH_STRINGA);
    }

    MergeSortR(A, B, l, r);
}

void MergeSortR(char** A, char** *B, int l, int r) {
    int q = (l + r) / 2;
    if (r <= l)
        return;
    MergeSortR(A, B, l, q);
    MergeSortR(A, B, q + 1, r);
    Merge(A, B, l, q, r);
}

void Merge(char** A, char** B, int l, int q, int r) {
    int i, j, k;
    i = l;
    j = q + 1;
    for (k = l; k <= r; k++)
        if (i > q)
            strcpy(B[k], A[j++]);
        else if (j > r)
            strcpy(B[k], A[i++]);
        else if (strcmp(A[i], A[j]) <= 0)
            strcpy(B[k], A[i++]);
        else
            strcpy(B[k], A[j++]);
    for (k = l; k <= r; k++)
        strcpy(A[k], B[k]);
}

