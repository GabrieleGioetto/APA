//
// Created by gabriele on 02/01/19.
//

#ifndef E01_DATA_H
#define E01_DATA_H

typedef struct{
    int anno;
    int mese;
    int giorno;
}data;

int dataCMP(data d1, data d2);
data newData(int anno,int mese,int giorno);

#endif //E01_DATA_H
