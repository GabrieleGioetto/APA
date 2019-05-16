#include <stdio.h>
#include "graph.h"

int main() {
    Graph  g = initGrafo("grafo.txt");
    setGrafo(g,"grafo.txt");

    printSortedVertex(g);


    generaListaAdiacenza(g);
    verticiAdiacenti(g);

    return 0;
}