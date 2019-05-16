#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define FILE_TILES "tiles.txt"
#define FILE_BOARD "board.txt"

typedef struct{
    char colore;
    int valore;
}tubo;

typedef struct{
    tubo tubi[2];
    int rotazione;
}tessera;

void leggiScacchieraIniziale(int *nr, int *nc, tessera* tessere, int*** posizioniOccupate, int** markTessereUsate, int*** markRotazione,int* contTessereUsate);
tessera *leggiTessere(int *nTessereTotali);
int perm(tessera* tessere,int contTessereNonUsate, int** sol,int** solMax,int** markRotazioneMax,int* contSolMax,int* markTessereNonUsate,int** markRotazione,int** posizioniOccupateFisse,int* indiciTessereNonUsate, int pos, int nr, int nc);
int disp_rotazione(tessera* tessere,int contTessereNonUsate, int** sol,int** solMax,int** markRotazioneMax,int* contSolMax,int** markRotazione,int** posizioniOccupateFisse, int pos, int nr, int nc);
int controlloSoluzione(tessera* tessere,int **sol, int* contSolMax, int **markRotazione, int nr, int nc);
void copiaSol(int **sol, int **solMax,int** markRotazioneMax,int** markRotazione ,int nr, int nc);
void stampaSoluzioneFinale(int nr, int nc, tessera *tessere, int **solMax, int **markRotazioneMax);
int **initPosizioniOccupateFisse(int nr, int nc, int **posizioniOccupate);
int *initMarkTessereNonUsate(int nTessereTotali, int *markTessereUsate, int contTessereNonUsate, int *indiciTessereNonUsate);
void initSolMax_MarkRotazioneMax(int nr, int nc, int ***solMax, int ***markRotazioneMax);
void freeMatriceInteri(int** matrice, int nr);

int main() {

    int nr, nc, nTessereTotali;
    int** posizioniOccupate;
    int* markTessereUsate;
    int** markRotazione;
    int contTessereUsate = 0;
    int contSolMax = -1;
    tessera* tessere;

    tessere = leggiTessere(&nTessereTotali);
    leggiScacchieraIniziale(&nr, &nc, tessere, &posizioniOccupate, &markTessereUsate, &markRotazione, &contTessereUsate);

    //MATRICE CHE SERVE A MANTENERE IN MEMORIA LE TESSERE FISSE DELLA SCACCHIERE(IN BASE ALLA SCACCHIERA INIZIALE)
    int** posizioniOccupateFisse;
    posizioniOccupateFisse = initPosizioniOccupateFisse(nr, nc, posizioniOccupate);

    int contTessereNonUsate = nTessereTotali - contTessereUsate;

    //VETTORE CON INDICI DELLE TESSERE NON USATE
    int* indiciTessereNonUsate = (int*)malloc(sizeof(int) * (contTessereNonUsate));

    //VETTORE DI SUPPORTO PER PERMUTAZIONI
    int* markTessereNonUsate;
    markTessereNonUsate = initMarkTessereNonUsate(nTessereTotali, markTessereUsate, contTessereNonUsate,
                                                  indiciTessereNonUsate);

    //SOLMAX: MATRICE CON INDICI TESSERE
    //MARKROTAZIONEMAX: MATRICE CON VALORI 1 OPPURE 0 (TESSERA RUOTATA/NON RUOTATA)
    int **solMax, **markRotazioneMax;
    initSolMax_MarkRotazioneMax(nr, nc, &solMax, &markRotazioneMax);
    
    perm(tessere,contTessereNonUsate, posizioniOccupate, solMax,markRotazioneMax,&contSolMax,markTessereNonUsate,markRotazione, posizioniOccupateFisse,indiciTessereNonUsate, 0, nr, nc);

    stampaSoluzioneFinale(nr, nc, tessere, solMax, markRotazioneMax);

    //DEALLOCO
    free(markTessereUsate);
    free(indiciTessereNonUsate);
    free(markTessereNonUsate);
    free(tessere);
    freeMatriceInteri(posizioniOccupate, nr);
    freeMatriceInteri(markRotazione, nr);
    freeMatriceInteri(posizioniOccupateFisse, nr);
    freeMatriceInteri(solMax, nr);
    freeMatriceInteri(markRotazioneMax, nr);


    return 0;
}

void freeMatriceInteri(int** matrice, int nr){
    int i;
    for (i = 0; i < nr; ++i) {
        free(matrice[i]);
    }
    free(matrice);
}

void initSolMax_MarkRotazioneMax(int nr, int nc, int ***solMax, int ***markRotazioneMax) {
    int i;
    (*solMax) = (int**)malloc(sizeof(int*) * nr);
    (*markRotazioneMax) = (int**)malloc(sizeof(int*) * nr);
    for (i = 0; i < nr; ++i) {
        (*solMax)[i] = (int*)calloc(nc, sizeof(int));
        (*markRotazioneMax)[i] = (int*)calloc(nc, sizeof(int));
    }
}

