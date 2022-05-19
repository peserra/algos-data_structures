#include<stdio.h>
#include<stdlib.h>

void ImprimeVetor(int *A, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", A[i]);
    }
    printf("\n");
}

void InsertionSort(int *A, int n) // copiado da aula
{
    int i, j, chave,deslocamentos = 0;
    for (j = 1; j < n; j++)
    {
        chave = A[j];
        i = j - 1;
        while (i >= 0 && chave < A[i])
        {
            //desloca para a direita
            A[i + 1] = A[i];
            deslocamentos++;
            ImprimeVetor(A,n);
            i--;
        }
        A[i + 1] = chave;
        ImprimeVetor(A,n);
    }
    printf("Deslocamentos:%d",deslocamentos);
    
}


int main ()
{
    int i, n;
    scanf("%d", &n);
    int *v = malloc(sizeof(int) * n);
    for(i = 0; i < n; i++)
    {
        scanf("%d", &v[i]);
    }
    InsertionSort(v,n);
    free(v);

    return 0;
}