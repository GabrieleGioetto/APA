#include <stdio.h>
#include <stdlib.h>

#define NOME_FILE "grafo.txt"

typedef struct{
    int vertice1;
    int vertice2;
}arco;

arco* leggiFile(int* N, int* E);
int powerset(int pos,int *val,int *sol,int k,int count, arco* archi);
int valutaSoluzioneParziale(int* sol, int* val, int k, arco* archi);
void stampaSoluzioneParziale(int* sol,int* val, int k);

int main() {

    //N: numero vertici
    //E: numero archi
    int N,E;

    arco* archi = leggiFile(&N,&E);

    int* val = (int*)malloc(N*sizeof(int));
    int* sol = (int*)malloc(N*sizeof(int));

    //Scrivo in val tutti i vertici
    int i;
    for (i = 0; i < N; ++i) {
        val[i] = i;
    }

    powerset(0,val,sol,4,0,archi);

    return 0;
}

arco* leggiFile(int* N, int* E){

    FILE* fp = fopen(NOME_FILE,"r");

    if(fp == NULL){
        printf("Errore lettura file %s", NOME_FILE);
        exit(-1);
    }

    fscanf(fp,"%d %d",N,E);

    arco* archi = (arco*)malloc(*E * sizeof(arco));

    //Leggo archi da file
    int i;
    for(i = 0; i < *E; i++)
        fscanf(fp,"%d %d",&archi[i].vertice1,&archi[i].vertice2);

    fclose(fp);

    return archi;
}

int powerset(int pos,int *val,int *sol,int k,int count, arco* archi) {
    if (pos >= k) {
        if(valutaSoluzioneParziale(sol, val, k, archi)) {
            stampaSoluzioneParziale(sol,val,k);
            return count + 1;//Nuova soluzione trovata
        }

        return count;//La soluzione parziale non è soluzione al problema
    }
    sol[pos] = 0;
    count = powerset(pos + 1, val, sol, k, count, archi);
    sol[pos] = 1;
    count = powerset(pos + 1, val, sol, k, count, archi);
    return count;
}

void stampaSoluzioneParziale(int* sol,int* val, int k){
    int j;

    //Stampa soluzione parziale
    printf("{ ");
    for (j = 0; j < k; j++)
        if (sol[j] != 0)
            printf("%d ", val[j]);
    printf("} \n");
}

int valutaSoluzioneParziale(int* sol, int* val, int k, arco* archi){
    int i,j,trovato = 0;

    /*
     * Scorro tutti gli archi per vedere se per ogni arco almeno uno dei
     * due vertici è presente nella soluzione parziale
     * Se in almeno un arco non è presente nemmeno uno dei vertici della soluzione
     * parziale, allora la soluzione è nulla
     */
    for (i = 0; i < k; ++i) {
        trovato = 0;
        for (j = 0; j < k && !trovato; ++j) {
            if(sol[j] != 0 && (val[j] == archi[i].vertice1 ||val[j] == archi[i].vertice2))
                trovato = 1;
        }

        if(!trovato)
            return 0;
    }

    return 1;
}