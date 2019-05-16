#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LUNGHMAX 255
#define NOME_FILE "brani.txt"

typedef struct{
    char** scelte;
    int num_scelte;
}Livello;

Livello* leggiFile(int* nAmici);
int princ_molt(int pos, Livello* val, char** sol,int n, int count) ;
void stampaPlaylist(int nAmici, Livello *val);
void dealloca(Livello* val,int nAmici);

int main() {

    int nAmici;

    Livello *val = leggiFile(&nAmici);//Leggo il file e ritorno il vettore val con

    stampaPlaylist(nAmici, val);//Stampo canzoni scelte da ogni amico

    char **sol = (char **) malloc(sizeof(char*) * nAmici);

    printf("\n");
    printf("N solizioni: %d", princ_molt(0, val, sol, nAmici, 0));

    dealloca(val, nAmici);

    return 0;
}

void dealloca(Livello* val,int nAmici){
    int i,j;
    for (i = 0; i < nAmici; ++i) {
        for (j = 0; j < val[i].num_scelte; ++j) {
            free(val[i].scelte[j]);
        }
        free(val[i].scelte);
    }

    free(val);
}

Livello* leggiFile(int* nAmici) {
    FILE *fp = fopen(NOME_FILE, "r");

    if (fp == NULL) {
        printf("Errore apertura file %s", NOME_FILE);
        exit(-1);
    }

    fscanf(fp, "%d", nAmici);

    Livello *val = (Livello *) malloc((*nAmici) * sizeof(Livello));

    int i, j;


    for (i = 0; i < *nAmici; ++i) {
        fscanf(fp, "%d", &(val[i].num_scelte));
        val[i].scelte = (char **) malloc(val[i].num_scelte * sizeof(char *));

        for (j = 0; j < val[i].num_scelte; ++j) {
            val[i].scelte[j] = (char *) malloc(LUNGHMAX * sizeof(char));
            fscanf(fp, "%s", val[i].scelte[j]);
        }
    }

    fclose(fp);

    return val;
}

void stampaPlaylist(int nAmici, Livello *val) {
    int i,j;

    printf("-----------\n");
    for (i = 0; i < nAmici; ++i) {
        for (j = 0; j < val[i].num_scelte; ++j) {
            printf("%s ",val[i].scelte[j]);
        }
        printf("\n-----------\n");
    }
}

int princ_molt(int pos, Livello* val, char** sol,int n, int count) {
    int i;

    if (pos >= n) {
        for (i = 0; i < n; ++i) {
            printf("%s ", sol[i]);
        }
        printf("\n");
        return count + 1;
    }

    for (i = 0; i < val[pos].num_scelte; ++i) {
        sol[pos] = val[pos].scelte[i];
        count = princ_molt(pos + 1, val, sol, n, count);
    }

    return count;
}