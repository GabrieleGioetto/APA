#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXRIGHE 1000
#define MAX_LUNG_CODICE 7
#define MAX_LUNG_STRINGA 31
#define MAX_LUNG_DATA 15
#define MAX_LUNG_ORA 9
#define NOME_FILE "tratte.txt"

typedef enum{
    r_stampa, r_data,r_codice, r_partenza, r_destinazione, r_ricerca, r_fine
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

typedef struct{
    int ordinamentoData;
    int ordinamentoCodice;
    int ordinamentoPartenza;
    int ordinamentoDestinazione;
}ControlloOrdinamento;

int leggiFile(tratta tratte[MAXRIGHE]);
void selezioneComando(tratta tratte[MAXRIGHE], int nTratte,ControlloOrdinamento* controllo, comando codiceComando,tratta* ordinamentoData[],tratta* ordinamentoCodice[],tratta* ordinamentoPartenza[],tratta* ordinamentoDestinazione[]);
void stampa(FILE* dest,tratta tratte[MAXRIGHE], int nTratte);
void stampaP(FILE* dest,tratta** tratte, int nTratte);
void MergeSortR(char **A, char **B, int l, int r, tratta* ordinamento[], tratta* ordinamentoB[]) ;
void MergeSort(char **A, int N, tratta* ordinamento[]);
void Merge(char **A, char **B, int l, int q, int r, tratta* ordinamento[], tratta* ordinamentoB[]);
comando leggiComando();
void inizializzaVettorePuntatori(tratta tratte[], int nTratte, tratta* vettoreP[]);
int ricercaDicotomica(tratta* tratte[], int l, int r, char* stazionePartenza);
void ricercaLineare(tratta tratte[], int nTratte, char* stazionePartenza);
void ricercaStazione(ControlloOrdinamento* controllo,tratta tratte[],tratta** ordinamentoPartenza,int nTratte);

int main() {
    tratta tratte[MAXRIGHE];

    int nTratte;
    if( !(nTratte = leggiFile(tratte))){
        printf("Errore apertura file %s", NOME_FILE);
        exit(-1);
    }

    comando codiceComando = r_stampa;

    //Vettori in cui salvo gli ordinamenti
    tratta* ordinamentoData[nTratte];
    tratta* ordinamentoCodice[nTratte];
    tratta* ordinamentoPartenza[nTratte];
    tratta* ordinamentoDestinazione[nTratte];

    //Inizializzo i vettori dei puntatori facendoli puntare alle tratte con l'ordinamento iniziale(quello del file)
    inizializzaVettorePuntatori(tratte,nTratte,ordinamentoData);
    inizializzaVettorePuntatori(tratte,nTratte,ordinamentoCodice);
    inizializzaVettorePuntatori(tratte,nTratte,ordinamentoPartenza);
    inizializzaVettorePuntatori(tratte,nTratte,ordinamentoDestinazione);

    //Struttura per controllare se un ordinamento è già stato creato
    ControlloOrdinamento controllo = {0,0,0,0};

    while(codiceComando != r_fine){
        codiceComando = leggiComando();

        selezioneComando(tratte, nTratte, &controllo,codiceComando,ordinamentoData,ordinamentoCodice,ordinamentoPartenza,ordinamentoDestinazione);
    }

    return 0;
}

void inizializzaVettorePuntatori(tratta tratte[], int nTratte, tratta* vettoreP[]){
    int i;
    for (i = 0; i < nTratte; ++i) {
        vettoreP[i] = &tratte[i];
    }
}

void selezioneComando(tratta tratte[MAXRIGHE], int nTratte,ControlloOrdinamento* controllo, comando codiceComando,tratta* ordinamentoData[],tratta* ordinamentoCodice[],tratta* ordinamentoPartenza[],tratta* ordinamentoDestinazione[]) {

    char *vettoreStringhe[MAXRIGHE];//Vettore che uso per i confronti
    int i;

    switch (codiceComando) {
        case r_stampa:// Stampa a video con l'ordinamento iniziale
            stampa(stdout, tratte, nTratte);
            break;
        case r_data:
            if (!controllo->ordinamentoData) { //Se il vettore non è stato ancora ordinato per data

                for (i = 0; i < nTratte; ++i) { //Carico vettore stringhe con le date delle tratte
                    vettoreStringhe[i] = malloc(strlen(ordinamentoData[i]->data) + strlen(ordinamentoData[i]->oraPartenza) + 1); // Per controllare data + ora
                    strcpy(vettoreStringhe[i], ordinamentoData[i]->data);
                    strcat(vettoreStringhe[i], ordinamentoData[i]->oraPartenza);

                }
                MergeSort(vettoreStringhe, nTratte,
                          ordinamentoData);//Ordino orientamentoData in base al vettoreStringhe(in questo caso date)

                controllo->ordinamentoData = 1;
            }

            stampaP(stdout, ordinamentoData, nTratte);//Stampo a video con ordinamento per data
            break;
        case r_codice:
            if (!controllo->ordinamentoCodice) {
                for (i = 0; i < nTratte; ++i) {
                    //Passo a vettoreStringhe il puntatore alla prima cella del codice(cioè una stringa) della tratta puntata da ordinamentoCodice[i]
                    vettoreStringhe[i] = &ordinamentoCodice[i]->codice[0];
                }
                MergeSort(vettoreStringhe, nTratte, ordinamentoCodice);

                controllo->ordinamentoCodice = 1;
            }
            stampaP(stdout, ordinamentoCodice, nTratte);
            break;
        case r_partenza:
            if (!controllo->ordinamentoPartenza) {
                for (i = 0; i < nTratte; ++i) {
                    vettoreStringhe[i] = &ordinamentoPartenza[i]->partenza[0];
                }
                MergeSort(vettoreStringhe, nTratte, ordinamentoPartenza);

                controllo->ordinamentoPartenza = 1;
            }
            stampaP(stdout, ordinamentoPartenza, nTratte);
            break;
        case r_destinazione:
            if (!controllo->ordinamentoDestinazione) {
                for (i = 0; i < nTratte; ++i) {
                    vettoreStringhe[i] = &ordinamentoDestinazione[i]->destinazione[0];
                }
                MergeSort(vettoreStringhe, nTratte, ordinamentoDestinazione);

                controllo->ordinamentoDestinazione = 1;
            }

            stampaP(stdout, ordinamentoDestinazione, nTratte);
            break;
        case r_ricerca:
            ricercaStazione(controllo,tratte,ordinamentoPartenza,nTratte);
            break;
        case r_fine:
            break;

    }
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

void stampaP(FILE* dest,tratta** tratte, int nTratte){
    int i;
    for (i = 0; i < nTratte; ++i) {
        fprintf(dest, "%s %s %s %s %s %s %d\n",tratte[i]->codice,tratte[i]->partenza,tratte[i]->destinazione,
                tratte[i]->data,tratte[i]->oraPartenza,tratte[i]->oraArrivo,tratte[i]->ritardo);
    }
}


void stampa(FILE* dest,tratta tratte[], int nTratte){
    int i;
    for (i = 0; i < nTratte; ++i) {
        fprintf(dest, "%s %s %s %s %s %s %d\n",tratte[i].codice,tratte[i].partenza,tratte[i].destinazione,
                tratte[i].data,tratte[i].oraPartenza,tratte[i].oraArrivo,tratte[i].ritardo);
    }
}

comando leggiComando(){
    char cmd[20];
    comando c;

    char tabella[7][20]={
            "stampa","data","codice","partenza",
            "destinazione","ricerca","fine"
    };

    printf("Inserisci comando ( stampa | data | codice | partenza | destinazione | ricerca | fine ): ");
    scanf("%s", cmd);

    c = r_stampa;

    while(c < r_fine && strcmp(cmd,tabella[c]) != 0)
        c++;

    return c;
}

void Merge(char **A, char **B, int l, int q, int r, tratta* ordinamento[], tratta* ordinamentoB[]) {
    int i, j, k;
    i = l;
    j = q+1;
    for(k = l; k <= r; k++)
        if (i > q){
            ordinamentoB[k] = ordinamento[j];
            B[k] = A[j++];
        }
        else if (j > r){
            ordinamentoB[k] = ordinamento[i];
            B[k] = A[i++];
        }
        else if (strcmp(A[i], A[j]) < 0 || !strcmp(A[i], A[j])  ){
            ordinamentoB[k] = ordinamento[i];
            B[k] = A[i++];
        }
        else{
            ordinamentoB[k] = ordinamento[j];
            B[k] = A[j++];
        }

    for ( k = l; k <= r; k++ ){
        A[k] = B[k];
        ordinamento[k] = ordinamentoB[k];
    }

}

void MergeSortR(char **A, char **B, int l, int r, tratta* ordinamento[], tratta* ordinamentoB[]) {
    int q;
    if (r <= l)
        return;
    q = (l + r)/2;
    MergeSortR(A, B, l, q, ordinamento, ordinamentoB);
    MergeSortR(A, B, q+1, r, ordinamento, ordinamentoB);
    Merge(A, B, l, q, r, ordinamento, ordinamentoB);
}

void MergeSort(char **A, int N, tratta* ordinamento[]) {
    int l=0, r=N-1;
    char **B = (char **)malloc(N*sizeof(char*));
    tratta **ordinamentoB = (tratta **)malloc(N*sizeof(tratta*));

    if (B == NULL) {
        printf("Memory allocation error\n");
        exit(1);
    }
    MergeSortR(A, B, l, r, ordinamento, ordinamentoB);
}

int leggiFile(tratta tratte[]){

    FILE* fp = fopen(NOME_FILE,"r");

    if(fp == NULL)
        return 0;

    int nTratte = 0;

    fscanf(fp, "%d", &nTratte);

    int i = 0;

    while(fscanf(fp,"%s %s %s %s %s %s %d",tratte[i].codice,tratte[i].partenza,tratte[i].destinazione,tratte[i].data,tratte[i].oraPartenza,tratte[i].oraArrivo,&tratte[i].ritardo) != EOF){
        i++;
    }

    fclose(fp);

    return nTratte;
}