#include <stdio.h>
#include <stdlib.h>
#define FILENAME "elementi.txt"

typedef struct{
    char nome[100];
    int tipologia;
    int dirIng;
    int dirUsc;
    int reqPrec;
    int finale;
    float valore;
    int difficolta;
}esercizio;

typedef struct{
    int numeroEs;
    esercizio esercizi[5];
    int difficolta;
    float valore;
}diagonale;

void LeggiFile(int *num_diag,esercizio **esercizi);
int controlloPruning(int indice_es,esercizio *sol,int pos,esercizio *esercizi,int DD,int DP);
void GeneraDiagonali(diagonale** diagonali,esercizio *sol,esercizio* esercizi,int pos,int es_max,int num_es,int DD,int DP,int *num_diag);
void MemorizzaDiagonale(diagonale** diagonali,int num_diag,esercizio* sol,int esercizi);
int CalcolaDifficolta(esercizio *sol,int esercizi);
void DiagonaliMigliori(diagonale* diagonali,int num_diag,diagonale* sol,diagonale* sol_temp,int pos,int k,float *max_diff,int DP);
int CheckMigliore(diagonale* sol_temp,float *max_diff);
int Acrobazia(esercizio *sol,int pos);
int Difficolta(diagonale* sol_temp,int pos,diagonale diagonale_successiva,int DP);
int Acrobazie(diagonale *sol_temp);
float CalcolaValore(esercizio *sol,int esercizi);
void OrdinaDiagonali(diagonale* diagonali,int num_diag);
void initVettori(diagonale **diagonali, esercizio **sol, diagonale **sol_diag, diagonale **sol_temp);
void stampaDiagonaleMax(float max_diff, const diagonale *sol_diag);

int main() {
    int num_es, num_diag = 0;
    int DD, DP;
    float max_diff = 0;

    esercizio *esercizi;
    diagonale *diagonali;
    esercizio *sol;
    diagonale *sol_diag;
    diagonale *sol_temp;

    initVettori(&diagonali, &sol, &sol_diag, &sol_temp);

    printf("Inserire DD intero : ");
    scanf("%d", &DD);
    printf("Inserire DP intero : ");
    scanf("%d", &DP);

    LeggiFile(&num_es, &esercizi);
    GeneraDiagonali(&diagonali, sol, esercizi, 0, 5, num_es, DD, DP, &num_diag);
    OrdinaDiagonali(diagonali, num_diag);
    DiagonaliMigliori(diagonali, num_diag, sol_diag, sol_temp, 0, 3, &max_diff, DP);

    stampaDiagonaleMax(max_diff, sol_diag);

    return 0;
}

void GeneraDiagonali(diagonale** diagonali,esercizio *sol,esercizio* esercizi,int pos,int es_max,int num_es,int DD,int DP,int *num_diag) {

    if (pos >= es_max || (pos > 0 && sol[pos - 1].finale == 1))
        return;

    int i;
    for (i = 0; i < num_es; i++) {
        if (controlloPruning(i, sol, pos, esercizi, DD, DP)) {

            sol[pos] = esercizi[i];
            if (Acrobazia(sol, pos)) {
                MemorizzaDiagonale(diagonali, *num_diag, sol, pos + 1);
                (*num_diag)++;
            }
            GeneraDiagonali(diagonali, sol, esercizi, pos + 1, es_max, num_es, DD, DP, num_diag);
        }
    }
}

int controlloPruning(int indice_es,esercizio *sol,int pos,esercizio *esercizi,int DD,int DP) {
    int difficolta;

    if (pos == 0) {
        if (esercizi[indice_es].reqPrec == 0 && esercizi[indice_es].dirIng == 1 &&
            esercizi[indice_es].difficolta <= DD && esercizi[indice_es].difficolta <= DP)
            return 1;
        else return 0;
    }

    difficolta = CalcolaDifficolta(sol, pos) + esercizi[indice_es].difficolta;
    if (esercizi[indice_es].dirIng == sol[pos - 1].dirUsc && difficolta <= DD && difficolta <= DP)
        return 1;

    return 0;
}

void stampaDiagonaleMax(float max_diff, const diagonale *sol_diag) {
    int i,j;
    printf("Diagonali:\n");

    for (i = 0; i < 3; i++) {
        for (j = 0; j < sol_diag[i].numeroEs; j++)
            printf("%s ", sol_diag[i].esercizi[j].nome);
        printf("\n");
    }
    printf("%f", max_diff);
}

void initVettori(diagonale **diagonali, esercizio **sol, diagonale **sol_diag, diagonale **sol_temp) {
    (*diagonali) = malloc(sizeof(diagonale));
    (*sol) = malloc(5 * sizeof(esercizio));
    (*sol_diag) = malloc(3 * sizeof(diagonale));
    (*sol_temp) = malloc(3 * sizeof(diagonale));
}


int CalcolaDifficolta(esercizio *sol,int esercizi) {
    int i, difficoltaTotale = 0;

    for (i = 0; i < esercizi; i++)
        difficoltaTotale += sol[i].difficolta;

    return difficoltaTotale;
}

float CalcolaValore(esercizio *sol,int esercizi) {
    int i;
    float valoreTotale = 0;

    for (i = 0; i < esercizi; i++)
        valoreTotale += sol[i].valore;
    return valoreTotale;
}

