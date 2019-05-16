#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#include "ST.h"

Graph leggiFile(char* file1);
int verificaKernel(Graph G,int* sol);
void identificaKernelMin(Graph G, int* sol, int pos, int n, int* solMin, int* cMin);
void memorizzaKernelMinSuFile(Graph G, int* sol, char* file);
int contaCardinalita(int* sol, int n);
void copiaSolMin(int* sol, int* solMin, int n);
void azzeraVisited(int* v, int n);
void lunghezzaCamSemp(int* sol, int* lunghMax,int* verticiKernelMax, Graph G, int* visited, int v, int countKernel, int countCammino);
int* getKernel(char* file, Graph G);

int main(int argc, char** argv) {

    Graph G = leggiFile(argv[1]);

    int* sol = getKernel(argv[2], G);

    if(verificaKernel(G,sol))
        printf("Insieme letto da file è un kernel");
    else
        printf("Insieme letto da file non è un kernel");

    int cMin = G->V;
    sol = calloc(sizeof(int), G->V);
    int* solMin = calloc(sizeof(int), G->V);

    identificaKernelMin(G,sol,0,G->V, solMin,&cMin);

    memorizzaKernelMinSuFile(G,solMin, argv[3]);

    int lunghMax = 0;
    int verticiKernelMax = 0;
    int* visited =  calloc(sizeof(int), G->V);
    int i = 0;
    for (i = 0; i < G->V; ++i) {
        azzeraVisited(visited, G->V);

        lunghezzaCamSemp(solMin, &lunghMax, &verticiKernelMax,G, visited, i, 0, 1);
    }

    printf("Lunghezza cammino semplice max: %d", lunghMax);


    return 1;
}

int* getKernel(char* file, Graph G){
    FILE* fp = fopen(file, "r");

    int* sol = calloc(sizeof(int), G->V);
    char str[20];
    int n;
    while(fscanf(fp,"%s",str) == 1){
        n = STsearch(G->tab, str);
        if(n != -1)
            sol[n] = 1;
    }

    return sol;
}

void lunghezzaCamSemp(int* sol, int* lunghMax, int* verticiKernelMax, Graph G, int* visited, int v, int countKernel, int countCammino){//MODI
    if(sol[v] == 1)
        countKernel++;

    if(countKernel > *verticiKernelMax){
        *verticiKernelMax = countKernel;
        *lunghMax = countCammino;
    }

    visited[v] = 1;

    link t;
    for (t = G->lAdj[v]; t != G->z; t = t->next) {
        if(visited[t->v] == 0)
            lunghezzaCamSemp(sol, lunghMax, verticiKernelMax, G, visited, t->v, countKernel, countCammino + 1);
    }

    visited[v] = 0;
}

void azzeraVisited(int* v, int n){
    int i;
    for (i = 0; i < n; ++i) {
        v[i] = 0;
    }

}
void copiaSolMin(int* sol, int* solMin, int n){
    int i;
    for (i = 0; i < n; ++i) {
        solMin[i] = sol[i];
    }
}

int contaCardinalita(int* sol, int n){
    int i, cont = 0;

    for (i = 0; i < n; ++i) {
        if(sol[i] == 1)
            cont++;
    }

    return cont;
}

void memorizzaKernelMinSuFile(Graph G, int* sol, char* file){
    FILE* fp = fopen(file, "r");

    int i;
    for (i = 0; i < G->V; ++i)
        if(sol[i] == 1){
            printf("%s, ", G->tab->a[i]);
            fprintf(fp, "%s, ", G->tab->a[i]);
        }
}

void identificaKernelMin(Graph G, int* sol, int pos, int n, int* solMin, int* cMin){
    if(pos >= n){
        if(verificaKernel(G,sol)){
            if(contaCardinalita(sol, G->V) < *cMin){
                *cMin = contaCardinalita(sol, G->V);
                copiaSolMin(sol, solMin, G->V);
            }
        }
        return;
    }

    sol[pos] = 0;
    identificaKernelMin(G,sol,pos + 1,n, solMin,cMin);
    sol[pos] = 1;
    identificaKernelMin(G,sol,pos + 1,n, solMin,cMin);
}

int verificaKernel(Graph G,int* sol){
    int i;
    link t;

    for (i = 0; i < G->V; ++i) {
        if(sol[i] == 1){
            for(t = G->lAdj[i]; t != G->z; t = t->next)
                if(sol[t->v] == 1)
                    return 0;
        }
    }

    int* verticiAdiacenti = calloc(sizeof(int), G->V);

    for (i = 0; i < G->V; ++i) {
        if(sol[i] == 1){
            verticiAdiacenti[i] = 1;

            for(t = G->lAdj[i]; t != G->z; t = t->next)
                verticiAdiacenti[t->v] = 1;

        }
    }

    for (i = 0; i < G->V; ++i) {
        if(verticiAdiacenti[i] == 0)
            return 0;
    }

    return 1;

}


Graph leggiFile(char* file1){
    FILE* fp = fopen(file1, "r");

    char str[256];

    int n = 0;

    while(fgets(str, 256, fp) != NULL)
        n++;

    Graph G = GRAPHInit(n * 2);

    ST s = STInit(n * 2);

    fclose(fp);

    fp = fopen(file1, "r");

    char s1[20], s2[20];
    int n1, n2;

    G->V = 0;

    while( fscanf(fp, "%s %s", s1, s2) == 2){
        if( (n1 = STsearch(s,s1)) == -1){
            n1 = STinsert(s, s1);
            G->V++;
        }
        if( (n2 = STsearch(s,s2)) == -1){
            n2 = STinsert(s, s2);
            G->V++;
        }

        GRAPHinsertE(G, n1, n2);

    }

    G->tab = s;

    return G;
}