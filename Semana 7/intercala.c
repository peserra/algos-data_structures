// gcc intercala.c -o prog.exe
#include <stdio.h>
#include <stdlib.h>

// aloque 2 vetores com o tamanho q1 e q2
//  receba os valores nos vetores, ordenados em cada bloco
//  construa um terceiro vetor vr comm tamanho q1 + q2
// intercale os valores de q1 e q2 de modo a vr ficar ordenado
void imprimir(int *v, int n)
{

    for (int i = 0; i < n; i++)
    {
        printf("%d\n", v[i]);
    }
    
}


int *intercala(int *v1, int *v2, int q1, int q2)
{
    int *vAux = malloc(sizeof(int) * (q1+q2));
    int i = 0, j = 0, k = 0;

    while (i < q1 && j < q2) //i: vetor 1, j: vetor 2, k: vetor auxiliar;
    {
        if (v1[i] < v2[j])
        {
            vAux[k] = v1[i];
            k++;
            i++;
        }
        else
        {
            vAux[k] = v2[j];
            k++;
            j++;
        }
    }
    while (i < q1)
    {
        vAux[k] = v1[i];
        k++;
        i++;
    }
    while (j < q2)
    {
        vAux[k] = v2[j];
        k++;
        j++;
    }
    return vAux;
}

int main()
{
    int q1, q2, i;
    scanf("%d", &q1);
    scanf("%d", &q2);
    int *v1 = malloc(sizeof(int) * q1);
    int *v2 = malloc(sizeof(int) * q2);

    for (i = 0; i < q1; i++)
    {
        scanf("%d", &v1[i]);
    }

    for (i = 0; i < q2; i++)
    {
        scanf("%d", &v2[i]);
    }

    int *vetorOrdenado = intercala(v1, v2, q1, q2);
    imprimir(vetorOrdenado, (q1+q2));
    free(v1);
    free(v2);
    free(vetorOrdenado);
    return 0;
}