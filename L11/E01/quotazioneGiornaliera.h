//
// Created by gabriele on 02/01/19.
//

#ifndef E01_QUOTAZIONEGIORNALIERA_H
#define E01_QUOTAZIONEGIORNALIERA_H

#include "data.h"

typedef struct{
    float sommaValori;
    int nValori;
    float quota;
    data data;
}quotazione;

int quotazioneCMP(quotazione q1, quotazione q2);
quotazione quotazioneNULL();
quotazione newQuotazione(float sommaValori, int nValori, float quota, data data);

#endif //E01_QUOTAZIONEGIORNALIERA_H
