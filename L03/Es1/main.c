#include <stdio.h>
#include <stdlib.h>

#define LUNGHMAX 50

typedef struct{
    int r;//riga
    int c;//colonna
    int base;
    int altezza;
}rettangolo;

int leggiMatrice(int* nr, int* nc,int mappa[][LUNGHMAX]);
void copiaRettangolo(rettangolo* rett,int r, int c, int base, int altezza);
void cercaRettangoli(rettangolo* maxBase, rettangolo* maxAltezza, rettangolo* maxArea, int mappa[][LUNGHMAX],int nr, int nc);
void stampaRisultati(rettangolo maxBase,rettangolo maxAltezza,rettangolo maxArea);
void saltaRettangolo(int mappa[][LUNGHMAX], int i, int j, int *base, int *altezza);
int riconosciRegione(int mappa[][LUNGHMAX],int nr,int nc,int i,int j,int* base,int* altezza);
void controlloRettangoli(rettangolo* maxBase, rettangolo* maxAltezza, rettangolo* maxArea, int base, int altezza, int i, int j);

int main() {

    int mappa[LUNGHMAX][LUNGHMAX];
    int nr, nc;

    if (!leggiMatrice(&nr,&nc,mappa)){
        printf("Errore lettura file");
        return -1;
    }

    rettangolo maxBase = {0,0,0,0,0};
    rettangolo maxAltezza = {0,0,0,0,0};
    rettangolo maxArea = {0,0,0,0,0};

    cercaRettangoli(&maxBase,&maxAltezza,&maxArea,mappa,nr,nc);

    stampaRisultati(maxBase,maxAltezza,maxArea);

    return 0;
}

void stampaRisultati(rettangolo maxBase,rettangolo maxAltezza,rettangolo maxArea){
    printf("Max Base: estr. sup. SX=<%d,%d> b=%d, h=%d, Area=%d\n",maxBase.r,maxBase.c,maxBase.base,maxBase.altezza,maxBase.base*maxBase.altezza);
    printf("Max Area: estr. sup. SX=<%d,%d> b=%d, h=%d, Area=%d\n",maxArea.r,maxArea.c,maxArea.base,maxArea.altezza,maxArea.base*maxArea.altezza);
    printf("Max Altezza: estr. sup. SX=<%d,%d> b=%d, h=%d, Area=%d",maxAltezza.r,maxAltezza.c,maxAltezza.base,maxAltezza.altezza,maxAltezza.base*maxAltezza.altezza);
}


void cercaRettangoli(rettangolo* maxBase, rettangolo* maxAltezza, rettangolo* maxArea, int mappa[][LUNGHMAX],int nr, int nc){
    int i,j,k,t;
    int base,altezza;

    for (i = 0; i < nr; i++) {//Scorro righe
        for (j = 0; j < nc; j++) {//Scorro colonne

            if (riconosciRegione(mappa,nr,nc,i,j,&base,&altezza)) {
                printf("Rettangolo di estremo (%d,%d) di base %d ed altezza %d\n", i, j, base, altezza);

                controlloRettangoli(maxBase, maxAltezza, maxArea, base, altezza, i, j);//Controlla se i rettangoli
            }
        }
    }
}

void controlloRettangoli(rettangolo* maxBase, rettangolo* maxAltezza, rettangolo* maxArea, int base, int altezza, int i, int j){
    if (maxBase->base < base)
        copiaRettangolo(maxBase, i, j, base, altezza);
    if (maxAltezza->altezza < altezza)
        copiaRettangolo(maxAltezza, i, j, base, altezza);
    if (maxArea->altezza * maxArea->base < base * altezza)
        copiaRettangolo(maxArea, i, j, base, altezza);
}

int riconosciRegione(int mappa[][LUNGHMAX],int nr,int nc,int i,int j,int* base,int* altezza){

    int k,t;

    if(!mappa[i][j])
        return 0;

    for (k = j; k < nc &&mappa[i][k]; k++);//Scorro riga per vedere caselle == 1

    k--;

    for (t = i+1; t < nr && mappa[t][k]; ++t);//Scorro colonna

    t--;

    *base = k + 1 - j;
    *altezza = t + 1 - i;

    saltaRettangolo(mappa,i,j,base,altezza);//Imposto caselle già lette a zero, per non rileggerle


    j = k +1;//Salto caselle già viste(solo per riga)

    return 1;

}

void saltaRettangolo(int mappa[][LUNGHMAX], int i, int j, int *base, int *altezza){
    int k,t;
    for (k = i; k < i + *altezza; k++) {
        for (t = j; t < j + *base; t++) {
            mappa[k][t] = 0;
        }
    }
}

void copiaRettangolo(rettangolo* rett,int r, int c, int base, int altezza){
    rett->r = r;
    rett->c = c;
    rett->altezza = altezza;
    rett->base = base;
};

int leggiMatrice(int* nr, int* nc,int mappa[][LUNGHMAX]){

    FILE* fp = fopen("mappa.txt", "r");

    if(fp == NULL){
        return 0;
    }

    fscanf(fp,"%d %d", nr, nc);

    int i,j;
    for (i = 0; i < *nr; ++i) {
        for (j = 0; j < *nc; ++j) {
            fscanf(fp,"%d",&mappa[i][j]);
        }
    }

    fclose(fp);

    return 1;
}