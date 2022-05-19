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

void SelectionSort(int *A, int n) // copiado da atividade
{
    int i, temp,contador = 0;
    for (i = 0; i < n-1; i++)
    {
        int min = i;
        for(int j = i + 1; j < n; j++)
        {
            if (A[j] < A[min])
            {
                min = j;
                
            }
            contador++;
        }
        temp = A[i];
        A[i] = A[min];
        A[min] = temp;
        ImprimeVetor(A,n);

    }
    printf("Total de IFs executados:%d",contador);
    
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
    SelectionSort(v,n);
    free(v);

    return 0;
}