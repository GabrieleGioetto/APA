//
// Created by gabriele on 16/01/19.
//

#ifndef E01_GRAPH_H
#define E01_GRAPH_H

typedef struct Graph_t* Graph;

Graph leggiGrafoDaFile(char* nomeFile);
void trovaDAG(Graph g);

#endif //E01_GRAPH_H
