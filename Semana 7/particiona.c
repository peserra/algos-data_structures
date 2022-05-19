// gcc particiona.c -o prog.exe
#include <stdio.h>
#include <stdlib.h>
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
void troca(int *v, int i, int j)
{
    int temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

int *particiona(int *v, int e, int d, int p)
{
    troca(v, d - 1, p);
    int j = e, i = j - 1;
    while (j < d-1)
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
    printf("%d\n", i);
    return v;
}
int main()
{
    int n, p;
    scanf("%d", &n);
    scanf("%d", &p);
    int *v = malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &v[i]);
    }
    int *vParticionado = particiona(v, 0, n, p);
    imprimir(vParticionado,n);
    free(v);
    return 0;
}