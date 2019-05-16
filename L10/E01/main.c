#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LUNGH_MAX_NOME 100
#define NOME_FILE "elementi.txt"

typedef struct{
    char nome[LUNGH_MAX_NOME];
    int tipo;
    int dirIng;
    int dirUsc;
    int reqPrec;
    int finale;
    double valore;
    int difficolta;
}elemento;

typedef struct{
    int esercizi[5];
}diagonale;

typedef struct{
    int nElementi_1;
    int nElementi_2;
    int nElementi_3;
}nElementiFinale;

double sommaEserciziTotaleMax = 0;
nElementiFinale contElementiFinaliMax = {0,0,0};

elemento *leggiElementiDaFile(int *nElementi);
void inputValori(int *DD, int *DP);
//void disp_rip(int pos,int posElementi,nElementiFinale contElementiFinali, diagonale* solDiagonali, diagonale* solMaxDiagonali,elemento* elementi, int nElementi, int DD, int DP);
void disp_rip_2(int pos,nElementiFinale contElementiFinali, diagonale* solDiagonali, diagonale* solMaxDiagonali,elemento* elementi, int nElementi, int DD, int DP);
int controlloPruningElementi(int pos, int posElementi, diagonale *solDiagonali, elemento *elementi, int nElementi, int DD, int DP);
int controlloPruningDiagonali(int pos, nElementiFinale contElementiFinali, diagonale *solDiagonali, elemento *elementi);
double calcolaValoreDiagonale(int pos, int posElementi, diagonale *solDiagonali, elemento *elementi);
int controlloFinaleDiagonali(int posDiagonale, nElementiFinale contElementiFinali, diagonale *solDiagonali, elemento *elementi, int nElementi, int DD, int DP);
int getElementoFinale(int pos, nElementiFinale contElementiFinali);
void salvaElementoFinale(int pos, nElementiFinale *contElementiFinali, int posElementi);
int calcolaDifficoltaDiagonale(int pos, int posElementi, diagonale *solDiagonali, elemento *elementi);
void stampaSoluzioneFinale(diagonale *solMaxDiagonali, elemento *elementi);

double calcolaValoreProgramma(nElementiFinale contElementiFinale, diagonale *solDiagonali, elemento *elementi);

int main() {

    int nElementi;
    elemento* elementi = leggiElementiDaFile(&nElementi);

    int DD, DP;
    inputValori(&DD, &DP);

    diagonale* solDiagonali = (diagonale*)malloc(3 * sizeof(diagonale));
    diagonale* solMaxDiagonali = (diagonale*)malloc(3 * sizeof(diagonale));
    nElementiFinale contElementiFinali = {-1,-1,-1};

    disp_rip_2(0,contElementiFinali,solDiagonali,solMaxDiagonali, elementi, nElementi, DD, DP);

    stampaSoluzioneFinale(solMaxDiagonali,elementi);

    return 0;
}

void stampaSoluzioneFinale(diagonale *solMaxDiagonali, elemento *elementi) {
    int i,j;

    printf("Soluzione finale (valore: %f): \n", calcolaValoreProgramma(contElementiFinaliMax, solMaxDiagonali, elementi));

    for (i = 0; i < 3; ++i) {
        for (j = 0; j < getElementoFinale(i,contElementiFinaliMax); ++j) {
            printf("%s ", elementi[solMaxDiagonali[i].esercizi[j]].nome);
        }
        printf("\n");
    }
}

