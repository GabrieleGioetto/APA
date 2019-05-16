//
// Created by gabriele on 16/01/19.
//

#include "graph.h"
#include "ST.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef struct node* link;

struct node{
    int v;
    int wt;
    link next;
};

typedef struct{
    int v;
    int w;
    int wt;
}Edge;


struct Graph_t{
    int V;
    int E;
    link* lAdj;
    link z;
    ST tab;
    Edge* edges;
};

static link NEW(int a,int wt, link next);
int dfsR(Graph G, Edge e, int *time, int *pre, int *post, int *st,int* archiDaConsiderare);
static Edge EDGEcreate(int v, int w, int wt);
int power_set(Graph G,int m,int pos,int *sol,int* solMax,int* pesoMax);
int GRAPHdfs(Graph G, int id, int* archiDaConsiderare);
void stampaArchi( Graph G, int* archiConsiderati);
int arcoDaConsiderare(int v, int w, Graph G, int *archiDaConsiderare);
void DAGrts(Graph G, int* archiConsiderati);

void stampaDistanzeMassimi(Graph G, int *archiConsiderati, int *ts);

Graph initGrafo(){

    Graph grafo = malloc(sizeof(struct Graph_t));

    grafo->V = 0;
    grafo->E = 0;
    grafo->z = NEW(-1,0, NULL);
    grafo->tab.size = 0;
    grafo->tab.a = (Item*)malloc(sizeof(Item) * grafo->V);

    return grafo;
}

static link NEW(int a,int wt, link next) {
    link x = malloc(sizeof *x);

    x->v = a;
    x->wt = wt;
    x->next = next;
    return x;
}



Graph leggiGrafoDaFile(char* nomeFile){

    Graph g = initGrafo();

    FILE* fp = fopen(nomeFile, "r");

    if(fp == NULL){
        printf("Errore apertura file %s", nomeFile);
        exit(-1);
    }

    fscanf(fp,"%d", &g->V);

    g->lAdj = (link*)malloc(sizeof(link) * g->V);
    int i;
    for (i = 0; i < g->V; ++i) {
        g->lAdj[i] = g->z;
    }

    g->tab.a = (Item*)malloc(sizeof(Item) * g->V);
    g->tab.size = g->V;

    //LEGGO VERTICI
    for (i = 0; i < g->V; ++i) {
        fscanf(fp, "%s", g->tab.a[i].nome);
    }

    char nome1[MAX_LUNGH_STRINGA];
    char nome2[MAX_LUNGH_STRINGA];
    int wt;
    int indice1, indice2;

    g->edges = (Edge*)malloc(sizeof(Edge) * g->V * 2);
    i = 0;

    //LEGGO ARCHI
    while(fscanf(fp, "%s %s %d", nome1, nome2, &wt) != EOF){
        indice1 = getIndiceByNome(g->tab, nome1);
        indice2 = getIndiceByNome(g->tab, nome2);

        if(indice1 == -1 || indice2 == -1){
            printf("Errore\n");
            exit(-1);
        }

        g->E++;
        g->lAdj[indice1] = NEW(indice2, wt, g->lAdj[indice1]);
        g->edges[i++] = EDGEcreate(indice1,indice2, wt);
    }

    g->edges = realloc(g->edges, g->E * sizeof(Edge));

    //DA mettere in un for che parte da E a 0 in una funzione propria

    return g;
}

void trovaDAG(Graph g){
    int i;
    int* sol= calloc(g->E,sizeof(int));
    int* solMax= calloc(g->E,sizeof(int));
    int pesoMax = 0;

    //STAMPO TUTTI GLI INSIEMI MASSIMI
    for (i = g->E; i > 0; --i) {
        if(power_set(g,i, 0, sol,solMax,&pesoMax))
            break;
    }

    //STAMPO SOLUZIONE CON ARCHI RIMOSSI DI PESO MASSIMO
    printf("Soluzione massima: \n");
    stampaArchi(g,solMax);


    //STAMPO DAG MASSIMO
    DAGrts(g, solMax);

}

void TSdfsR(Graph G, int v, int *ts, int *pre, int *time, int* archiDaConsiderare) {
    link t;
    pre[v] = 0;
    for (t = G->lAdj[v]; t != G->z; t = t->next) {
        if (pre[t->v] == -1 && arcoDaConsiderare(v, t->v, G, archiDaConsiderare))
            TSdfsR(G, t->v, ts, pre, time, archiDaConsiderare);
    }
    ts[(*time)++] = v;
}

void DAGrts(Graph G, int* archiConsiderati) {
    int v, time = 0, *pre, *ts;
    pre = malloc(G->V * sizeof(int));
    ts = malloc(G->V * sizeof(int));
    for (v = 0; v < G->V; v++) {
        pre[v] = -1;
        ts[v] = -1;
    }
    for (v = 0; v < G->V; v++)
        if (pre[v] == -1)
            TSdfsR(G, v, ts, pre, &time, archiConsiderati);

    //Inverti vettore
    int i, tmp;
    for (i = 0; i < G->V / 2; ++i) {
        tmp = ts[i];
        ts[i] = ts[G->V - 1 - i];
        ts[G->V - 1 - i] = tmp;
    }

    stampaDistanzeMassimi(G, archiConsiderati, ts);

}

