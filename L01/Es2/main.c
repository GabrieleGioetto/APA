#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSOSTITUZIONI 30
#define LUNGHPAROLE 20
#define LUNGHRIGHE 200

typedef struct {
    char codice[10];
    char parola[LUNGHPAROLE];
}sostituzione;

int leggiFileDizionario(sostituzione sostituzioni[],int *nSostituzioni );
int leggiFileSorgenteEscriviRicodificato(sostituzione sostituzioni[],int nSostituzioni);
void nuovaRiga(int posSubstring, char* riga, sostituzione sost  );

int main(int argc, char const *argv[]) {

    int nSostituzioni;
    sostituzione sostituzioni[MAXSOSTITUZIONI];

    if (!leggiFileDizionario(sostituzioni, &nSostituzioni)) {
        printf("Errore lettura file dizionario\n");
        return -1;
    }

    if (!leggiFileSorgenteEscriviRicodificato(sostituzioni, nSostituzioni)) {
        printf("Errore lettura file\n");
        return -1;
    }

    return 0;
}

int leggiFileDizionario(sostituzione sostituzioni[],int *nSostituzioni ) {

    FILE *fpDizionario = fopen("dizionario.txt", "r");
    if (fpDizionario == NULL)
        return (-1);

    fscanf(fpDizionario, "%d", nSostituzioni);
    int i = 0;

    while (fscanf(fpDizionario, "%s %s", sostituzioni[i].codice, sostituzioni[i].parola) != EOF)
        i++;

    fclose(fpDizionario);

    return 1;
}

int leggiFileSorgenteEscriviRicodificato(sostituzione sostituzioni[],int nSostituzioni) {

    FILE *fpSorgente = fopen("sorgente.txt", "r");
    if (fpSorgente == NULL)
        return (0);

    FILE *fpRicodificato = fopen("ricodificato.txt", "w+");
    if (fpRicodificato == NULL)
        return (0);

    char riga[LUNGHRIGHE];
    strcpy(riga, "");
    int i;
    char *result;
    int posSubstring;

    while (fgets(riga, LUNGHRIGHE, fpSorgente)) {
        for (i = 0; i < nSostituzioni; i++) {
            result = strstr(riga, sostituzioni[i].parola);
            if (result) {
                posSubstring = result - riga;

                nuovaRiga(posSubstring,riga,sostituzioni[i]);//Scrive in riga la riga modificata
            }
        }

        printf("%s",riga);
        fprintf(fpRicodificato,"%s",riga);
    }

    fclose(fpSorgente);
    fclose(fpRicodificato);

    return 1;
}

void nuovaRiga(int posSubstring, char* riga, sostituzione sost  ){

    char newLine[LUNGHRIGHE];
    int i;

    for (i = 0; i < posSubstring; i++) {//Copia frase prima del codice
        newLine[i] = riga[i];
    }
    for (i = posSubstring; i < posSubstring + strlen(sost.codice); i++) {//Copia il codice
        newLine[i] = sost.codice[i - posSubstring];
    }
    for (i = posSubstring + strlen(sost.codice); (i) < strlen(riga) + strlen(sost.codice) - strlen(sost.parola); i++) {//Copia frase dopo il codice
        newLine[i] = riga[i + (strlen(sost.parola) - strlen(sost.codice))];
    }

    newLine[i] = '\0'; //Per togliere caratteri extra
    strcpy(riga,newLine);
}
