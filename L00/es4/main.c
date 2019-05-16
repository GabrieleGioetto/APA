/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   main.c
 * Author: gabriele
 *
 * Created on October 3, 2018, 6:14 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILELENGTH 40

void copiaMatrice(int nr, int nc, int supportMatrix[][nc], int maxSupportMatrix[][nc]);
void printSubMatrix(int nr, int nc, int matrix[][nc]);

int main(int argc, char** argv) {


    char fileName[FILELENGTH];
    printf("Insert file name: ");
    scanf("%s",fileName);

    FILE *fp;
    fp = fopen("textFile.txt","r");

    int nr, nc;
    fscanf(fp,"%d %d",&nr,&nc);

    int dim;
    int numberMatrix[nr][nc];

    int r = 0, c = 0;

    while(fscanf(fp,"%d",&numberMatrix[r][c]) != EOF){
        c++;
        if (c == 3){
            r++;
            c = 0;
        }


    }


    printSubMatrix(nr,nc,numberMatrix);

    int i,j,k,t;
    int matrixSum = 0, maxMatrixSum = 0, supportMatrix[dim][dim], maxSupportMatrix[dim][dim];

    while(1){
        printf("Insert the dimension of the submatrix: ");
        scanf("%d",&dim);

        if (dim < 1 || dim > nr || dim > nc)
            break;

        for(i = 0; i <= nr - dim; i++){
            for(j = 0; j <= nc - dim; j++){
                for(k = i; k < i + dim; k++){
                    for(t = j; t < j + dim; t++){
                        matrixSum +=  numberMatrix[k][t];
                        printf("k-i: %d ",k-i);
                        printf("t-j: %d \n",t-j);
                        printf("dato letto: %d \n", numberMatrix[k][t]);
                        supportMatrix[k-i][t-j] = numberMatrix[k][t];
                        printSubMatrix(dim,dim,supportMatrix);
                        printf("\n");
                    }
                }

                if(matrixSum > maxMatrixSum){
                    //memcpy(supportMatrix,maxSupportMatrix, dim*dim*sizeof(int));
                    copiaMatrice(nr,nc,supportMatrix, maxSupportMatrix);
                }

                matrixSum = 0;
            }


        }

        printf("\n\n\n\n");
        printSubMatrix(dim,dim,maxSupportMatrix);
    }

    return (EXIT_SUCCESS);
}

void printSubMatrix(int nr, int nc, int matrix[][nc]){
    int i,j;
    for (i = 0; i < nr; i++){
        for(j = 0; j < nc; j++){
            printf("%d ",matrix[i][j]);
        }
        printf("\n");
    }
}

void copiaMatrice(int nr, int nc, int supportMatrix[][nc], int maxSupportMatrix[][nc]){
    int i,j;
    for (i = 0; i < nr; i++){
        for(j = 0; j < nc; j++){
            maxSupportMatrix[i][j]= supportMatrix[i][j];
        }
    }
}
