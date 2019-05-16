//
// Created by gabriele on 02/01/19.
//

#include "data.h"

int dataCMP(data d1, data d2){
    int data1 = d1.anno * 10000 + d1.mese* 100 + d1.giorno;
    int data2 = d2.anno * 10000 + d2.mese* 100 + d2.giorno;

    if (data1 > data2)
        return 1;
    else if (data1 < data2)
        return -1;

    return 0;
}

data newData(int anno,int mese,int giorno){
    data d;
    d.anno = anno;
    d.mese = mese;
    d.giorno = giorno;

    return d;
}
