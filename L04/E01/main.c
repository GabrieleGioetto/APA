#include <stdio.h>

int gcd(int a, int b);

int main() {
    int a,b;

    printf("Inserire due numeri interi positivi: ");
    scanf("%d %d",&a, &b);

    printf("Il loro Massimo Comun Divisore è %d", gcd(a,b));
    return 0;
}

int gcd(int a, int b){

    if(a == b)
        return a;

    if(a % 2 == 0 && b % 2 == 0)//Entrambi pari
        return 2* gcd(a/2,b/2);
    else if(a % 2 == 1 && b % 2 == 0)//a dispari, b pari
        return gcd(a,b/2);
    else if(b % 2 == 1 && a % 2 == 0)//a pari, b dispari
        return gcd(b,a/2);
    else if(a > b)//Entrambi dispari, a maggiore
        return gcd((a-b)/2,b);
    else
        return gcd((b-a)/2,a);
}