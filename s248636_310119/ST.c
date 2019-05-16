//
// Created by gabriele on 31/01/19.
//

#include "ST.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


ST STInit(int maxN) {
    ST st;
    int i;
    st = malloc(sizeof(*st));
    st->a = malloc(maxN * sizeof(char*) );
    for (i = 0; i < maxN; ++i) {
        st->a[i] = malloc(20 * sizeof(char));
    }
    st->maxN = maxN;
    st->n= 0;
    return st;
}

int STsearch(ST st, char* k) {
    int i;
    if (st->n == 0)
        return -1;
    for (i = 0; i < st->n; i++)
        if (strcmp(k, st->a[i]) == 0)
            return i;
    return -1;
}

int STinsert(ST st, char* val) {
    int i = st->n;
    strcpy(st->a[i], val);
    st->n++;
    return i;
}