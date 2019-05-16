#include <stdio.h>

#define N_TIPI_GIOIELLI 4

void inputDati(int* n_z,int* n_s,int* n_r,int* n_t);
int disp_rip(int pos,int *val,int *sol,int* solMax,int* lunghSolMassima,int n,int k,int contGioielli[],int count);
char* getGioielloByID(int id);
int controllo(int contGioielli[], int sol[],int pos);

typedef enum{
    id_zaffiri, id_smeraldi, id_rubini, id_topazi
}id;

int main() {

    int n_z, n_s, n_r, n_t;

    inputDati(&n_z, &n_s, &n_r, &n_t);

    int k =  n_z + n_s + n_r + n_t;

    /* CONDIZIONI DISPOSIZIONE
     * z - [z r]
     * s - [s t]
     * r - [s t]
     * t - [z r]
     */

    int val[] = {id_zaffiri, id_smeraldi, id_rubini, id_topazi};
    int sol[k], solMax[k];
    int lunghSolMassima = 0;
    int contGioielli[] = {n_z,n_s,n_r,n_t};

    disp_rip(0,val,sol,solMax,&lunghSolMassima,N_TIPI_GIOIELLI,k,contGioielli,0);

    int i;
    printf("Soluzione massima: ");
    for (i = 0; i < lunghSolMassima; ++i) {
        printf("%s ", getGioielloByID(solMax[i]));
    }
    printf("\n");
    printf("Soluzione ottima di lunghezza %d", lunghSolMassima);


    return 0;
}

int disp_rip(int pos,int *val,int *sol,int* solMax,int* lunghSolMassima,int n,int k,int contGioielli[],int count) {
    int i,j;

    if (pos >= k) {
        return count + 1;
    }

    for (i = 0; i < n; i++) {
        sol[pos] = val[i];

        //CONTROLLO SE LA SOLUZIONE E' VALIDA (PRUNING)
        if (controllo(contGioielli, sol, pos)){

            if((pos + 1) > *lunghSolMassima){
                //SE E' SOLUZIONE CON LUNGHEZZA MASSIMA AGGIORNO LA SOLUZIONE MIGLIORE
                for (j = 0; j <= pos; ++j) {
                    solMax[j] = sol[j];
                }
                *lunghSolMassima = pos + 1;
            }
            count = disp_rip(pos + 1, val, sol, solMax,lunghSolMassima, n, k, contGioielli, count);
        }
    }
    return count;
}

int controllo(int contGioielli[], int sol[],int pos) {
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
