#include <stdio.h>
#include <stdlib.h>

#define NOME_FILE "matrice.txt"

int **malloc2dR(int* nr, int* nc);
void stampaMatrice(int nr, int nc, int **matrice);
void separa(int **mat, int nr, int nc, int** vettoreNeri, int** vettoreBianchi, int* nCaselleBianche, int* nCaselleNere);
void stampaVettore(int nCaselle, const int *vettore);

int main() {

    int nr, nc;

    //Alloco e leggo la matrice dal file
    int **matrice = malloc2dR(&nr, &nc);

    stampaMatrice(nr, nc, matrice);

    int nCaselleBianche, nCaselleNere;
    int *vettoreNeri, *vettoreBianchi;

    separa(matrice, nr, nc, &vettoreNeri, &vettoreBianchi, &nCaselleBianche, &nCaselleNere);

    //Stampo i vettori calcolati nella funzione separa
    printf("CASELLE BIANCHE: ");
    stampaVettore(nCaselleNere, vettoreNeri);
    printf("CASELLE NERE: ");
    stampaVettore(nCaselleBianche, vettoreBianchi);

    //Dealloco i puntatori
    free(matrice);
    free(vettoreBianchi);
    free(vettoreNeri);

    return 0;
}

void stampaVettore(int nCaselle, const int *vettore) {
    int i;
    for (i = 0; i < nCaselle; ++i) {
        printf("%d ",vettore[i]);
    }
    printf("\n");
}

void separa(int **mat, int nr, int nc, int** vettoreNeri, int** vettoreBianchi, int* nCaselleBianche, int* nCaselleNere) {

    *nCaselleBianche = (nr * nc) / 2;
    *nCaselleNere = (nr * nc) / 2;

    if (nr % 2 == 1 && nc % 2 == 1)//Numero caselle totali dispari
        (*nCaselleBianche)++;

    *vettoreBianchi = (int *) malloc(sizeof(int) * (*nCaselleBianche));
    *vettoreNeri = (int *) malloc(sizeof(int) * (*nCaselleNere));

    int i, j, contN = 0, contB = 0;
    //CICLO RIGHE SCACCHIERA
    for (i = 0; i < nr; ++i) {
        //CICLO COLONNE SCACCHIERA PER OGNI RIGA
        for (j = 0; j < nc; ++j) {
            if ((i + j) % 2)
                (*vettoreBianchi)[contB++] = mat[i][j];
            else
                (*vettoreNeri)[contN++] = mat[i][j];
        }
    }
}

void stampaMatrice(int nr, int nc, int **matrice) {
    printf("NR: %d NC: %d\n", nr, nc);
    int i,j;
    for (i = 0; i < nr; ++i) {
        for (j = 0; j < nc; ++j) {
            printf("%d ",matrice[i][j]);
        }
        printf("\n");
    }
}

int **malloc2dR(int* nr, int* nc) {

    FILE *fp = fopen(NOME_FILE, "r");

    if (fp == NULL) {
        printf("Errore apertura file %s", NOME_FILE);
        exit(-1);
    }

    fscanf(fp, "%d %d", nr, nc);

    int i, j;

    int **matrice;

    matrice = (int **) malloc(sizeof(int *) * (*nr));
    for (i = 0; i < *nr; ++i) {
        matrice[i] = (int *) malloc(sizeof(int) * (*nc));
        for (j = 0; j < *nc; ++j)
            fscanf(fp, "%d", &matrice[i][j]);
    }

    fclose(fp);

    return matrice;
}
