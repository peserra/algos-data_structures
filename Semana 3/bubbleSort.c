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

void BubbleSort(int *A, int n) // copiado da atividade
{
    int i, j, auxiliar,contador = 0,satisfeitos = 0;
    for(i = 0; i < n-1; i++)
    {
        for(j = 0; j < n-i-1; j++)
        {
            if(A[j] > A[j+1])
            {
                auxiliar = A[j];
                A[j] = A[j+1];
                A[j+1] = auxiliar;
                ImprimeVetor(A,n);
                satisfeitos++;
            }
            contador++;
        }
    }
    printf("Total de IFs executados:%d\n",contador);
    printf("Total de IFs satisfeitos:%d",satisfeitos);
    
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
    BubbleSort(v,n);
    free(v);

    return 0;
}