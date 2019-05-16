#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#define LENGTH 20

int conta(char parola[20],int n);

int main(int argc, char** argv) {

    FILE *fp;
    fp = fopen("textFile.txt","r");
    
    int substringsCount = 0;

    
    int n;
    printf("Insert n: ");
    scanf("%d",&n);
    
    int N;
    fscanf(fp,"%d",&N);

    char parola[LENGTH];
    while(fscanf(fp,"%s",parola) != EOF){
        substringsCount += conta(parola, n);
    }
    
    printf("Number substrings: %d",substringsCount);
    
    return (EXIT_SUCCESS);
}

int conta(char parola[20],int n){
    
    int i, i2, count, substringsCount = 0;
    char lowerChar;
    
    for(i = 0; i <= strlen(parola) - n; i++){
        
        count = 0;
        for(i2 = i; i2 < i+n; i2++){
            
            lowerChar = tolower(parola[i2]);
            if(lowerChar == 'a' || lowerChar == 'e' || lowerChar == 'i' || lowerChar == 'o' || lowerChar == 'u')
                count++;
        }
        
        if(count == 2)
            substringsCount++;
    }
    
    return substringsCount;
}