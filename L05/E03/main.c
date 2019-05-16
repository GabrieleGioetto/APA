#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LUNG_CODICE 7
#define MAX_LUNG_STRINGA 31
#define MAX_LUNG_DATA 15
#define MAX_LUNG_ORA 9

typedef enum{
    r_stampa, r_data,r_codice, r_partenza, r_destinazione, r_ricerca, r_lettura,r_fine
}comando;

typedef struct{
    char codice[MAX_LUNG_CODICE];
    char partenza[MAX_LUNG_STRINGA];
    char destinazione[MAX_LUNG_STRINGA];
    char data[MAX_LUNG_DATA];
    char oraPartenza[MAX_LUNG_ORA];
    char oraArrivo[MAX_LUNG_ORA];
    int ritardo;
}tratta;

//Struttura per salvare se un'ordinamento è già stato fatto
typedef struct{
    int ordinamentoData;
    int ordinamentoCodice;
    int ordinamentoPartenza;
    int ordinamentoDestinazione;
}ControlloOrdinamento;

tratta* leggiFile(int* nTratte,ControlloOrdinamento* controllo, tratta*** ordinamentoData,tratta*** ordinamentoCodice,tratta*** ordinamentoPartenza,tratta*** ordinamentoDestinazione);
void selezioneComando(tratta** tratte, int* nTratte,ControlloOrdinamento* controllo, comando codiceComando,tratta* ordinamentoData[],tratta* ordinamentoCodice[],tratta* ordinamentoPartenza[],tratta* ordinamentoDestinazione[]);
void stampa(FILE* dest,tratta* tratte, int nTratte);
void stampaP(FILE* dest,tratta** tratte, int nTratte);
void MergeSortR(char **A, char **B, int l, int r, tratta* ordinamento[], tratta* ordinamentoB[]) ;
void MergeSort(char **A, int N, tratta* ordinamento[]);
void Merge(char **A, char **B, int l, int q, int r, tratta* ordinamento[], tratta* ordinamentoB[]);
comando leggiComando();
tratta** inizializzaVettorePuntatori(tratta* tratte, int nTratte);
int ricercaDicotomica(tratta* tratte[], int l, int r, char* stazionePartenza);
void ricercaLineare(tratta tratte[], int nTratte, char* stazionePartenza);
void ricercaStazione(ControlloOrdinamento* controllo,tratta tratte[],tratta** ordinamentoPartenza,int nTratte);
void dealloca(tratta** tratte, tratta* ordinamentoData[],tratta* ordinamentoCodice[],tratta* ordinamentoPartenza[],tratta* ordinamentoDestinazione[]);

int main() {

    //Vettori in cui salvo gli ordinamenti
    tratta **ordinamentoData;
    tratta **ordinamentoCodice;
    tratta **ordinamentoPartenza;
    tratta **ordinamentoDestinazione;

    ControlloOrdinamento controllo;;//Struttura per controllare se un ordinamento è già stato creato

    int nTratte;
    //Salvo le tratte leggendole dal file
    tratta *tratte = leggiFile(&nTratte, &controllo, &ordinamentoData, &ordinamentoCodice, &ordinamentoPartenza,
                               &ordinamentoDestinazione);

    comando codiceComando = r_stampa;

    while (codiceComando != r_fine) {
        codiceComando = leggiComando();

        selezioneComando(&tratte, &nTratte, &controllo, codiceComando, ordinamentoData, ordinamentoCodice,
                         ordinamentoPartenza, ordinamentoDestinazione);
    }

    return 0;
}

tratta** inizializzaVettorePuntatori(tratta* tratte, int nTratte) {

    tratta **vettoreP = (tratta **) malloc(sizeof(tratta *) * nTratte);
    int i;
    for (i = 0; i < nTratte; ++i) {
        vettoreP[i] = &tratte[i];
    }

    return vettoreP;
}