int Acrobazia(esercizio *sol,int pos){
    int i;

    for(i=0;i<=pos;i++){
        if(sol[i].tipologia==2 || sol[i].tipologia==1)
            return 1;
    }
    return 0;
}

int Acrobazie(diagonale *sol_temp) {
    int i, j, acrobazia_avanti = 0, acrobazia_indietro = 0, sequenza_acrobazie = 0;

    for (i = 0; i < 3; i++) {
        for (j = 0; j < sol_temp[i].numeroEs; j++) {
            if (acrobazia_avanti == 0 && sol_temp[i].esercizi[j].tipologia == 2)
                acrobazia_avanti = 1;
            else {
                if (acrobazia_indietro == 0 && sol_temp[i].esercizi[j].tipologia == 1)
                    acrobazia_indietro = 1;
            }
            if (sequenza_acrobazie == 0 && j > 0) {
                if ((sol_temp[i].esercizi[j].tipologia == 2 || sol_temp[i].esercizi[j].tipologia == 1) &&
                    (sol_temp[i].esercizi[j - 1].tipologia == 2 || sol_temp[i].esercizi[j - 1].tipologia == 1))
                    sequenza_acrobazie = 1;
            }

        }
    }
    if (acrobazia_avanti && acrobazia_indietro && sequenza_acrobazie)
        return 1;
    return 0;
}

void MemorizzaDiagonale(diagonale** diagonali,int num_diag,esercizio* sol,int es_diag) {
    int i;

    if (num_diag)
        *diagonali = (diagonale *) realloc(*diagonali, (num_diag * 2) * sizeof(diagonale));

    for (i = 0; i < es_diag; i++)
        (*diagonali)[num_diag].esercizi[i] = sol[i];
    (*diagonali)[num_diag].numeroEs = es_diag;
    (*diagonali)[num_diag].difficolta = CalcolaDifficolta(sol, es_diag);
    (*diagonali)[num_diag].valore = CalcolaValore(sol, es_diag);

    return;
}

void OrdinaDiagonali(diagonale* diagonali,int num_diag) {
    int i, j;
    diagonale tmp;
    float rapporto1, rapporto2;

    for (i = 0; i < num_diag; i++) {
        for (j = 0; j < num_diag - i + 1; j++) {
            rapporto1 = diagonali[j].valore / diagonali[j].difficolta;
            rapporto2 = diagonali[j + 1].valore / diagonali[j + 1].difficolta;
            if (rapporto1 < rapporto2) {
                tmp = diagonali[j];
                diagonali[j] = diagonali[j + 1];
                diagonali[j + 1] = tmp;
            }
        }
    }
    return;
}

void DiagonaliMigliori(diagonale* diagonali,int num_diag,diagonale* sol,diagonale* sol_temp,int pos,int k,float *max_diff,int DP) {
    int i, j;

    if (pos > k - 1) {
        if (Acrobazie(sol_temp))
            if (CheckMigliore(sol_temp, max_diff))
                for (j = 0; j < pos; j++)
                    sol[j] = sol_temp[j];
        return;
    }

    for (i = 0; i < num_diag; i++) {
        if (Difficolta(sol_temp, pos, diagonali[i], DP)) {
            sol_temp[pos] = diagonali[i];
            DiagonaliMigliori(diagonali, num_diag, sol, sol_temp, pos + 1, k, max_diff, DP);
        }
    }
    return;
}

int Difficolta(diagonale* sol_temp,int pos,diagonale diagonale_successiva,int DP) {
    int i, diff = 0;

    for (i = 0; i < pos; i++)
        diff += sol_temp[i].difficolta;

    if (diff + diagonale_successiva.difficolta > DP)
        return 0;
    return 1;
}

int CheckMigliore(diagonale* sol_temp,float *max_diff) {
    int i, j;
    float s = 0, max_sol_temp = 0;

    for (i = 0; i < 3; i++)
        if (i != 2)
            for (j = 0; j < sol_temp[i].numeroEs; j++)
                max_sol_temp += (sol_temp[i].esercizi[j].valore);
        else if (sol_temp[i].esercizi[(sol_temp[i].numeroEs) - 1].difficolta >= 8) {
            for (j = 0; j < sol_temp[i].numeroEs; j++)
                s += (sol_temp[i].esercizi[j].valore);
            s *= 1.5;
            max_sol_temp += s;
        } else
            for (j = 0; j < sol_temp[i].numeroEs; j++)
                max_sol_temp += (sol_temp[i].esercizi[j].valore);

    if (max_sol_temp > *max_diff) {
        *max_diff = max_sol_temp;
        return 1;
    }
    return 0;
}

void LeggiFile(int *num_diag,esercizio **esercizi) {
    FILE *f;
    int i;
    esercizio *esercizi;

    f = fopen(FILENAME, "r");

    if (f == NULL) {
        printf("Errore apertura file %s", FILENAME);
        exit(-1);
    }

    fscanf(f, "%d", num_diag);
    esercizi = malloc(*num_diag * sizeof(esercizio));
    for (i = 0; i < *num_diag; i++)
        fscanf(f, "%s %d %d %d %d %d %f %d", esercizi[i].nome, &esercizi[i].tipologia, &esercizi[i].dirIng,
               &esercizi[i].dirUsc, &esercizi[i].reqPrec, &esercizi[i].finale, &esercizi[i].valore,
               &esercizi[i].difficolta);

    *esercizi = esercizi;
}