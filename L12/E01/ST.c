//
// Created by gabriele on 19/01/19.
//

#include "ST.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int getIndiceByNome(ST st,char* nome){
    int i;
    for (i = 0; i < st.size; ++i) {
        if(!strcmp(st.a[i].nome,nome))
            return i;
    }

    return -1;

}
char* getNomeByIndice(ST st,int indice){
    return st.a[indice].nome;
}

Item ITEMSetNULL(){
    Item a;
    strcpy(a.nome,"ItemNULL");

    return a;
}