void selezioneComando(tratta** tratte, int* nTratte,ControlloOrdinamento* controllo, comando codiceComando,tratta* ordinamentoData[],tratta* ordinamentoCodice[],tratta* ordinamentoPartenza[],tratta* ordinamentoDestinazione[]) {

    char **vettoreStringhe;//Vettore che uso per i confronti
    vettoreStringhe = (char **) malloc(sizeof(char *) * (*nTratte));

    int i;

    switch (codiceComando) {
        case r_stampa:// Stampa a video con l'ordinamento iniziale
            stampa(stdout, *tratte, *nTratte);
            break;
        case r_data:
            if (!controllo->ordinamentoData) { //Se il vettore non è stato ancora ordinato per data

                for (i = 0; i < *nTratte; ++i) { //Carico vettore stringhe con le date delle tratte

                    // Per controllare la data e l'ora creo un'unica stringa composta da data + ora
                    vettoreStringhe[i] = malloc(strlen(ordinamentoData[i]->data) + strlen(ordinamentoData[i]->oraPartenza) + 1);
                    strcpy(vettoreStringhe[i], ordinamentoData[i]->data);
                    strcat(vettoreStringhe[i], ordinamentoData[i]->oraPartenza);
                }

                //Ordino orientamentoData in base al vettoreStringhe(in questo caso composto da date)
                MergeSort(vettoreStringhe, *nTratte,ordinamentoData);

                controllo->ordinamentoData = 1;
            }

            //Stampo a video con ordinamento per data
            stampaP(stdout, ordinamentoData, *nTratte);
            break;
        case r_codice:
            if (!controllo->ordinamentoCodice) {
                for (i = 0; i < *nTratte; ++i) {
                    //Passo a vettoreStringhe il puntatore alla prima cella del codice(cioè una stringa) della tratta puntata da ordinamentoCodice[i]
                    vettoreStringhe[i] = &ordinamentoCodice[i]->codice[0];
                }
                MergeSort(vettoreStringhe, *nTratte, ordinamentoCodice);

                controllo->ordinamentoCodice = 1;
            }
            stampaP(stdout, ordinamentoCodice, *nTratte);
            break;
        case r_partenza:
            if (!controllo->ordinamentoPartenza) {
                for (i = 0; i < *nTratte; ++i) {
                    vettoreStringhe[i] = &ordinamentoPartenza[i]->partenza[0];
                }
                MergeSort(vettoreStringhe, *nTratte, ordinamentoPartenza);

                controllo->ordinamentoPartenza = 1;
            }
            stampaP(stdout, ordinamentoPartenza, *nTratte);
            break;
        case r_destinazione:
            if (!controllo->ordinamentoDestinazione) {
                for (i = 0; i < *nTratte; ++i) {
                    vettoreStringhe[i] = &ordinamentoDestinazione[i]->destinazione[0];
                }
                MergeSort(vettoreStringhe, *nTratte, ordinamentoDestinazione);

                controllo->ordinamentoDestinazione = 1;
            }

            stampaP(stdout, ordinamentoDestinazione, *nTratte);
            break;
        case r_ricerca:
            ricercaStazione(controllo,*tratte,ordinamentoPartenza,*nTratte);
            break;
        case r_lettura:
            //Dealloco tutti i vettori prima della lettura del nuovo file
            dealloca(tratte, ordinamentoData, ordinamentoCodice, ordinamentoPartenza, ordinamentoDestinazione) ;

            //Leggo nuovo file e salvo nuovo vettore tratte
            *tratte = leggiFile(nTratte, controllo, &ordinamentoData, &ordinamentoCodice, &ordinamentoPartenza,
                                &ordinamentoDestinazione);
            break;
        case r_fine:
            dealloca(tratte, ordinamentoData, ordinamentoCodice, ordinamentoPartenza, ordinamentoDestinazione) ;
            break;

    }
}


void dealloca(tratta** tratte, tratta* ordinamentoData[],tratta* ordinamentoCodice[],tratta* ordinamentoPartenza[],tratta* ordinamentoDestinazione[]){
    free(*tratte);
    free(ordinamentoCodice);
    free(ordinamentoData);
    free(ordinamentoPartenza);
    free(ordinamentoDestinazione);

}

void ricercaStazione(ControlloOrdinamento* controllo,tratta tratte[],tratta** ordinamentoPartenza,int nTratte){
    char stazione[30];
    int indiceRicercaStazione;

    printf("Inserisci nome stazione di partenza: ");
    scanf("%s", stazione);

    //Se le tratte sono già state ordinate per la stazione di partenza uso la ricerca Dicotomica, altrimenti uso la lineare
    if (controllo->ordinamentoPartenza) {

        indiceRicercaStazione = ricercaDicotomica(ordinamentoPartenza, 0, nTratte - 1, stazione);
        if(indiceRicercaStazione == -1)
            printf("Nessuna tratta trovata con stazione di partenza %s",stazione);
        else
            stampaP(stdout,ordinamentoPartenza + indiceRicercaStazione,1);

    } else {
        ricercaLineare(tratte, nTratte, stazione);
    }

}

int ricercaDicotomica(tratta* tratte[], int l, int r, char* stazionePartenza){
    int m;

    if(l > r)
        return -1;

    m = (l+r)/2;

    if(strstr(tratte[m]->partenza,stazionePartenza) != NULL)
        return m;

    if(strcmp(tratte[m]->partenza,stazionePartenza) > 0)
        return ricercaDicotomica(tratte,l,m-1,stazionePartenza);

    return ricercaDicotomica(tratte,m+1,r,stazionePartenza);
}

void ricercaLineare(tratta tratte[], int nTratte, char* stazionePartenza){
    int i,trovato = 0;
    for (i = 0; i < nTratte; ++i) {
        if(strstr(tratte[i].partenza,stazionePartenza) != NULL){
            //Passo puntatore alla i-esima cella con lunghezza vettore uguale ad uno
            //in modo da stampare solo la tratta in questione
            stampa(stdout,tratte + i,1);
            trovato = 1;
        }
    }

    if(!trovato)
        printf("Nessuna tratta trovata con stazione di partenza %s",stazionePartenza);
}

