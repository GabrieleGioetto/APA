#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLUNGHNOMEFILE 20
#define MAXLUNGHMATRICE 30

typedef struct{
    int x;//Offset x
    int y;//Offset y
    int indicePrimoNumero[2];//Riga,colonna del primo numero della serie
    int indiceUltimoNumero[2];//Riga,colonna dell'ultimo numero della serie
    int n;//Lunghezza riga o colonna
}direzioni;


int caricaMatrice(int matrice[][MAXLUNGHMATRICE],int *nr, int *nc);
void ruota(direzioni dir,int matrice[][MAXLUNGHMATRICE],char selettore[],int indice,char direzione[],int posizioni,int nr,int nc);
void stampaMatrice(int matrice[][MAXLUNGHMATRICE], int nr, int nc);
void impostaStrutturaDirezioni(direzioni* dir,char selettore[],int indice,char direzione[],int nr,int nc );

int main() {

    int matrice[MAXLUNGHMATRICE][MAXLUNGHMATRICE];

    int nr, nc;

    if (!caricaMatrice(matrice, &nr, &nc)) {
        printf("Errore lettura file");
        return -1;
    }

    char selettore[9];
    int indice;
    char direzione[9];
    int posizioni;
    direzioni dir;

    while (1){
        printf("Inserisci <selettore> <indice> <direzione> <posizioni>: ");
        scanf("%s %d %s %d",selettore, &indice, direzione, &posizioni);

        if(!strcmp(selettore, "fine"))
            break;


        impostaStrutturaDirezioni(&dir,selettore,indice,direzione,nr,nc);

        ruota(dir,matrice, selettore, indice, direzione, posizioni, nr, nc);

        stampaMatrice(matrice,nr,nc);
    }

    return 0;

}

void impostaStrutturaDirezioni(direzioni* dir,char selettore[],int indice,char direzione[],int nr,int nc ){
    if (!strcmp(selettore,"riga") ){
        dir->n = nc;
        dir->y = 0;

        if (!strcmp(direzione,"destra")){
            dir->x = 1;
            dir->indicePrimoNumero[1] = 0;
            dir->indiceUltimoNumero[1] = nc-1;
        } else if (!strcmp(direzione,"sinistra")) {
            dir->x = -1;
            dir->indicePrimoNumero[1] = nc - 1;
            dir->indiceUltimoNumero[1] = 0;
        }

        dir->indicePrimoNumero[0] = indice;
        dir->indiceUltimoNumero[0] = indice;

    }
    if (!strcmp(selettore,"colonna")){
        dir->n = nr;
        dir->x = 0;

        if (!strcmp(direzione,"su")){
            dir->y = -1;
            dir->indicePrimoNumero[0] = nr-1;
            dir->indiceUltimoNumero[0] = 0;
        }else if (!strcmp(direzione,"giu")) {
            dir->y = +1;
            dir->indicePrimoNumero[0] = 0;
            dir->indiceUltimoNumero[0] = nr - 1;
        }

        dir->indicePrimoNumero[1] = indice;
        dir->indiceUltimoNumero[1] = indice;

    }
}

void ruota(direzioni dir,int matrice[][MAXLUNGHMATRICE],char selettore[],int indice,char direzione[],int posizioni,int nr,int nc) {

    int i,j,k;
    int tmp;
    for (i = 0; i < posizioni; i++) {

        tmp = matrice[dir.indiceUltimoNumero[0]][dir.indiceUltimoNumero[1]];//Salvo ultimo numero

        for (j = 0 ,k = 0; abs(j) < dir.n && abs(k) < dir.n; j += dir.y, k += dir.x) {
            matrice[dir.indiceUltimoNumero[0] - j][dir.indiceUltimoNumero[1] - k] = matrice[dir.indiceUltimoNumero[0] - j - dir.y][dir.indiceUltimoNumero[1] - k - dir.x];
        }

        matrice[dir.indicePrimoNumero[0]][dir.indicePrimoNumero[1]] = tmp;//Nella prima posizione metto l'ultimo numero
    }

}

int caricaMatrice(int matrice[][MAXLUNGHMATRICE],int *nr, int *nc) {

    char nomeFile[MAXLUNGHNOMEFILE];

    printf("Inserisci nome file('testo.txt'): ");
    scanf("%s", nomeFile);

    FILE *fp = fopen(nomeFile, "r");

    if (fp == NULL)
        return 0;

    int i, j;
    fscanf(fp, "%d %d", nr, nc);

    for (i = 0; i < *nr; i++) {
        for (j = 0; j < *nc; j++) {
            fscanf(fp, "%d", &matrice[i][j]);
        }
    }

    fclose(fp);

    return 1;
}

void stampaMatrice(int matrice[][MAXLUNGHMATRICE], int nr, int nc) {
    int i, j;
    for (i = 0; i < nr; i++) {
        for (j = 0; j < nc; j++) {
            printf("%d ", matrice[i][j]);
        }
        printf("\n");
    }
}