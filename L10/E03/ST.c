//
// Created by gabriele on 31/12/18.
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


int aggiungiRete(ST* st,Item item){

    st->a[st->size++] = item;
    return st->size - 1;
}

int getIndiceRete(){

};