void disp_rip_2(int pos, nElementiFinale contElementiFinali, diagonale* solDiagonali, diagonale* solMaxDiagonali,elemento* elementi, int nElementi, int DD, int DP){

    int posDiagonali = pos / 5;
    int posElementi = pos % 5;

    if(!strcmp(elementi[solMaxDiagonali[0].esercizi[0]].nome, "rondata") && !strcmp(elementi[solMaxDiagonali[0].esercizi[1]].nome, "back_tuck")){
        printf("f");
    }

    if(!strcmp(elementi[solMaxDiagonali[0].esercizi[0]].nome, "rondata") && !strcmp(elementi[solMaxDiagonali[0].esercizi[1]].nome, "back_tuck")){
        if(!strcmp(elementi[solMaxDiagonali[1].esercizi[0]].nome, "front_tuck") && !strcmp(elementi[solMaxDiagonali[1].esercizi[1]].nome, "front_tuck")){
            if(!strcmp(elementi[solMaxDiagonali[2].esercizi[0]].nome, "rondata") && !strcmp(elementi[solMaxDiagonali[2].esercizi[1]].nome, "back_layout_double_twist")){
                printf("mhhh");
            }

        }

    }



    if(posDiagonali > 1 && posElementi == 0 && controlloPruningDiagonali(posDiagonali, contElementiFinali,solDiagonali, elementi )){
        return;
    }

    int i,j;



/*
    for (i = 0; i < 3; ++i) {
        for (j = 0; j <= getElementoFinale(i,contElementiFinali); ++j) {
            printf("%s %d ", elementi[solDiagonali[i].esercizi[j]].nome, elementi[solDiagonali[i].esercizi[j]].difficolta);
        }
        printf("\n");
    }*/

    //SALVATAGGIO SOLUZIONE
    if(controlloFinaleDiagonali(posDiagonali,contElementiFinali ,solDiagonali, elementi, nElementi, DD, DP)){

       double sommaEserciziTotale = calcolaValoreProgramma(contElementiFinali, solDiagonali, elementi);

        //SOLUZIONE MIGLIORE
        if(sommaEserciziTotale > sommaEserciziTotaleMax){
            sommaEserciziTotaleMax = sommaEserciziTotale;

            for (i = 0; i < 3; ++i) {
                solMaxDiagonali[i] = solDiagonali[i];
            }
            contElementiFinaliMax.nElementi_1 = contElementiFinali.nElementi_1;
            contElementiFinaliMax.nElementi_2 = contElementiFinali.nElementi_2;
            contElementiFinaliMax.nElementi_3 = contElementiFinali.nElementi_3;
        }
    }

    salvaElementoFinale(posDiagonali, &contElementiFinali, posElementi);

    if(posDiagonali >= 2 && (posElementi >= 4))
        return;


    for(j = 0; j < nElementi; j++) {
        solDiagonali[posDiagonali].esercizi[posElementi] = j;

        if (controlloPruningElementi(posDiagonali, posElementi, solDiagonali, elementi, nElementi, DD, DP))
            disp_rip_2(pos + 1,contElementiFinali, solDiagonali, solMaxDiagonali, elementi, nElementi, DD, DP);
    }


}
/*
void disp_rip(int pos,int posElementi, nElementiFinale contElementiFinali, diagonale* solDiagonali, diagonale* solMaxDiagonali,elemento* elementi, int nElementi, int DD, int DP){

    if(posElementi >= 5 || elementi[solDiagonali[pos].esercizi[posElementi - 1]].finale == 1 ){

        salvaElementoFinale(pos, &contElementiFinali, posElementi);
        double sommaEserciziTotale;

        if(pos < 2 ){
            disp_rip(pos + 1,posElementi,contElementiFinali,solDiagonali,solMaxDiagonali, elementi, nElementi, DD, DP);
        }
        else if(controlloFinaleDiagonali(pos + 1,contElementiFinali ,solDiagonali, elementi, nElementi, DD, DP)){

            sommaEserciziTotale = calcolaValoreProgramma(contElementiFinali, solDiagonali, elementi);

            //SOLUZIONE MIGLIORE
            if(sommaEserciziTotale > sommaEserciziTotaleMax){
                sommaEserciziTotaleMax = sommaEserciziTotale;

                int i;
                for (i = 0; i < 3; ++i) {
                    solMaxDiagonali[i] = solDiagonali[i];
                }
                contElementiFinaliMax.nElementi_1 = contElementiFinali.nElementi_1;
                contElementiFinaliMax.nElementi_2 = contElementiFinali.nElementi_2;
                contElementiFinaliMax.nElementi_3 = contElementiFinali.nElementi_3;
            }
        }

        return;
    }

    int j;
    for(j = 0; j < nElementi; j++) {
        solDiagonali[pos].esercizi[posElementi] = j;

        if (controlloPruningElementi(pos, posElementi, solDiagonali, elementi, nElementi, DD, DP))
            disp_rip(pos, posElementi + 1,contElementiFinali, solDiagonali, solMaxDiagonali, elementi, nElementi, DD, DP);
    }


}
*/