void stampaP(FILE* dest,tratta** tratte, int nTratte) {
    int i;
    for (i = 0; i < nTratte; ++i) {
        fprintf(dest, "%s %s %s %s %s %s %d\n", tratte[i]->codice, tratte[i]->partenza, tratte[i]->destinazione,
                tratte[i]->data, tratte[i]->oraPartenza, tratte[i]->oraArrivo, tratte[i]->ritardo);
    }
}


void stampa(FILE* dest,tratta* tratte, int nTratte){
    int i;
    for (i = 0; i < nTratte; ++i) {
        fprintf(dest, "%s %s %s %s %s %s %d\n",tratte[i].codice,tratte[i].partenza,tratte[i].destinazione,
                tratte[i].data,tratte[i].oraPartenza,tratte[i].oraArrivo,tratte[i].ritardo);
    }
}

comando leggiComando(){
    char cmd[20];
    comando c;

    char tabella[][20]={
            "stampa","data","codice","partenza",
            "destinazione","ricerca","lettura","fine"
    };

    printf("Inserisci comando ( stampa | data | codice | partenza | destinazione | ricerca | lettura | fine ): ");
    scanf("%s", cmd);

    c = r_stampa;

    while(c < r_fine && strcmp(cmd,tabella[c]) != 0)
        c++;

    return c;
}

void Merge(char **A, char **B, int l, int q, int r, tratta* ordinamento[], tratta* ordinamentoB[]) {
    int i, j, k;
    i = l;
    j = q + 1;
    for (k = l; k <= r; k++)
        if (i > q) {
            ordinamentoB[k] = ordinamento[j];
            B[k] = A[j++];
        } else if (j > r) {
            ordinamentoB[k] = ordinamento[i];
            B[k] = A[i++];
        } else if (strcmp(A[i], A[j]) < 0 || !strcmp(A[i], A[j])) {
            ordinamentoB[k] = ordinamento[i];
            B[k] = A[i++];
        } else {
            ordinamentoB[k] = ordinamento[j];
            B[k] = A[j++];
        }

    for (k = l; k <= r; k++) {
        A[k] = B[k];
        ordinamento[k] = ordinamentoB[k];
    }
}

void MergeSortR(char **A, char **B, int l, int r, tratta* ordinamento[], tratta* ordinamentoB[]) {
    int q;
    if (r <= l)
        return;
    q = (l + r) / 2;
    MergeSortR(A, B, l, q, ordinamento, ordinamentoB);
    MergeSortR(A, B, q + 1, r, ordinamento, ordinamentoB);
    Merge(A, B, l, q, r, ordinamento, ordinamentoB);
}

void MergeSort(char **A, int N, tratta* ordinamento[]) {
    int l = 0, r = N - 1;
    char **B = (char **) malloc(N * sizeof(char *));
    tratta **ordinamentoB = (tratta **) malloc(N * sizeof(tratta *));

    if (B == NULL) {
        printf("Memory allocation error\n");
        exit(1);
    }
    MergeSortR(A, B, l, r, ordinamento, ordinamentoB);
}

tratta* leggiFile(int* nTratte,ControlloOrdinamento* controllo, tratta*** ordinamentoData,tratta*** ordinamentoCodice,tratta*** ordinamentoPartenza,tratta*** ordinamentoDestinazione) {
    char nomeFile[30];
    printf("Inserire nome file da leggere: ");
    scanf("%s", nomeFile);

    FILE *fp = fopen(nomeFile, "r");

    if (fp == NULL) {
        printf("Errore lettura file");
        exit(-1);
    }

    fscanf(fp, "%d", nTratte);

    //Alloco nuovo vettore tratte di lunghezza nTratte
    tratta *tratte = (tratta *) malloc(sizeof(tratta) * (*nTratte));

    int i = 0;

    //Leggo tratte da file
    while (fscanf(fp, "%s %s %s %s %s %s %d", tratte[i].codice, tratte[i].partenza, tratte[i].destinazione,
                  tratte[i].data, tratte[i].oraPartenza, tratte[i].oraArrivo, &tratte[i].ritardo) != EOF) {
        i++;
    }

    fclose(fp);

    //Inizializzo i vettori dei puntatori facendoli puntare alle tratte con l'ordinamento iniziale(quello del file)
    *ordinamentoData = inizializzaVettorePuntatori(tratte, *nTratte);
    *ordinamentoCodice = inizializzaVettorePuntatori(tratte, *nTratte);
    *ordinamentoPartenza = inizializzaVettorePuntatori(tratte, *nTratte);
    *ordinamentoDestinazione = inizializzaVettorePuntatori(tratte, *nTratte);

    //Inizializzo struttura per controllare se un ordinamento è già stato creato
    //All'inizio nessun ordinamento è stato fatto
    controllo->ordinamentoData = 0;
    controllo->ordinamentoCodice = 0;
    controllo->ordinamentoPartenza = 0;
    controllo->ordinamentoDestinazione = 0;

    return tratte;
}