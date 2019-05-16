//
// Created by gabriele on 02/01/19.
//

#include "quotazioneGiornaliera.h"


int quotazioneCMP(quotazione q1, quotazione q2){
    return dataCMP(q1.data, q2.data);
}

quotazione quotazioneNULL(){
    quotazione q;
    q.quota = -1;
    q.sommaValori = -1;
    q.nValori = -1;

    return q;
}

quotazione newQuotazione(float sommaValori, int nValori, float quota, data data){
    quotazione q;
    q.sommaValori = sommaValori;
    q.nValori = nValori;
    q.quota = quota;
    q.data = data;

    return q;
}