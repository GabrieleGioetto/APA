//
// Created by gabriele on 31/01/19.
//

#ifndef ESAME310119_ST_H
#define ESAME310119_ST_H


typedef struct ST_T* ST;

struct ST_T{
    char** a;
    int n;
    int maxN;
};

ST STInit(int maxN);
int STsearch(ST st, char* k);
int STinsert(ST st, char* val);

#endif //ESAME310119_ST_H
