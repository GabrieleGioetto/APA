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

tessera **leggiScacchieraIniziale(int *nr, int *nc, tessera* tessere, int*** posizioniOccupate, int** markTessereUsate, int* contTessereUsate);
tessera *leggiTessere(int *nTessereTotali);
int disp(tessera* tessere,int contTessereNonUsate, int** sol,int** solMax,int** markRotazioneMax,int* contSolMax,int* markTessereNonUsate,int** markRotazione,int** posizioniOccupateFisse,int** posizioniOccupate,int* indiciTessereNonUsate, int pos, int nr, int nc);
int disp_rotazione(tessera* tessere,int contTessereNonUsate, int** sol,int** solMax,int** markRotazioneMax,int* contSolMax,int** markRotazione,int** posizioniOccupateFisse, int pos, int nr, int nc);
void stampaSoluzione(int** sol);
int controlloSoluzione(tessera* tessere,int **sol, int* contSolMax, int **markRotazione, int nr, int nc);
void copiaSol(int **sol, int **solMax,int** markRotazioneMax,int** markRotazione ,int nr, int nc);

int main() {

    int nr, nc, nTessereTotali;
    int** posizioniOccupate;//TODO DA ALLOCARE DINAMICAMENTE
    int* markTessereUsate;
    int contTessereUsate = 0;
    int i,j = 0;

    tessera** tabella;
    tessera* tessere;

    tessere = leggiTessere(&nTessereTotali);
    tabella = leggiScacchieraIniziale(&nr, &nc, tessere, &posizioniOccupate, &markTessereUsate, &contTessereUsate);

    //CREAZIONI OCCUPAZIONI FISSE
    int** posizioniOccupateFisse = (int**)malloc(sizeof(int*) * nr);
    for (i = 0; i < nr; ++i) {
        posizioniOccupateFisse[i] = (int*)malloc(sizeof(int) * nc);
    }
    for (i = 0; i < nr; ++i) {
        for (j = 0; j < nc; ++j) {
            posizioniOccupateFisse[i][j] = posizioniOccupate[i][j];
        }
    }

    int contTessereNonUsate = nTessereTotali - contTessereUsate;

    int* indiciTessereNonUsate = (int*)malloc(sizeof(int) * (contTessereNonUsate));
    int* markTessereNonUsate = (int*)calloc(contTessereNonUsate, sizeof(int));

    printf("Indici tessere usate main: ");
    for (j = 0; j < nTessereTotali; ++j) {
        printf("%d ", markTessereUsate[j]);
    }
    printf("\n\n");

    //TODO DA METTERE IN UNA FUNZIONE
    //Riempio tessere non usate
    j = 0;
    for (i = 0; i < nTessereTotali; ++i) {
        if(markTessereUsate[i] == 0){
            indiciTessereNonUsate[j++] = i;//SALVO INDICE TESSERE NON USATA
        }
    }

    printf("Indici tessere non usate main: ");
    for (j = 0; j < contTessereNonUsate; ++j) {
        printf("%d ", indiciTessereNonUsate[j]);
    }
    printf("\n\n");


    //ALLOCO MARK ROTAZIONE
    int** markRotazione = (int**)malloc(sizeof(int*) * nr);
    for (i = 0; i < nr; ++i) {
        markRotazione[i] = (int*)calloc(nc,sizeof(int));
        for (j = 0; j < nc; ++j) {
            if(markTessereUsate[i*nc +j] == 1)
                markRotazione[i][j] = tabella[i][j].rotazione;
        }
    }

    printf("MARK ROTAZIONE: \n");
    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 3; ++j) {
            printf("%d ", markRotazione[i][j]);
        }
        printf("\n");
    }





    //ALLOCO SOL_MAX e markRotazioneMax
    int** solMax = (int**)malloc(sizeof(int*) * nr);
    for (i = 0; i < nr; ++i) {
        solMax[i] = (int*)calloc(nc,sizeof(int));
    }

    int** markRotazioneMax = (int**)malloc(sizeof(int*) * nr);
    for (i = 0; i < nr; ++i) {
        markRotazioneMax[i] = (int*)calloc(nc,sizeof(int));
    }


    int contSolMax = -1;

    disp(tessere,contTessereNonUsate, posizioniOccupate, solMax,markRotazioneMax,&contSolMax,markTessereNonUsate,markRotazione, posizioniOccupateFisse,posizioniOccupate,indiciTessereNonUsate, 0, nr, nc);

    printf("\n\n");

    printf("RIGHE: \n");
    for (i = 0; i < nr; ++i) {
        for (j = 0; j < nc; ++j) {
            printf("%c %d ", tessere[solMax[i][j]].tubi[markRotazioneMax[i][j]].colore,tessere[solMax[i][j]].tubi[markRotazioneMax[i][j]].valore);
        }
        printf("\n");
    }

    printf("\n\n\n");

    printf("COLONNE: \n");
    for (i = 0; i < nr; ++i) {
        for (j = 0; j < nc; ++j) {
            printf("%c %d ", tessere[solMax[i][j]].tubi[!markRotazioneMax[i][j]].colore,tessere[solMax[i][j]].tubi[!markRotazioneMax[i][j]].valore);
        }
        printf("\n");
    }


    return 0;
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

