//
// Created by gabriele on 02/01/19.
//

#ifndef E01_LISTTITOLI_H
#define E01_LISTTITOLI_H

#include "titolo.h"

typedef struct tabTitoli_t* listTitoli;

listTitoli leggiFile();
float ricercaQuotazioneByData(listTitoli lista);
void ricercaQuotazioneMinimaEMassimaTraDate(listTitoli lista);
void ricercaQuotazioneMinimaEMassima(listTitoli lista);
void bilanciaBstTitolo(listTitoli lista);

#endif //E01_LISTTITOLI_H
