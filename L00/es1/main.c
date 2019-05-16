#include <stdio.h>

int findMaxLength(int n,int v[]);
void printLongestSequences(int n, int maxLegth, int V[]);

int main()
{
    int n;

    do
    {
        printf("Insert n: ");
        scanf("%d", &n);
    } while (n < 0 && n > 30);

    int V[n];

    int i;
    for (i = 0; i < n; i++)
    {
        printf("Insert number: ");
        scanf("%d", &V[i]);
    }

    int maxLength = findMaxLength(n,V);

    printLongestSequences(n, maxLength,V);

    return 0;
}

void printLongestSequences(int n, int maxLength, int V[]){
    
    int cont, i2, i;

    for (i = 0; i < n - maxLength; i++) {
        cont = 0;
        while (cont < maxLength) {
            if (V[i + cont] != 0) {
                cont++;
            }
            else{
                
                break;
            }
            
            if (cont == maxLength) {
                for (i2 = i; i2 < (i + maxLength); i2++) {
                    printf("%d ", V[i2]);
                }
                printf("\n");
            }

        }
    }
}


int findMaxLength(int n,int v[])
{
    int length, i = 0, maxLength = 0;


    while(i < n){

        while(v[i] != 0 && i < n){
          length++;
          i++;
        }

        i++;

        if(length > maxLength)
            maxLength = length;

        length = 0;
    }

    return maxLength;
}