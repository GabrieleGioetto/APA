#include <stdio.h>

int maggioritario(int* v, int N);

int main() {

    int n;
    printf("Inserire elementi vettore: ");
    scanf("%d", &n);

    int v[n];
    int i;
    for (i = 0; i < n; ++i) {
        printf("Inserisci elemento %d: ", i);
        scanf("%d", &v[i]);
    }

    printf("Maggioritario: %d", maggioritario(v, n));
    return 0;
}

int maggioritario(int* v, int N) {
    if (N == 1)
        return v[0];

    int k = N / 2;

    int maggSinistra = maggioritario(v, k);

    /*Controllo se la lunghezza è dispari e diversa da 1, se lo è gli passo la lunghezza + 1
      Controllo non necessario se argomenti fossero 'l' e 'r'(left / rigth) al posto di N */
    int maggDestra = maggioritario(&v[k], (N % 2 == 0 || N == 1) ? k : k + 1);

    if (maggSinistra == maggDestra)
        return maggSinistra;

    int i, contSinistra = 0, contDestra = 0;

    //Ciclo per controllare se i maggioritari delle funzioni 'figlie' sono maggioritarie nella funzione padre
    for (i = 0; i < N; ++i) {
        if (*(v + i) == maggSinistra)
            contSinistra++;
        if (*(v + i) == maggDestra)
            contDestra++;
    }

    if (contSinistra > k)
        return maggSinistra;
    if (contDestra > k)
        return maggDestra;

    return -1;
}