#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXRIGHE 1000

typedef enum{
    r_date, r_partenza, r_capolinea, r_ritardo,r_ritardo_tot, r_fine
}comando;

typedef struct{
    char codice[7];
    char partenza[30];
    char destinazione[30];
    char data[15];
    char oraPartenza[9];
    char oraArrivo[9];
    int ritardo;
}tratta;

comando leggiComando();
void selezionaDati(tratta tratte[MAXRIGHE], int nTratte, comando codiceComando);
int leggiFile(tratta tratte[MAXRIGHE]);
void selezionaDatiFiltrati(tratta tratte[MAXRIGHE], int nTratte, char dataInizio[], char dataFine[], char fermataPartenza[], char fermataCapolinea[],int controllaRitardo);
void trovaRitardoComplessivo(tratta tratte[MAXRIGHE], int nTratte,char codice[] );
void stampaTratta(tratta tr);

int main() {

    tratta tratte[MAXRIGHE];

    int nTratte;
    if( !(nTratte = leggiFile(tratte)))
        return 0;

    comando codiceComando = r_date;

    while(codiceComando != r_fine){
        codiceComando = leggiComando();

        selezionaDati(tratte,nTratte, codiceComando);
    }
}

void selezionaDati(tratta tratte[MAXRIGHE], int nTratte, comando codiceComando){

    char dataInizio[12] = "", dataFine[12] = "", fermataPartenza[20] = "",fermataCapolinea[20] = "", codice[7];
    int controllaRitardo = 0;

    switch(codiceComando){
        case r_date:
            printf("Inserisci data inizio e data fine(YYYY/MM/DD): ");
            scanf("%s %s", dataInizio,dataFine);
            break;
        case r_partenza:
            printf("Inserisci fermata partenza: ");
            scanf("%s", fermataPartenza);
            break;
        case r_capolinea:
            printf("Inserisci fermata capolinea: ");
            scanf("%s", fermataCapolinea);
            break;
        case r_ritardo:
            printf("Inserisci data inizio, data fine(YYYY/MM/DD) e destinazione: ");
            scanf("%s %s %s", dataInizio,dataFine, fermataCapolinea);
            controllaRitardo = 1;
            break;
        case r_ritardo_tot:
            printf("Inserisci codice (Ritardo complessivo): ");
            scanf("%s", codice);
            trovaRitardoComplessivo(tratte,nTratte,codice);
            return;
            break;
        case r_fine:return;

    }
    selezionaDatiFiltrati(tratte,nTratte,dataInizio,dataFine,fermataPartenza,fermataCapolinea, controllaRitardo);

}

void trovaRitardoComplessivo(tratta tratte[MAXRIGHE], int nTratte,char codice[] ){

    int i, ritardoTot = 0;

    for (int i = 0; i < nTratte; ++i) {
        if (!strcmp(tratte[i].codice,codice))
            ritardoTot += tratte[i].ritardo;
    }

    printf("Il ritardo complessivo della tratta è di %d minuti\n\n", ritardoTot);
}

void selezionaDatiFiltrati(tratta tratte[MAXRIGHE], int nTratte, char dataInizio[], char dataFine[], char fermataPartenza[], char fermataCapolinea[] ,int controllaRitardo){
    int i;

    for (int i = 0; i < nTratte; i++) {

        if(( !strcmp(dataInizio, "") || (strcmp(dataInizio,tratte[i].data)) <= 0) && ((!strcmp(dataFine, "") || strcmp(dataFine,tratte[i].data) >= 0))) {
            if ((!strcmp(fermataPartenza, "") || !strcmp(fermataPartenza, tratte[i].partenza)) && ((!strcmp(fermataCapolinea, "") || !strcmp(fermataCapolinea, tratte[i].destinazione))))
                if (!controllaRitardo || tratte[i].ritardo)
                    stampaTratta(tratte[i]);
        }

    }
}

void stampaTratta(tratta tr){
    printf("Codice tratta: %s\n", tr.codice);
    printf("Partenza: %s\n", tr.partenza);
    printf("Destinazione: %s\n", tr.destinazione);
    printf("Data: %s\n", tr.data);
    printf("Ora Partenza: %s\n", tr.oraPartenza);
    printf("Ora arrivo: %s\n", tr.oraArrivo);
    printf("Ritardo: %s\n\n\n", tr.ritardo > 0 ? "sì" : "no");
}

comando leggiComando(){
    comando c;

    char cmd[20];
    char tabella[6][20] = {
            "data", "partenza",
            "capolinea", "ritardo",
            "ritardo_tot","fine"
    };

    printf("Inserisci comando: ");
    scanf("%s", cmd);

    c = r_date;

    while (c<r_fine && strcmp(cmd,tabella[c])!=0)
        c++;

    return (c);

}

int leggiFile(tratta tratte[]){

    FILE* fp = fopen("tratte.txt","r");

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