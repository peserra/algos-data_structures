// gcc quickSort.c -o prog.exe
#include <stdio.h>
#include <stdlib.h>

// Imprime o conteudo do vetor v[e..d-1].
void imprimir(int *v, int e, int d)
{
    for (int i = e; i < d - 1; i++)
    {
        printf("%d ", v[i]);
    }
    if (d > e)
    {
        printf("%d\n", v[d - 1]);
    }
}

// Troca os elementos v[i] <-> v[j].
void troca(int *v, int i, int j)
{
    int temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

// Recebe um vetor v[e..d-1] e indice do Pivo (= v[p]).
// Rearranja o vetor de modo que:
// v[e..i-1] <= Pivo <= v[i+1..d-1]
// Devolve o indice atualizado do Pivo.
int particiona(int *v, int e, int d, int p) // e <= p <= d-1
{
    troca(v, d - 1, p); // coloca o pivo no fim do vetor
    int j = e, i = j - 1;
    while (j < d - 1)
    {
        if (v[j] <= v[d - 1])
        {
            i++;
            troca(v, i, j);
        }
        j++;
    }
    i++;
    troca(v, i, d - 1);
    return i;
}

// Recebe um vetor v[e..d-1] e ordena recursivamente.
void quickSortR(int *v, int e, int d) // d = n-1
{
    if (e < d - 1)
    {
        int pivo = d - 1; //"pivo é o ultimo elemento"
        pivo = particiona(v, e, d, pivo);
        printf("Pivo: [%d] %d\n", pivo, v[pivo]);
        imprimir(v, e, d);
        quickSortR(v, e, pivo);
        quickSortR(v, pivo + 1, d);
    }
}

// Recebe o vetor e o seu tamanho e ordena o vetor com o algoritmo QuickSort.
void quickSort(int *v, int n)
{
    quickSortR(v, 0, n);
}

int main()
{
    int n, i;
    scanf("%d", &n);
    int *v = malloc(sizeof(int) * n);
    for (i = 0; i < n; i++)
    {
        scanf("%d", &v[i]);
    }
    quickSort(v, n);
    imprimir(v, 0, n);
    free(v);
    return 0;
}