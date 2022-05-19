// gcc intercalaStrings2.c -o prog.exe
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
char *intercala(char *v, int q1, int q2)
{
    char *vAux = malloc(sizeof(char) * (q1 + q2));
    int i = 0, j = q1, k = 0;

    while (i < q1 && j < (q1+q2))
    {
        if (v[i] < v[j])
        {
            vAux[k] = v[i];
            i++; k++;
        }
        else
        {
            vAux[k] = v[j];
            j++; k++;
        }
        
    }
    while (i < q1)
    {
        vAux[k] = v[i];
        k++; i++;
        
    }
    while (j < (q1+q2))
    {
        vAux[k] = v[j];
        k++, j++;
    }
    return vAux;
    
}

int main()
{
    int q1, q2, i;
    scanf ("%d", &q1);
    scanf ("%d", &q2);
    char *v = malloc (sizeof (char) * (q1+q2));
    
    for (i = 0; i < q1; i++) {
        scanf (" %c", &v[i]);
    }
    for (; i < q1+q2; i++) {
        scanf (" %c", &v[i]);
    }

    char *vOrdenado = intercala(v,q1,q2);
    imprimir(vOrdenado,(q1+q2));

    free(v);
    free(vOrdenado);
    return 0;
}
