#include <stdio.h>

#define N_TIPI_GIOIELLI 4

void inputDati(int* n_z,int* n_s,int* n_r,int* n_t, int* val_z, int* val_s, int* val_r, int* val_t, int* maxRipetizioni);
int disp_rip(int pos,int *val,int *sol,int* solMax,int* valoreMassimo,int* lunghSolMassima,int maxRipetizioni, int n,int k,int contGioielli[],int valGioielli[],
             int count);
char* getGioielloByID(int id);
int controllo(int contGioielli[], int sol[],int pos, int maxRipetizioni);
int calcolaValoreCollana(int pos, int *sol, int valGioielli[]);

typedef enum{
    id_zaffiri, id_smeraldi, id_rubini, id_topazi
}id;

int main() {

    int n_z, n_s, n_r, n_t;
    int val_z, val_s, val_r, val_t;
    int maxRipetizioni;

    inputDati(&n_z, &n_s, &n_r, &n_t, &val_z, &val_s, &val_r, &val_t, &maxRipetizioni);

    int k =  n_z + n_s + n_r + n_t;

    /* CONDIZIONI DISPOSIZIONE
     * z - [z r]
     * s - [s t]
     * r - [s t]
     * t - [z r]
     */

    int val[] = {id_zaffiri, id_smeraldi, id_rubini, id_topazi};
    int sol[k], solMax[k];
    int valoreMassimo = 0, lunghSolMassima = 0;;
    int contGioielli[] = {n_z,n_s,n_r,n_t};
    int valGioielli[] = {val_z,val_s,val_r,val_t};

    disp_rip(0,val,sol,solMax,&valoreMassimo,&lunghSolMassima,maxRipetizioni,N_TIPI_GIOIELLI,k,contGioielli,valGioielli,0);

    int i;
    printf("Soluzione massima: ");
    for (i = 0; i < lunghSolMassima; ++i) {
        printf("%s ", getGioielloByID(solMax[i]));
    }
    printf("\n");
    printf("Soluzione ottima di valore %d usando %d gemma/e", valoreMassimo, lunghSolMassima);


    return 0;
}

int disp_rip(int pos,int *val,int *sol,int* solMax,int *valoreMassimo,int* lunghSolMassima,int maxRipetizioni,int n,int k,int contGioielli[],int valGioielli[],
             int count) {
    int i,j, valoreCollana;

    if (pos >= k) {
        return count + 1;
    }

    for (i = 0; i < n; i++) {
        sol[pos] = val[i];

        //CONTROLLO SE LA SOLUZIONE E' VALIDA (PRUNING)
        if (controllo(contGioielli, sol, pos, maxRipetizioni)){

            //SE LA SOLUZIONE E' VALIDA CONTROLLO SE E' SOLUZIONE MIGLIORE
            valoreCollana = calcolaValoreCollana(pos,sol,valGioielli);

            if(valoreCollana >= *valoreMassimo){
                //SE E' SOLUZIONE CON VALORE MASSIMO AGGIORNO LA SOLUZIONE MIGLIORE
                for (j = 0; j <= pos; ++j) {
                    solMax[j] = sol[j];
                }
                *valoreMassimo = valoreCollana;
                *lunghSolMassima = pos + 1;
            }
            count = disp_rip(pos + 1, val, sol, solMax,valoreMassimo,lunghSolMassima,maxRipetizioni, n, k, contGioielli,valGioielli, count);
        }
    }
    return count;
}

int calcolaValoreCollana(int pos, int *sol, int valGioielli[]){
    int valore = 0, i;
    for (i = 0; i <= pos; ++i) {
        valore += valGioielli[sol[i]];
    }

    return valore;
}

int controllo(int contGioielli[], int sol[],int pos,int maxRipetizioni) {
    int i, j, contatore = 0;

    //CONTROLLO NUMERO GIOIELLI
    for (i = 0; i < N_TIPI_GIOIELLI; ++i) {
        contatore = 0;
        for (j = 0; j <= pos; ++j) {
            if (sol[j] == i)
                contatore++;
        }

        if (contatore > contGioielli[i])
            return 0;
    }

    //CONTROLLO POSIZIONI GIOIELLI
    for (i = 0; i < pos; ++i) {
        if (sol[i] == id_zaffiri && !(sol[i + 1] == id_zaffiri || sol[i + 1] == id_rubini))
            return 0;
        if (sol[i] == id_smeraldi && !(sol[i + 1] == id_smeraldi || sol[i + 1] == id_topazi))
            return 0;
        if (sol[i] == id_rubini && !(sol[i + 1] == id_smeraldi || sol[i + 1] == id_topazi))
            return 0;
        if (sol[i] == id_topazi && !(sol[i + 1] == id_zaffiri || sol[i + 1] == id_rubini))
            return 0;
    }

    //CONTROLLO RIPETIZIONI
    contatore = 1;
    for (i = 1; i <= pos ; ++i) {
        if(sol[i] == sol[i-1])
            contatore++;
        else
            contatore = 1;

        if(contatore > maxRipetizioni)
            return 0;
    }

    //CONTROLLO NUMERO ZAFFIRI E NUMERO SMERALDI
    int contZaffiri = 0, contSmeraldi = 0;
    for (i = 0; i <= pos ; ++i) {
        if(sol[i] == id_zaffiri)
            contZaffiri++;
        if(sol[i] == id_smeraldi)
            contSmeraldi++;
    }

    if(contZaffiri > contSmeraldi)
        return 0;

    return 1;
}

char* getGioielloByID(int id){
    switch(id){
        default:
            return "errore";
            break;
        case id_zaffiri:
            return "zaffiri";
            break;
        case id_smeraldi:
            return "smeraldi";
            break;
        case id_topazi:
            return "topazi";
            break;
        case id_rubini:
            return "rubini";
            break;
    }
}

void inputDati(int* n_z,int* n_s,int* n_r,int* n_t, int* val_z, int* val_s, int* val_r, int* val_t, int* maxRipetizioni){
    printf("Inserisci numero zaffiri: ");
    scanf("%d", n_z);
    printf("Inserisci valore zaffiri: ");
    scanf("%d", val_z);
    printf("Inserisci numero rubini: ");
    scanf("%d", n_r);
    printf("Inserisci valore rubini: ");
    scanf("%d", val_r);
    printf("Inserisci numero topazi: ");
    scanf("%d", n_t);
    printf("Inserisci valore topazi: ");
    scanf("%d", val_t);
    printf("Inserisci numero smeraldi: ");
    scanf("%d", n_s);
    printf("Inserisci valore smeraldi: ");
    scanf("%d", val_s);

    printf("Inserisci numero massimo ripetizioni: ");
    scanf("%d", maxRipetizioni);
}
