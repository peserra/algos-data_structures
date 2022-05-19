// gcc intercala2.c -o prog.exe
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


int *intercala(int *v, int q1, int q2)
{
    int *vAux = malloc(sizeof(int) * (q1+q2));
    int i = 0, j = q1, k = 0;

    while (i < q1 && j < (q1+q2)) //i: vetor 1, j: vetor 2, k: vetor auxiliar;
    {
        if (v[i] < v[j])
        {
            vAux[k] = v[i];
            i++;
        }
        else
        {
            vAux[k] = v[j];
            j++;
        }
        k++;
    }
    while (i < q1)
    {
        vAux[k] = v[i];
        k++;
        i++;
    }
    while (j < (q1+q2))
    {
        vAux[k] = v[j];
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
    int *v = malloc(sizeof(int) * (q1 + q2));
    
    for (i = 0; i < (q1+q2); i++)
    {
        scanf("%d", &v[i]);
    }

    

    int *vetorOrdenado = intercala(v, q1, q2);
    imprimir(vetorOrdenado, (q1+q2));
    free(v);
    free(vetorOrdenado);
    return 0;
}