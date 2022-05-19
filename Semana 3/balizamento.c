// gcc 49-balizamento2.c -o prog.exe
#include <stdio.h>
#include <stdlib.h>

typedef struct tAtleta
{
    char nome[99];
    int min, seg, cen;
    double tempo;
} Atleta;

// copiado do exercicio 32
void insertionSort(Atleta *atleta, int n)
{
    int i, j;
    Atleta temp;

    for (j = 1; j < n; j++)
    {

        temp = atleta[j];
        i = j - 1;

        while (i >= 0 && temp.tempo < atleta[i].tempo)
        {
            atleta[i + 1] = atleta[i];
            i--;
        }

        atleta[i + 1] = temp;
    }
}

// Recebe recebe estrutura Atleta numero de nadadores, posicao de inicio, numero de raias 
// Imprime conforme numero de nadadores por série.
void imprimirSerie(Atleta *A, int nadadores, int inicio, int raias)
{

    int i, meio, aux;

    if (raias % 2 == 0) //determina o meio de acordo com o numero de raias
    {
        meio = raias / 2;
    }
    else
    {
        meio = raias / 2 + 1;
    }

    aux = meio; 

    for (i = 0; i < nadadores; i++) 
    {
        // alterna nadadores (meio, meio -1, meio +1, meio -2, meio +2 ....)
        if (i % 2 == 0) 
        {
            aux -= i;
        }
        else
        {
            aux += i;
        }

        printf("Raia %d: %s\n", aux, A[inicio].nome);
        inicio++;   //desloca no vetor
    }
}



int main()
{

    int i, n, m, series, contador, aux = 0, aux2 = 0;
    scanf("%d", &n);                                // numero de raias
    scanf("%d", &m);                                // numero de nadadores
    Atleta *atletas = malloc(sizeof(Atleta) * m);   //cria vetor de atletas
    for (i = 0; i < m; i++)
    {
        scanf("%s %d %d %d", atletas[i].nome, &atletas[i].min, &atletas[i].seg, &atletas[i].cen);
        
        atletas[i].tempo = atletas[i].min + atletas[i].seg * 0.01 + atletas[i].cen * 0.0001; //Para ordenar o vetor, transforma o tempo em uma coisa só
        if (atletas[i].tempo == 0)
        {
            atletas[i].tempo = 100;
        }
    }

    insertionSort(atletas, m);
    // Receber e imprimir as series
    aux = m;                 //numero de atletas
    contador = m;            //numero de atletas
    if (n >= m)             //numero de raias >= numero de atletas
    {
        series = 1;
        aux2 = m;
    }
    else if (m % n == 0)    //numero de atletas é multiplo do numero de raias
    {
        series = m / n;
        aux2 = n;
    }
    else
    {
        series = m / n + 1;
        aux2 = m % n;       //atletas que sobram
        aux -= aux2;        //reduzir do total de atletas
        while (aux2 < 3)    //tem que ter pelo menos 3 atletas por serie, reduz 
        {
            aux--;          //faz com que atletas sejam reduzidos até que a serie tenha pelo menos 3    
            aux2++;
        }
    }

    if (series > 1)
    {
        printf("%d series\n", series);
    }
    else
    {
        printf("%d serie\n", series);
    }

    for (i = 1; i <= series; i++)
    {
        printf("%da. serie\n", i);
        if (i == 1)
        {

            contador -= aux2;
            imprimirSerie(atletas,aux2, contador, n);
        }
        else if (i == 2 && ((aux % n) != 0))
        {

            contador -= (aux % n);
            imprimirSerie(atletas,(aux % n), contador, n);
        }
        else
        {

            contador -= n;
            imprimirSerie(atletas, n, contador, n);
        }
    }

    return 0;
}