#include <stdio.h>
#include <string.h>
#include "ListTitoli.h"

typedef enum{
    c_ricercaQuotazione, c_ricercaQuotazioneTraDate, c_ricercaQuotazioneMassima, c_bilanciamentoQuotazioni, c_fine
}comando;

comando selezionaComando();
void selezionaDati(comando c, listTitoli lista);

int main() {

    //CARICO LISTA TITOLI
    listTitoli lista = leggiFile();

    comando c = c_ricercaQuotazione;
    while(c != c_fine){
        c = selezionaComando();

        selezionaDati(c, lista);
    }

    return 0;
}

comando selezionaComando(){
    char tabella[4][50]={"ricercaQuotazione", "ricercaQuotazioneTraDate", "ricercaQuotazioneMassima", "bilanciamentoQuotazioni"};

    char comandoScelto[50];
    printf("Scegli comando: ( ricercaQuotazione | ricercaQuotazioneTraDate | ricercaQuotazioneMassima | bilanciamentoQuotazioni | f ine) : ");
    scanf("%s", comandoScelto);

    comando c = c_ricercaQuotazione;
    while(c < c_fine && strcmp(comandoScelto,tabella[c]) != 0)
        c++;

    return c;
}


void selezionaDati(comando c, listTitoli lista) {
    switch(c){
        case c_ricercaQuotazione:
            printf("Quotazione nella data : %.2f\n", ricercaQuotazioneByData(lista));
            break;
        case c_ricercaQuotazioneTraDate:
            ricercaQuotazioneMinimaEMassimaTraDate(lista);
            break;
        case c_ricercaQuotazioneMassima:
            ricercaQuotazioneMinimaEMassima(lista);
            break;
        case c_bilanciamentoQuotazioni:
            bilanciaBstTitolo(lista);
            break;
        case c_fine:
            break;
    }
}
