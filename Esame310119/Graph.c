//
// Created by gabriele on 31/01/19.
//

#include "Graph.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int v;
    int w;
}Edge;

static link NEW(int v, link next);
static void insertE(Graph G, Edge e);

Graph GRAPHInit(int V) {
    int v;
    Graph G = malloc(sizeof *G);
    G->V = V;
    G->E = 0;
    G->z = NEW(-1, NULL);
    G->lAdj = malloc(G->V*sizeof(link));
    for (v = 0; v < G->V; v++)
        G->lAdj[v] = G->z;
    G->tab = STInit(V);
    return G;
}

static link NEW(int v, link next) {
    link x = malloc(sizeof *x);
    x->v = v;
    x->next = next;
    return x;
}

static Edge EDGEcreate(int v, int w) {
    Edge e;
    e.v = v; e.w = w;
    return e;
}

void GRAPHinsertE(Graph G, int id1, int id2) {
    insertE(G, EDGEcreate(id1, id2));
}

static void insertE(Graph G, Edge e) {
    int v = e.v, w = e.w;
    G->lAdj[v] = NEW(w, G->lAdj[v]);
    G->E++;
}