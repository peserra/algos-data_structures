//gcc mergeSort.c -o prog.exe
#include <stdio.h>
#include <stdlib.h>

// Recebe um vetor e o seu tamanho.
// Imprime o conteudo do vetor.
void imprimir(int *v, int n)
{

    for (int i = 0; i < n - 1; i++)
    {
        printf("%d ", v[i]);
    }
    if (n > 0)
    {
        printf("%d\n", v[n - 1]);
    }
}

// Recebe um vetor bipartido: v[e..m-1] e v[m..d-1] ordenados.
// Intercala os elementos de modo que v[e..d-1] fique ordenado.
// Usa um vetor auxiliar de tamanho n = d-e.
// Imprima o conteudo do vetor auxiliar antes de liberar a memoria e finalizar o procedimento.
void intercala(int *v, int e, int m, int d)
{
    int tamanhoAux = d - e ;
    int *vAux = malloc(sizeof(int) * tamanhoAux);
    int i = e, j = m, k = 0; // i: esquerdo , j: direito, k: auxiliar
    while (i < m && j < d)
    {
        if (v[i] < v[j])
        {
            vAux[k] = v[i];
            k++;
            i++;
        }
        else
        {
            vAux[k] = v[j];
            k++;
            j++;
        }
    }
    while (i < m) // preenche o resto do vetor auxiliar caso  sobre o lado esquerdo
    {
        vAux[k] = v[i];
        k++;
        i++;
    }
    while (j < d) // preenche o resto do vetor auxiliar caso  sobre o lado direito
    {
        vAux[k] = v[j];
        k++;
        j++;
    }
    for (i = 0; i < tamanhoAux; i++)
    {
        v[e + i] = vAux[i];
    }
    imprimir(vAux, tamanhoAux);
    free(vAux);
}

// Recebe um vetor v[e..d-1] e ordena recursivamente.
void mergeSortR(int *v, int e, int d)
{
    int meio;
    if (e < d - 1) // enquanto nao tiver um elemento
    {
        meio = (d + e) / 2;
        mergeSortR(v, e, meio); // lado esquerdo
        mergeSortR(v, meio, d); // lado direito
        intercala(v, e, meio, d); //intercala
    }
}

// Recebe um vetor e o seu tamanho.
// Ordena o vetor com o algoritmo mergeSort.
void mergeSort(int *v, int n)
{
    mergeSortR(v, 0, n);
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
    mergeSort(v, n);
    free(v);
    return 0;
}