int *initMarkTessereNonUsate(int nTessereTotali, int *markTessereUsate, int contTessereNonUsate, int *indiciTessereNonUsate) {
    int *markTessereNonUsate;
    markTessereNonUsate = (int*)calloc(contTessereNonUsate, sizeof(int));

    int i,j = 0;
    //Riempio tessere non usate
    for (i = 0; i < nTessereTotali; ++i) {
        if(markTessereUsate[i] == 0){
            indiciTessereNonUsate[j++] = i;//SALVO INDICE TESSERE NON USATA
        }
    }
    return markTessereNonUsate;
}

int **initPosizioniOccupateFisse(int nr, int nc, int **posizioniOccupate) {
    int i,j;

    int ** posizioniOccupateFisse_tmp = (int**)malloc(sizeof(int*) * nr);
    for (i = 0; i < nr; ++i) {
        posizioniOccupateFisse_tmp[i] = (int*)malloc(sizeof(int) * nc);
    }


    for (i = 0; i < nr; ++i) {
        for (j = 0; j < nc; ++j) {
            posizioniOccupateFisse_tmp[i][j] = posizioniOccupate[i][j];
        }
    }
    return posizioniOccupateFisse_tmp;
}

void stampaSoluzioneFinale(int nr, int nc, tessera *tessere, int **solMax, int **markRotazioneMax) {

    int i,j;

    printf("RIGHE: \n");
    for (i = 0; i < nr; ++i) {
        for (j = 0; j < nc; ++j) {
            printf("%c %d ", tessere[solMax[i][j]].tubi[markRotazioneMax[i][j]].colore,tessere[solMax[i][j]].tubi[markRotazioneMax[i][j]].valore);
        }
        printf("\n");
    }

    printf("\n");

    printf("COLONNE: \n");
    for (i = 0; i < nr; ++i) {
        for (j = 0; j < nc; ++j) {
            printf("%c %d ", tessere[solMax[i][j]].tubi[!markRotazioneMax[i][j]].colore,tessere[solMax[i][j]].tubi[!markRotazioneMax[i][j]].valore);
        }
        printf("\n");
    }
}

tessera *leggiTessere(int *nTessereTotali) {
    tessera *tessere;
    FILE *fp;

    fp = fopen(FILE_TILES, "r");

    if (fp == NULL) {
        printf("Errore apertura file %s", FILE_TILES);
        exit(-1);
    }

    fscanf(fp, "%d", nTessereTotali);

    tessere = (tessera *) malloc(*nTessereTotali * sizeof(tessera));


    int i;
    for (i = 0; i < *nTessereTotali; ++i) {
        fscanf(fp, "\n%c", &tessere[i].tubi[0].colore);
        fscanf(fp, "%d", &tessere[i].tubi[0].valore);
        fscanf(fp, " %c", &tessere[i].tubi[1].colore);
        fscanf(fp, "%d", &tessere[i].tubi[1].valore);
    }

    return tessere;

}

int perm(tessera* tessere,int contTessereNonUsate, int** posizioniOccupate,int** solMax,int** markRotazioneMax,int* contSolMax,int* markTessereNonUsate,int** markRotazione,int** posizioniOccupateFisse,int* indiciTessereNonUsate, int pos, int nr, int nc){


    int i;
    if(pos >= (nr * nc)){
        disp_rotazione(tessere,contTessereNonUsate, posizioniOccupate,solMax,markRotazioneMax, contSolMax, markRotazione, posizioniOccupateFisse, 0, nr, nc);

        return 1;
    }

    int pos_i = pos/nc;
    int pos_j = pos % nc;

    if(posizioniOccupateFisse[pos_i][pos_j] != -1){
        perm(tessere,contTessereNonUsate,posizioniOccupate,solMax,markRotazioneMax,contSolMax,markTessereNonUsate, markRotazione,posizioniOccupateFisse,indiciTessereNonUsate, pos + 1, nr, nc);
        return 1;
    }


    for(i = 0; i < contTessereNonUsate; i++){
        if(markTessereNonUsate[i] == 0){
            markTessereNonUsate[i] = 1;
            posizioniOccupate[pos_i][pos_j] = indiciTessereNonUsate[i];

            perm(tessere,contTessereNonUsate,posizioniOccupate,solMax,markRotazioneMax,contSolMax,markTessereNonUsate, markRotazione,posizioniOccupateFisse,indiciTessereNonUsate, pos + 1, nr, nc);
            markTessereNonUsate[i] = 0;
        }
    }
    return 1;
}

