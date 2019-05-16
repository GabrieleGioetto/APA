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
int leggiFileSorgente(sostituzione sostituzioni[],int nSostituzioni);
int main(int argc, char const *argv[]) {

  int nSostituzioni;
  sostituzione sostituzioni[MAXSOSTITUZIONI];

  if (!leggiFileDizionario(sostituzioni,&nSostituzioni )){
    printf("Errore lettura file dizionario\n");
    return -1;
  }

  printf("%d\n", nSostituzioni);

  if(!leggiFileSorgente(sostituzioni,nSostituzioni)){
    printf("Errore lettura file sorgente\n");
    return -1;
  }

  return 0;
}

int leggiFileDizionario(sostituzione sostituzioni[],int *nSostituzioni ){

  FILE *fpDizionario = fopen("dizionario.txt","r");
  if (fpDizionario == NULL)
    return(-1);


  fscanf(fpDizionario,"%d",nSostituzioni);
  int i = 0;

  while(fscanf(fpDizionario,"%s %s",sostituzioni[i].codice,sostituzioni[i].parola) != EOF){
      i++;
  }


  return 1;
}

int leggiFileSorgente(sostituzione sostituzioni[],int nSostituzioni){

  FILE *fpSorgente = fopen("sorgente.txt","r");
  if (fpSorgente == NULL)
    return(0);


  char riga[LUNGHRIGHE];
  int i;

  while (fgets(riga,LUNGHRIGHE, fpSorgente)) {
    for (i = 0; i < nSostituzioni; i++) {
        if(strstr(riga,sostituzioni[i].parola)){
          printf("%s",strstr(riga,sostituzioni[i].parola));
        }
    }
  }

  return 1;
}