void stampaDistanzeMassimi(Graph G, int *archiConsiderati, int *ts) {
    int* d = malloc(G->V * sizeof(int));
    int i;

    link t;
    int j;

    for (j = 0; j < G->V; ++j) {
        for (i = 0; i < G->V; ++i)
            d[i] = INT_MIN;
        d[ts[j]] = 0;

        for (i = j; i < G->V; ++i) {
            if (d[ts[i]] != INT_MIN) {
                for (t = G->lAdj[ts[i]]; t != G->z; t = t->next) {
                    if (d[t->v] < d[ts[i]] + t->wt && arcoDaConsiderare(ts[i], t->v, G, archiConsiderati)) {
                        d[t->v] = d[ts[i]] + t->wt;
                    }
                }
            }
        }

        printf("Start: %d \n", ts[j]);
        for (i = 0; i < G->V; ++i) {
            printf("%s %d ", getNomeByIndice(G->tab,i) ,d[i] == INT_MIN ? -1 : d[i]);
        }
        printf("\n");
    }
}


static Edge EDGEcreate(int v, int w, int wt) {
    Edge e;
    e.v = v; e.w = w; e.wt = wt;
    return e;
}

void stampaArchi( Graph G, int* archiConsiderati){
    int i;
    for (i = 0; i < G->E; i++)
        if (archiConsiderati[i] == 1)
            printf("%s %s %d\n", getNomeByIndice(G->tab,G->edges[i].v),getNomeByIndice(G->tab,G->edges[i].w),G->edges[i].wt);
    printf("\n\n");
}

int power_set(Graph G,int m,int pos,int *sol,int* solMax,int* pesoMax) {
    int i, count, peso = 0;
    if (pos >= G->E) {
        count = 0;
        for (i = 0; i < G->E; ++i)
            if (sol[i] == 1)
                count++;
            else
                peso += G->edges[i].wt;
        if(count == m){
            //Creato sottoinsieme corretto

            /*
            if(sol[5] == 0)
                printf("Sono qui");*/

            if(GRAPHdfs(G, 0, sol)) {

                printf("Numero archi soluzione: %d\n",m);
                printf("Numero archi rimossi: %d\n", G->E - m);
                printf("Archi rimossi: ");
                for (i = 0; i < G->E; ++i) {
                    if(sol[i] == 0)
                        printf("{%d %d} ", G->edges[i].v, G->edges[i].w);
                }
                printf("\n\n");

                //Stampa
                stampaArchi(G,sol);

                if(peso >= *pesoMax){
                    *pesoMax = peso;

                    //Salvo soluzione massima
                    for (i = 0; i < G->E; ++i)
                       solMax[i] = sol[i];
                }

                return 1;
            }
        }
        return 0;
    }

    int sol1, sol2;

    sol[pos] = 0;
    sol1 = power_set(G, m, pos + 1, sol, solMax, pesoMax);
    sol[pos] = 1;
    sol2 = power_set(G, m, pos + 1, sol, solMax, pesoMax);

    if(sol1 || sol2)//Se ho trovato una soluzione con questa lunghezza m in almeno uno dei due sottorami
        return 1;

    return 0;
}


int GRAPHdfs(Graph G, int id, int* archiDaConsiderare) {
    int v, time = 0, *pre, *post, *st, i;
    pre = malloc(G->V * sizeof(int));
    post = malloc(G->V * sizeof(int));
    st = malloc(G->V * sizeof(int));
    for (v = 0; v < G->V; v++) {
        pre[v] = -1;
        post[v] = -1;
        st[v] = -1;
    }

    int controllo = 0;

    if( dfsR(G, EDGEcreate(id, id, 0), &time, pre, post, st, archiDaConsiderare)){
        controllo = 1;

    }

    if(!controllo)
        return 0;

    for (v = 0; v < G->V; v++)
        if (pre[v] == -1)
            if(dfsR(G, EDGEcreate(v, v, 0), &time, pre, post, st, archiDaConsiderare)) {//è un dag
                controllo = 1;
            }
    return controllo;
}

int dfsR(Graph G, Edge e, int *time, int *pre, int *post, int *st, int* archiDaConsiderare){
    link t;

    //printf("%d %s\n",e.w, getNomeByIndice(G->tab,e.w));

    int i;
    for (i = 0; i < G->E; ++i) {
        //Non considero multigrafi

        //Se un arco non è da considerare esco dall'istanza
        if(e.v == G->edges[i].v && e.w == G->edges[i].w && archiDaConsiderare[i] == 0)
            return -1;
    }

    int v, w = e.w;
    st[e.w] = e.v;
    pre[w] = (*time)++;
    for (t = G->lAdj[w]; t != G->z; t = t->next) {
        if (pre[t->v] == -1) {
            if (!dfsR(G, EDGEcreate(w, t->v, t->wt), time, pre, post, st, archiDaConsiderare))
                return 0;
        }
        else if (arcoDaConsiderare(w,t->v,G,archiDaConsiderare)){
            v = t->v;
            if (post[v] == -1) {
                //ARCO BACK
                return 0;
            }
        }
    }
    post[w] = (*time)++;
    return 1;
}

int arcoDaConsiderare(int v, int w, Graph G, int *archiDaConsiderare) {
    int i;
    for (i = 0; i < G->E; ++i) {
        //Non considero multigrafi
        if (v == G->edges[i].v && w == G->edges[i].w && archiDaConsiderare[i] == 0)
            return 0;
    }

    return 1;
}

