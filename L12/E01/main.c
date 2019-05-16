#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

#define NOME_FILE "grafo4.txt"


int main() {

    Graph G = leggiGrafoDaFile(NOME_FILE);

    trovaDAG(G);



    return 0;
}