int disp_rotazione(tessera* tessere,int contTessereNonUsate, int** sol,int** solMax,int** markRotazioneMax,int* contSolMax,int** markRotazione,int** posizioniOccupateFisse, int pos, int nr, int nc){

    if (pos >= nr * nc) {

        if(controlloSoluzione(tessere,sol,contSolMax,markRotazione, nr,nc)){
            copiaSol(sol, solMax,markRotazioneMax,markRotazione, nr,nc);
        }

        return 1;
    }

    int pos_i = pos/nc;
    int pos_j = pos % nc;

    if(posizioniOccupateFisse[pos_i][pos_j] != -1){
        disp_rotazione(tessere,contTessereNonUsate,sol,solMax,markRotazioneMax,contSolMax,markRotazione, posizioniOccupateFisse, pos + 1, nr, nc);
        return 1;
    }


    markRotazione[pos_i][pos_j] = 0;
    disp_rotazione(tessere,contTessereNonUsate,sol,solMax,markRotazioneMax,contSolMax,markRotazione, posizioniOccupateFisse, pos + 1, nr, nc);
    markRotazione[pos_i][pos_j] = 1;
    disp_rotazione(tessere,contTessereNonUsate,sol,solMax,markRotazioneMax,contSolMax,markRotazione, posizioniOccupateFisse, pos + 1, nr, nc);
    return 1;
}

void copiaSol(int **sol, int **solMax,int** markRotazioneMax,int** markRotazione, int nr, int nc){
    int i,j;

    for (i = 0; i < nr; ++i) {
        for (j = 0; j < nc; ++j) {
            solMax[i][j] = sol[i][j];
            markRotazioneMax[i][j] = markRotazione[i][j];
        }

    }
}

int controlloSoluzione(tessera* tessere,int **sol, int* contSolMax, int **markRotazione, int nr , int nc) {
    int cont = 0;
    int contTotale = 0;
    int i,j;

    //CONTROLLO RIGHE
    for (i = 0; i < nr; ++i) {
        cont = tessere[sol[i][0]].tubi[markRotazione[i][0]].valore;
        for (j = 1; j < nc; ++j) {
            //Se è rotato prendo il secondo tubo
            if(tessere[sol[i][j]].tubi[markRotazione[i][j]].colore == tessere[sol[i][j-1]].tubi[markRotazione[i][j - 1]].colore)
                cont += tessere[sol[i][j]].tubi[markRotazione[i][j]].valore;
            else
                cont = 0;
        }

        contTotale += cont;
    }

    //CONTROLLO COLONNE
    for (j = 0; j < nc; ++j) {
        cont = tessere[sol[0][j]].tubi[!markRotazione[0][j]].valore;
        for (i = 1; i < nr; ++i) {
            //Se è rotato prendo il secondo tubo
            if(tessere[sol[i][j]].tubi[!markRotazione[i][j]].colore == tessere[sol[i - 1][j]].tubi[!markRotazione[i - 1][j]].colore)
                cont += tessere[sol[i][j]].tubi[!markRotazione[i][j]].valore;
            else
                cont = 0;
        }

        contTotale += cont;
    }

    if(contTotale > *contSolMax){
        *contSolMax = contTotale;
        return 1;
    }

    return 0;
}

void leggiScacchieraIniziale(int *nr, int *nc, tessera* tessere, int*** posizioniOccupate, int** markTessereUsate,int*** markRotazione,int* contTessereUsate) {

    int **posizioniOccupate_tmp;
    int **markRotazione_tmp;

    FILE* fp;
    fp = fopen(FILE_BOARD, "r");

    if (fp == NULL) {
        printf("Errore apertura file %s" , FILE_BOARD);
        exit(-1);
    }

    fscanf(fp, "%d %d", nr, nc);

    posizioniOccupate_tmp = (int**)malloc(sizeof(int*) * (*nr));
    markRotazione_tmp = (int**)malloc(sizeof(int*) * (*nr));


    int i,j;
    for (i = 0; i < *nr; ++i){
        posizioniOccupate_tmp[i] = (int*)calloc(*nc,sizeof(int));
        markRotazione_tmp[i] = (int*)calloc(*nc,sizeof(int));
    }

    for (i = 0; i < *nr; ++i) {
        for (j = 0; j < *nc; ++j) {
            posizioniOccupate_tmp[i][j] = -1;
        }
    }

    int indiceTessera, rotazioneTessera;
    *markTessereUsate = (int *)calloc( *nc * (*nr),sizeof(int));//Forese size_t

    for (i = 0; i < *nr; ++i) {
        for (j = 0; j < *nc; ++j) {
            fscanf(fp, "%d/%d", &indiceTessera, &rotazioneTessera);
            if(indiceTessera != -1){
                markRotazione_tmp[i][j] = rotazioneTessera;
                posizioniOccupate_tmp[i][j] = indiceTessera;
                (*markTessereUsate)[indiceTessera] = 1;
                (*contTessereUsate)++;
            }
        }
    }

    *posizioniOccupate = posizioniOccupate_tmp;
    *markRotazione = markRotazione_tmp;
}