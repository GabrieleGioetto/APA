#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <memory.h>

#define MAX_SEQUENZE 20
#define MAX_LUNG_SEQUENZA 5
#define LUNG_PAROLA 25
#define MAX_OCCORRENZE 10

typedef struct{
    char parola[MAX_LUNG_SEQUENZA];
    char parolaOccorrenza[MAX_OCCORRENZE][LUNG_PAROLA];
    int occorrenze[MAX_OCCORRENZE];
    int contOccorrenze;
}sequenza;

int leggiFileSequenze(sequenza sequenze[]);
void stringaToLower(char stringa[]);
void pulisciStringa(char parolaLetta[25], int strlen);
int leggiRigheETrovaOccorrenze(sequenza sequenze[20], int nSequenze);

void stampaSequenze(sequenza sequenze[20], int nSequenze);

int main() {

    sequenza sequenze[MAX_SEQUENZE] = {"",{""},{0},0};
    int nSequenze = leggiFileSequenze(sequenze);

    if(!nSequenze){
        printf("Errore lettura file sequenze");
        return -1;
    }

    int i;
    for (i = 0; i < nSequenze; ++i)//Rendo stringhe sequenze minuscole
        stringaToLower(sequenze[i].parola);


    if(!leggiRigheETrovaOccorrenze(sequenze, nSequenze)){
        printf("Errore lettura file testo");
        return -1;
    }

    stampaSequenze(sequenze, nSequenze);

    return 0;
}

void stampaSequenze(sequenza sequenze[20], int nSequenze) {
    int i,j;
    for (i = 0; i < nSequenze; i++){
        printf("La sequenza %s è contenuta in %s", sequenze[i].parola, sequenze[i].contOccorrenze == 0 ? "nessuna parola" : "");
        for(j = 0; j < sequenze[i].contOccorrenze;j++){
            printf("%s (posizione %d)%c ",sequenze[i].parolaOccorrenza[j],sequenze[i].occorrenze[j], j == sequenze[i].contOccorrenze - 1 ? ' ' : ',');
        }
        printf("\n\n");
    }


}


int leggiRigheETrovaOccorrenze(sequenza sequenze[20], int nSequenze) {

    FILE* fp = fopen("testo.txt","r");

    if(fp == NULL)
        return 0;

    char parolaLetta[LUNG_PAROLA] = "";
    int i = 0,j, contParole = 0;

    char c;

    while( (c = fgetc(fp)) != EOF){

        if(isalnum(c))
            parolaLetta[i++] = tolower(c);
        else if(strlen(parolaLetta) > 0){ // if per non controllare in caso di doppi carattero non alfanumerici(Es ", ")

            contParole++;

            for (j = 0; j < nSequenze; ++j) {
                if(sequenze[j].contOccorrenze < 10 && strstr(parolaLetta,sequenze[j].parola) != NULL){
                    strcpy(sequenze[j].parolaOccorrenza[sequenze[j].contOccorrenze], parolaLetta);
                    sequenze[j].occorrenze[sequenze[j].contOccorrenze++] = contParole;
                }
            }

            pulisciStringa(parolaLetta, (int) strlen(parolaLetta));//Resetto stringa

            i = 0;
        }


    }

    fclose(fp);

    return 1;
}

void pulisciStringa(char parolaLetta[25], int strlen) {
    int i;
    for(i = 0; i < strlen; i++)
        parolaLetta[i] = '\0';
}

void stringaToLower(char stringa[]){
    int i = 0;
    while(stringa[i] != '\0'){
        stringa[i] = tolower(stringa[i]);
        i++;
    }

}

int leggiFileSequenze(sequenza sequenze[]){

    FILE* fp = fopen("sequenze.txt","r");

    if(fp == NULL)
        return 0;

    int nSequenze, i = 0;
    fscanf(fp,"%d",&nSequenze);

    while(fscanf(fp,"%s",sequenze[i++].parola) != EOF);

    fclose(fp);

    return nSequenze;
}