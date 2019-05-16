//
// Created by gabriele on 31/01/19.
//

#ifndef ESAME310119_GRAPH_H
#define ESAME310119_GRAPH_H

#include "ST.h"

typedef struct node* link;

struct node{
    int v;
    link next;
};

typedef struct Graph_t* Graph;

struct Graph_t{
    int V;
    int E;
    link* lAdj;
    link z;
    ST tab;
};


Graph GRAPHInit(int V);
void GRAPHinsertE(Graph G, int id1, int id2);

#endif //ESAME310119_GRAPH_H