double calcolaValoreProgramma(nElementiFinale contElementiFinale, diagonale *solDiagonali, elemento *elementi) {
    int i;

    double somma = 0.0;
    for (i = 0; i < 3; ++i) {
        somma += calcolaValoreDiagonale(i,getElementoFinale(i,contElementiFinale),solDiagonali,elementi);
    }

    return somma;
}

void salvaElementoFinale(int posDiagonale, nElementiFinale *contElementiFinali, int posElementi) {
    switch(posDiagonale){
        case 0:
            contElementiFinali->nElementi_1 = posElementi;
            break;
        case 1:
            contElementiFinali->nElementi_2 = posElementi;
            break;
        case 2:
            contElementiFinali->nElementi_3 = posElementi;
            break;
        default:
            printf("\nERRORE\n");
            exit(-1);
    }
}

int getElementoFinale(int pos, nElementiFinale contElementiFinali) {
    switch(pos){
        case 0:
            return contElementiFinali.nElementi_1;
            break;
        case 1:
            return contElementiFinali.nElementi_2;
            break;
        case 2:
            return contElementiFinali.nElementi_3;
            break;
        default:
            printf("\nERRORE\n");
            exit(-1);
    }
}

int controlloPruningDiagonali(int posDiagonale, nElementiFinale contElementiFinali, diagonale *solDiagonali, elemento *elementi){
    int i,j;
    //CONTROLLO ELEMENTI ACROBATICI
    for (i = 0; i < getElementoFinale(posDiagonale,contElementiFinali); ++i) {
        if(elementi[solDiagonali[posDiagonale].esercizi[i]].tipo == 1 || elementi[solDiagonali[posDiagonale].esercizi[i]].tipo == 2)
            return 1;
    }

    return 0;
}

int controlloFinaleDiagonali(int posDiagonale, nElementiFinale contElementiFinali, diagonale *solDiagonali, elemento *elementi, int nElementi, int DD, int DP) {

    int i,j;

    /*
    //CONTROLLO ELEMENTI ACROBATICI
    int ElementiAcrobatici;
    for (i = 0; i < posDiagonale; ++i) {
        ElementiAcrobatici = 0;
        for (j = 0; j < getElementoFinale(i,contElementiFinali) && !ElementiAcrobatici; ++j) {
            if(elementi[solDiagonali[i].esercizi[j]].tipo == 1 || elementi[solDiagonali[i].esercizi[j]].tipo == 2)
                ElementiAcrobatici = 1;
        }

        if(ElementiAcrobatici == 0)
            return 0;
    }
     */

    //CONTROLLO ELEMENTI ACROBATICI AVANTI E INDIETRO
    int ElementiAcrobaticiAvanti = 0;
    int ElementiAcrobaticiIndietro = 0;

    for (i = 0; i <= posDiagonale && (!ElementiAcrobaticiAvanti || !ElementiAcrobaticiIndietro); ++i) {
        for (j = 0; j <= getElementoFinale(i,contElementiFinali) && (!ElementiAcrobaticiAvanti || !ElementiAcrobaticiIndietro); ++j) {
            if (elementi[solDiagonali[i].esercizi[j]].tipo == 1)
                ElementiAcrobaticiIndietro = 1;
            else if (elementi[solDiagonali[i].esercizi[j]].tipo == 2)
                ElementiAcrobaticiAvanti = 1;
        }
    }

    if(ElementiAcrobaticiIndietro == 0 || ElementiAcrobaticiAvanti == 0)
        return 0;

    //CONTROLLO ELEMENTI ACROBATICI IN SEQUENZA
    int ElementiAcrobaticiInSequenza = 0;
    for (i = 0; i <= posDiagonale && !ElementiAcrobaticiInSequenza; ++i) {
        for (j = 1; j <= getElementoFinale(i,contElementiFinali) && !ElementiAcrobaticiInSequenza; ++j) {
            int tipo_el_succ = elementi[solDiagonali[i].esercizi[j]].tipo;
            int tipo_el_prec = elementi[solDiagonali[i].esercizi[j - 1]].tipo;

            if((tipo_el_prec == 1 || tipo_el_prec == 2) && (tipo_el_succ == 1 || tipo_el_succ == 2))
                ElementiAcrobaticiInSequenza = 1;
        }
    }

    if(ElementiAcrobaticiInSequenza == 0)
        return 0;

    int sommaDifficolta = 0;
    for (i = 0; i < posDiagonale; ++i) {
        sommaDifficolta += calcolaDifficoltaDiagonale(i, getElementoFinale(i,contElementiFinali), solDiagonali, elementi);
    }

    if(sommaDifficolta > DP)
        return 0;

    return 1;
}



