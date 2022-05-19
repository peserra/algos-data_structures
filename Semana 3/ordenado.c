#include <stdio.h>
#include <stdlib.h>

int OrdenadoDecrescente(int *A, int n)
{
    int i;
    for(i = 0; i < n-1; i++)
    {
        if(A[i+1] > A[i])
        {
            return 0; //false
        }
    }
    return 1; //true
}
int OrdenadoCrescente(int *A, int n)
{
    int i;
    for(i = 0; i < n-1; i++)
    {
        if(A[i+1] < A[i])
        {
            return 0; 
        }
    }
    return 1; 
}

int main()
{
    int i, n; 
     
    while (scanf("%d", &n) != EOF) //le o 'n' em cada linha (tira o 'n' da leitura)
    {
        if (n > 0) 
        {
            int *v = malloc(sizeof(int) * n);
            for (i = 0; i < n; i++) //leitura da proxima linha (vetor)
            {
                scanf("%d", &v[i]);
            }
            if(OrdenadoDecrescente(v,n) || OrdenadoCrescente(v,n)) 
            {
                printf("S\n");
            }
            else
            {
                printf("N\n");
            }
            free(v);
        }
        else
        {
            printf("S\n");//um vetor vazio está ordenado
        }
    }
    return 0;
}
