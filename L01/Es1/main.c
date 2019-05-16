#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXGIORNATE 20
#define MAXSQUADRE 20


typedef struct{
   int punti[MAXGIORNATE];
   int puntiPerGiornata;
}squadra;

int trovaSquadraInCima(int n, squadra squadre[]);
void calcolaClassificaPerGiornata(int m,int n,squadra squadre[]);
void caricaMatricePuntiSquadre(squadra squadre[], FILE* fp);
void inizializzaPuntiSquadre(squadra squadre[],int n);

int main(int argc, char const *argv[]) {


  FILE* fp = fopen("campionato.txt","r");

  if(fp == NULL){
    printf("Error reading file");
    return(-1);
  }

  int n = 4,m = 4;//Numero righe e colonne(Sarebbe da leggere da file)

  squadra squadre[n];

  inizializzaPuntiSquadre(squadre,n);

  caricaMatricePuntiSquadre(squadre,fp);

  calcolaClassificaPerGiornata(m,n,squadre);

  return 0;
}

void inizializzaPuntiSquadre(squadra squadre[],int n){
  int i,j;
  for(i = 0; i < n; i++)
    squadre[i].puntiPerGiornata = 0;
}

void calcolaClassificaPerGiornata(int m,int n, squadra squadre[]){
  int i,j;
  for (i = 0; i < m; i++) {
    for (j = 0; j < n; j++) {
      squadre[j].puntiPerGiornata += squadre[j].punti[i];
    }
    printf("Capolista giornata %d: %d\n",i+1, trovaSquadraInCima(n,squadre) +1);

  }
}

void caricaMatricePuntiSquadre(squadra squadre[], FILE* fp){
  char *token;

  char stringaPuntiSquadra[60];

  int i = 0,j = 0;
  while (fgets(stringaPuntiSquadra, 60,fp) != NULL) {
    token = strtok(stringaPuntiSquadra, " ");

   while( token != NULL ) { //Divido la stringa con tutti i punteggi e li metto nel vettore dell'apposita squadra
      squadre[i].punti[j] = atoi(token);
      token = strtok(NULL, " ");

      j++;
   }

   i++;
   j = 0;
  }
}


int trovaSquadraInCima(int n, squadra squadre[]){//Trova squadra in cima per giornata
  int i;

  int indiceMax = -1;
  int puntiMax = 0;
  for (i = 0; i < n; i++) {
    if (squadre[i].puntiPerGiornata > puntiMax){
      indiceMax = i;
      puntiMax = squadre[i].puntiPerGiornata;
    }
  }

  return indiceMax;
}
