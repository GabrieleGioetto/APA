#include <stdio.h>
#include <stdlib.h>

#define N_TIPI_GIOIELLI 4

void inputDati(int* n_z,int* n_s,int* n_r,int* n_t);
int inserisciGioielli(int n_z,int n_s,int n_r,int n_t,int**** matriceOccorrenze);
int fZ(int n_z,int n_s,int n_r,int n_t, int**** matriceOccorrenze, int cont);
int fS(int n_z,int n_s,int n_r,int n_t, int**** matriceOccorrenze, int cont);
int fR(int n_z,int n_s,int n_r,int n_t, int**** matriceOccorrenze, int cont);
int fT(int n_z,int n_s,int n_r,int n_t, int**** matriceOccorrenze, int cont);
int ****initMatriceOccorrenze(int n_z, int n_s, int n_r, int n_t);
void freeMatriceOccorrenze(int**** matriceOccorrenze,int n_z, int n_s, int n_r, int n_t);

int main() {

    int**** matriceOccorrenze;
    int n_z, n_s, n_r, n_t;

    inputDati(&n_z, &n_s, &n_r, &n_t);

    /* CONDIZIONI DISPOSIZIONE
     * z - [z r]
     * s - [s t]
     * r - [s t]
     * t - [z r]
     */

    matriceOccorrenze = initMatriceOccorrenze(n_z, n_s, n_r, n_t);

    printf("Collana massima di lunghezza %d", inserisciGioielli(n_z, n_s, n_r, n_t, matriceOccorrenze));

    freeMatriceOccorrenze(matriceOccorrenze,n_z, n_s, n_r, n_t);

    return 0;
}

int ****initMatriceOccorrenze(int n_z, int n_s, int n_r, int n_t) {
    int i,j,t,m;
    int**** matriceOccorrenze = (int****)malloc((n_z + 1) * sizeof(int***));
    for (i = 0; i < (n_z + 1); ++i) {
        matriceOccorrenze[i] = (int***)malloc((n_s + 1) * sizeof(int**));
        for (j = 0; j < (n_s + 1); ++j) {
            matriceOccorrenze[i][j] = (int**)malloc((n_r + 1) * sizeof(int*));
            for (t = 0; t < (n_r + 1); ++t) {
                matriceOccorrenze[i][j][t] = (int*)malloc((n_t + 1) * sizeof(int));

                for (m = 0; m < (n_t + 1); ++m) {
                    matriceOccorrenze[i][j][t][m] = -1;//RIEMPIO LA MATRICE MULTIDIMENSIONALE DI -1
                }
            }
        }
    }
    return matriceOccorrenze;
}

void freeMatriceOccorrenze(int**** matriceOccorrenze,int n_z, int n_s, int n_r, int n_t) {
    int i,j,t;
    for (i = 0; i < (n_z + 1); ++i) {
        for (j = 0; j < (n_s + 1); ++j) {
            for (t = 0; t < (n_r + 1); ++t) {
                free(matriceOccorrenze[i][j][t]);
            }
            free( matriceOccorrenze[i][j]);
        }
        free(matriceOccorrenze[i]);
    }
    free(matriceOccorrenze);
}

int inserisciGioielli(int n_z,int n_s,int n_r,int n_t,int**** matriceOccorrenze){
    int* lunghezzeSequenze = calloc(N_TIPI_GIOIELLI, sizeof(int));

    if(n_z > 0)
        lunghezzeSequenze[0] = fZ(n_z, n_s, n_r, n_t,matriceOccorrenze,0);
    if(n_r > 0)
        lunghezzeSequenze[1]= fR(n_z, n_s, n_r, n_t,matriceOccorrenze,0);
    if(n_t > 0)
        lunghezzeSequenze[2]= fT(n_z, n_s, n_r, n_t,matriceOccorrenze,0);
    if(n_s > 0)
        lunghezzeSequenze[3] = fS(n_z, n_s, n_r, n_t,matriceOccorrenze,0);

    int maxLunghezza = lunghezzeSequenze[0];
    int i;
    for (i = 1; i < N_TIPI_GIOIELLI; ++i) {
        if(lunghezzeSequenze[i] > maxLunghezza)
            maxLunghezza = lunghezzeSequenze[i];
    }

    return maxLunghezza;
}

int fZ(int n_z,int n_s,int n_r,int n_t, int**** matriceOccorrenze, int cont){

    if( matriceOccorrenze[n_z][n_s][n_r][n_t] != -1)
        return  matriceOccorrenze[n_z][n_s][n_r][n_t];

    n_z--;

    int nZ = 0, nR = 0;

    if(n_z > 0)
        nZ = fZ(n_z, n_s, n_r, n_t,matriceOccorrenze, cont+1);
    if(n_r > 0)
        nR = fR(n_z, n_s, n_r, n_t,matriceOccorrenze, cont+1);

    int solParziale =  nZ > nR ? nZ : nR;
    matriceOccorrenze[n_z][n_s][n_r][n_t] = solParziale;

    return solParziale + 1;
}

int fS(int n_z,int n_s,int n_r,int n_t, int**** matriceOccorrenze, int cont){

    if( matriceOccorrenze[n_z][n_s][n_r][n_t] != -1)
        return  matriceOccorrenze[n_z][n_s][n_r][n_t];

    n_s--;

    int nS = 0, nT = 0;

    if(n_s > 0)
        nS = fS(n_z, n_s, n_r, n_t,matriceOccorrenze, cont+1);
    if(n_t > 0)
        nT = fT(n_z, n_s, n_r, n_t,matriceOccorrenze, cont+1);

    int solParziale = nS > nT ? nS : nT;
    matriceOccorrenze[n_z][n_s][n_r][n_t]  = solParziale;

    return solParziale + 1;
}

int fR(int n_z,int n_s,int n_r,int n_t, int**** matriceOccorrenze, int cont){

    if( matriceOccorrenze[n_z][n_s][n_r][n_t] != -1)
        return  matriceOccorrenze[n_z][n_s][n_r][n_t];

    n_r--;

    int nS = 0, nT = 0;

    if(n_s > 0)
        nS = fS(n_z, n_s, n_r, n_t,matriceOccorrenze, cont+1);
    if(n_t > 0)
        nT = fT(n_z, n_s, n_r, n_t,matriceOccorrenze, cont+1);

    int solParziale = nS > nT ? nS : nT;
    matriceOccorrenze[n_z][n_s][n_r][n_t]  = solParziale;

    return solParziale + 1;
}

int fT(int n_z,int n_s,int n_r,int n_t, int**** matriceOccorrenze, int cont){

    if( matriceOccorrenze[n_z][n_s][n_r][n_t] != -1)
        return  matriceOccorrenze[n_z][n_s][n_r][n_t];

    n_t--;

    int nZ = 0, nR = 0;

    if(n_z > 0)
        nZ = fZ(n_z, n_s, n_r, n_t,matriceOccorrenze, cont+1);
    if(n_r > 0)
        nR = fR(n_z, n_s, n_r, n_t,matriceOccorrenze, cont+1);

    int solParziale =  nZ > nR ? nZ : nR;
    matriceOccorrenze[n_z][n_s][n_r][n_t] = solParziale;

    return solParziale + 1;
}

void inputDati(int* n_z,int* n_s,int* n_r,int* n_t){
    printf("Inserisci numero zaffiri: ");
    scanf("%d", n_z);
    printf("Inserisci numero rubini: ");
    scanf("%d", n_r);
    printf("Inserisci numero topazi: ");
    scanf("%d", n_t);
    printf("Inserisci numero smeraldi: ");
    scanf("%d", n_s);
}
