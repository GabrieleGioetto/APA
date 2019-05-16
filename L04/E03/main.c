#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define LUNGHSTRINGA 50

char *cercaRegexp(char *src, char *regexp, int* k);
void controlloCarattere(char carattere, char* regexp, int i, int* j, int k, int* valido);
int gestisciBackSlash(char carattere, char carattereBackSlash);
int gestisciQuadre(char CarattereStr, char* regex);

int main() {

    char src[LUNGHSTRINGA];
    char regexp[LUNGHSTRINGA];

    printf("Inserisci stringa sorgente in cui cercare: ");
    gets(src);
    printf("Inserisci espressione regolare da cercare: ");
    gets(regexp);

    int k;

    char* risultato = cercaRegexp(src,regexp, &k);
    printf("Stringa: %.*s", k, risultato);
    return 0;
}

char *cercaRegexp(char *src, char *regexp, int* k){

    int i, valido,j;

    //Ciclo le lettere della stringa sorgente
    for (i = 0; i <= strlen(src); ++i) {

        //Ciclo lettere regex per ogni lettera della stringa sorgente
        //j cicla la regex, *k cicla la stringa(uso puntatore per salvare numero caratteri da stampare nella stampa finale)
        for (j = 0,*k = 0, valido = 1; j <= strlen(regexp) && valido == 1; j++, (*k)++) {

            if(regexp[j] != '\0')
                controlloCarattere(src[*k + i],regexp,i,&j,*k + i,&valido);
            else
                return &src[i];//Sono arrivato al fondo della substring, perciò l'ho trovata

        }
    }

    return NULL;
}

void controlloCarattere(char carattere, char* regexp, int i, int* j, int k, int* valido){

    if(isalnum(regexp[*j])) {
        if (carattere != regexp[*j])
            *valido = 0;//Condizione di uscita dal ciclo
    }
    else if(regexp[*j] == '['){
        if(gestisciQuadre(carattere , regexp + *j +1) == 1)
            while (regexp[++(*j)] != ']');//Salto caratteri in regex fino alla quadra
        else
            *valido = 0;//Condizione di uscita dal ciclo
    }
    else if(regexp[*j] == '\\') {
        //Aumento j così salta carattere 'a' o 'A' nella regex, appena controllato
        *valido = gestisciBackSlash(carattere,regexp[*j + 1]);
        (*j)++;
    }
}


int gestisciQuadre(char CarattereStr, char* regex){
    int i = 0, condizioneVerificata = -1;

    if(regex[0] == '^')//Devo controllare se sono diversi
        i = 1;
    else//Controllo se sono uguali
        condizioneVerificata = 1;

    while(regex[i] != ']'){
        if(CarattereStr == regex[i])
            return condizioneVerificata;
        i++;
    }
    return condizioneVerificata * -1;
}

int gestisciBackSlash(char carattere, char carattereBackSlash){
    //carattereBackSlash può essere 'a' od 'A'
    return (islower(carattere) == islower(carattereBackSlash)) ;
}