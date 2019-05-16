//
// Created by gabriele on 31/12/18.
//

#ifndef E03_GRAPH_H
#define E03_GRAPH_H

typedef struct Graph_t* Graph;

Graph initGrafo(char* nomeFile);
void setGrafo(Graph grafo, char* nomeFile);
void printSortedVertex(Graph g);
void MergeSort(char** A, int N);
void MergeSortR(char** A, char** *B, int l, int r);
void Merge(char** A, char** B, int l, int q, int r);
void verticiAdiacenti(Graph g);
void generaListaAdiacenza(Graph g);
int verticiAdiacentiMatrice(Graph g,int indiciReti[], int nVerticiAdiacenti,char nomiVertici[][30]);
int verticiAdiacentiLista(Graph g,int indiciReti[],int nVerticiAdiacenti, char nomiVertici[][30]);
int controlloReteCollegata(Graph g, int indiceRete1, int indiceRete2, char nomiVertici[][30]);

#endif //E03_GRAPH_H
