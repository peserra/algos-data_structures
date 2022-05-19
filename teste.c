#include<stdio.h>
#include<stdlib.h>
#include <string.h>



int main ()
{
    char teste[] = "dados";
    int soma = 0;
    for(int i = 0; i < 5; i++)
    {
        soma += teste[i];
    }
    printf("%d\n", soma);

    return 0;
}