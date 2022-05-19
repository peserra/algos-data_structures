// gcc intercalaStrings.c -o prog.exe
#include <stdio.h>
#include <stdlib.h>

void imprimir(char *v, int n)
{

    for (int i = 0; i < n-1; i++)
    {
        printf("%c", v[i]);
    }
    if (n > 0)
    {
        printf("%c\n", v[n-1]);
    }
}

// Recebe dois vetores ordenados, v1 e v2, e os seus respectivos tamanhos, q1 e q2.
// Devolve um novo vetor ordenado com a intercalacao de v1 e v2.
char *intercala(char *v1, char *v2, int q1, int q2)
{
    char *vAux = malloc(sizeof(char) * (q1 + q2));
    int i = 0, j = 0, k = 0;

    while (i < q1 && j < q2)
    {
        if (v1[i] < v2[j])
        {
            vAux[k] = v1[i];
            i++; k++;
        }
        else
        {
            vAux[k] = v2[j];
            j++; k++;
        }
        
    }
    while (i < q1)
    {
        vAux[k] = v1[i];
        k++; i++;
        
    }
    while (j < q2)
    {
        vAux[k] = v2[j];
        k++, j++;
    }
    return vAux;
    
}

int main()
{
    int q1, q2, i;
    scanf("%d", &q1);
    char *v1 = malloc(sizeof(char) * q1);
    for (i = 0; i < q1; i++)
    {
        scanf(" %c", &v1[i]); // um espaco em branco antes de %c
    }

    scanf("%d", &q2);
    char *v2 = malloc(sizeof(char) * q2);
    for (i = 0; i < q2; i++)
    {
        scanf(" %c", &v2[i]); // um espaco em branco antes de %c
    }

    char *vOrdenado = intercala(v1,v2,q1,q2);
    imprimir(vOrdenado,(q1+q2));

    free(v1);
    free(v2);
    free(vOrdenado);
    return 0;
}