int controlloPruningElementi(int posDiagonali, int posElementi, diagonale *solDiagonali, elemento *elementi, int nElementi, int DD, int DP) {

    if(elementi[solDiagonali[posDiagonali].esercizi[0]].dirIng != 1)//Primo elemento frontalmente
        return 0;

    //Elemento richiede un elemento precedente
    if(elementi[solDiagonali[posDiagonali].esercizi[0]].reqPrec == 1 && posElementi == 0)
        return 0;

    //Controllo condizione uscita ed ingresso
    if(posElementi > 0 && elementi[solDiagonali[posDiagonali].esercizi[posElementi]].dirIng != elementi[solDiagonali[posDiagonali].esercizi[posElementi - 1]].dirUsc)
        return 0;

    if(calcolaDifficoltaDiagonale(posDiagonali, posElementi, solDiagonali, elementi) > DD)
        return 0;

    return 1;
}

int calcolaDifficoltaDiagonale(int pos, int posElementi, diagonale *solDiagonali, elemento *elementi) {
    int i;
    int difficolta = 0;

    for (i = 0; i <= posElementi; ++i) {
        difficolta += elementi[solDiagonali[pos].esercizi[i]].difficolta;
    }

    return difficolta;
}


double calcolaValoreDiagonale(int pos, int posElementi, diagonale *solDiagonali, elemento *elementi) {
    int i;
    double valore = 0.0;

    for (i = 0; i <= posElementi; ++i) {
        valore += elementi[solDiagonali[pos].esercizi[i]].valore;
    }

    if(pos == 2 && elementi[solDiagonali[pos].esercizi[posElementi - 1]].difficolta >= 8)
        valore *= 1.5;

    return valore;
}


void inputValori(int *DD, int *DP) {
    printf("Inserisci DD: ");
    scanf("%d", DD);
    printf("Inserisci DP: ");
    scanf("%d", DP);
}

elemento *leggiElementiDaFile(int *nElementi) {
    elemento* elementi;

    FILE* fp = fopen(NOME_FILE, "r");
    if(fp == NULL){
        printf("Errore apertura file %s",NOME_FILE);
        exit(-1);
    }

    fscanf(fp,"%d", nElementi);
    elementi = (elemento*)malloc(*nElementi * sizeof(elemento));

    int i;
    for (i = 0; i < *nElementi; ++i) {
        fscanf(fp, "%s", elementi[i].nome);
        fscanf(fp, "%d", &elementi[i].tipo);
        fscanf(fp, "%d", &elementi[i].dirIng);
        fscanf(fp, "%d", &elementi[i].dirUsc);
        fscanf(fp, "%d", &elementi[i].reqPrec);
        fscanf(fp, "%d", &elementi[i].finale);
        fscanf(fp, "%lf", &elementi[i].valore);
        fscanf(fp, "%d", &elementi[i].difficolta);
    }

    return elementi;
}