int disp(tessera* tessere,int contTessereNonUsate, int** sol,int** solMax,int** markRotazioneMax,int* contSolMax,int* markTessereNonUsate,int** markRotazione,int** posizioniOccupateFisse,int** posizioniOccupate,int* indiciTessereNonUsate, int pos, int nr, int nc){


    int i, j;
    if(pos >= 9){
        printf("Soluzione Finale: \n");
        //Stampa soluzione parziale
        stampaSoluzione(sol);


        //TODO RICHIAMA DISP_ROTAZIONI
        disp_rotazione(tessere,contTessereNonUsate, sol,solMax,markRotazioneMax, contSolMax, markRotazione, posizioniOccupateFisse, 0, nr, nc);

        printf("------------------------------------------------------------------------------------");
        return 1;
    }

    int pos_i = pos/nc;
    int pos_j = pos % nc;

    if(posizioniOccupateFisse[pos_i][pos_j] != -1){
        disp(tessere,contTessereNonUsate,sol,solMax,markRotazioneMax,contSolMax,markTessereNonUsate, markRotazione,posizioniOccupateFisse,posizioniOccupate,indiciTessereNonUsate, pos + 1, nr, nc);
        return 1;
    }


    for(i = 0; i < contTessereNonUsate; i++){

        /*
        printf("markTessereNonUsate : ");
        for(j = 0; j < contTessereNonUsate; j++)
            printf("%d", markTessereNonUsate[j]);
        printf("\n");
        */
        if(markTessereNonUsate[i] == 0){
            markTessereNonUsate[i] = 1;
            sol[pos_i][pos_j] = indiciTessereNonUsate[i];
            //printf("Soluzione parziale: \n");
            //stampaSoluzione(sol);

            disp(tessere,contTessereNonUsate,sol,solMax,markRotazioneMax,contSolMax,markTessereNonUsate, markRotazione,posizioniOccupateFisse,posizioniOccupate,indiciTessereNonUsate, pos + 1, nr, nc);
            markTessereNonUsate[i] = 0;
        }
    }
    return 1;
    //TODO CAMBIARE 1 IN VOID
}

int disp_rotazione(tessera* tessere,int contTessereNonUsate, int** sol,int** solMax,int** markRotazioneMax,int* contSolMax,int** markRotazione,int** posizioniOccupateFisse, int pos, int nr, int nc){

    //TODO MEMOIZATION

    //TODO CAMBIARE TUTTI I DIM CON NR E NC
    int i,j;
    if (pos >= nr * nc) {

        if(controlloSoluzione(tessere,sol,contSolMax,markRotazione, nr,nc)){

            copiaSol(sol, solMax,markRotazioneMax,markRotazione, nr,nc);
            printf("SOL MAX ATTUALE: \n");
            stampaSoluzione(solMax);
        }


        for (i=0; i<nr; ++i) {
            for (j = 0; j < nc; j++){
                printf("%d %d \t", sol[i][j],markRotazione[i][j]);
            }
            printf("\n");
        }

        printf("\n\n");
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


    stampaSoluzione(sol);
    for (i = 0; i < nr; ++i) {
        for (j = 0; j < nc; ++j) {
            printf("%c %d ", tessere[sol[i][j]].tubi[markRotazione[i][j]].colore,tessere[sol[i][j]].tubi[markRotazione[i][j]].valore);
        }
        printf("\n");
    }

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

    for (j = 0; j < nc; ++j) {
        for (i = 0; i < nr; ++i) {
            printf("%c %d ", tessere[sol[i][j]].tubi[markRotazione[i][j]].colore,tessere[sol[i][j]].tubi[markRotazione[i][j]].valore);
        }
        printf("\n");
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


void stampaSoluzione(int** sol){
    int i,j;
    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 3; ++j) {
            printf("%d ", sol[i][j]);
        }
        printf("\n");
    }
    printf("\n------------------------------\n");

}

tessera **leggiScacchieraIniziale(int *nr, int *nc, tessera* tessere, int*** posizioniOccupate, int** markTessereUsate,int* contTessereUsate) {

    tessera **tabella;
    int **posizioniOccupate_tmp;

    FILE* fp;
    fp = fopen(FILE_BOARD, "r");

    if (fp == NULL) {
        printf("Errore apertura file %s" , FILE_BOARD);
        exit(-1);
    }

    fscanf(fp, "%d %d", nr, nc);

    tabella = (tessera**)malloc(*nr * sizeof(tessera*));
    posizioniOccupate_tmp = (int**)malloc(sizeof(int*) * (*nr));

    int i,j;
    for (i = 0; i < *nr; ++i){
        tabella[i] = (tessera*)malloc(*nc * sizeof(tessera));
        posizioniOccupate_tmp[i] = (int*)calloc(*nc,sizeof(int));
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
                tabella[i][j] = tessere[indiceTessera];
                tabella[i][j].rotazione = rotazioneTessera;
                posizioniOccupate_tmp[i][j] = indiceTessera;
                (*markTessereUsate)[indiceTessera] = 1;
                (*contTessereUsate)++;
            }
        }
    }

    *posizioniOccupate = posizioniOccupate_tmp;
    return tabella;
}