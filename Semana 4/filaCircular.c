#include<stdio.h>
#include<stdlib.h>

typedef struct tFilaCircular {
    int *itens;       // ponteiro (vetor) de inteiros
    int inicio, fim;  // fila: acesso sempre pelo inicio e fim
    int tamanho;      // tamanho maximo alocado
} FilaCircular;

// Recebe o tamanho alocado para o vetor.
// Devolve um ponteiro para FilaCircular.
FilaCircular * criaFilaCircularVazia (int tamanho)
{
    FilaCircular * filaC = malloc(sizeof(FilaCircular));
    filaC->tamanho = tamanho;
    filaC->itens = malloc(sizeof(int) * tamanho);
    filaC->inicio = filaC->fim = 0;
}

// Libera memoria: liberar fila->itens primeiro, depois a fila.
void liberaFilaCircular (FilaCircular *fila)
{
    free(fila->itens);
    free(fila);
}

// Devolve 1 se FilaCircular cheia, 0 caso contrario.
int cheia (FilaCircular *fila)
{
    return (fila->fim + 1) % fila->tamanho == fila->inicio;
}

// Devolve 1 se FilaCircular vazia, 0 caso contrario.
int vazia (FilaCircular *fila)
{
    return fila->inicio == fila->fim;
}

// Insere uma chave x no fim da FilaCircular, caso nao esteja cheia.
void enfileirar (FilaCircular *fila, int x)
{
    if(!cheia(fila))
    {
        fila->itens[fila->fim] = x;
        fila->fim = (fila->fim + 1) % fila->tamanho; 
    }
}

// Remove uma chave do inicio da FilaCircular, caso nao esteja vazia.
// Devolve a chave removida, ou -1 caso contrario.
int desenfileirar (FilaCircular *fila)
{
    if(!vazia(fila))
    {
        int x = fila->itens[fila->inicio];
        fila->inicio = (fila->inicio + 1) % fila->tamanho;
        return x;
    }
    return -1;
}

int main ()
{
    char op;
    int x,n;
    scanf("%d", &n);
    FilaCircular *fila = criaFilaCircularVazia(n);
    while(scanf(" %c", &op) != EOF)
    {
        switch(op)
        {
            case 'E':
                scanf("%d", &x);
                enfileirar(fila,x);
                break;
            case 'D':
                x = desenfileirar(fila);
                if(x>=0)
                {
                    printf("%d\n", x);
                }
                break;
        }
    }
    liberaFilaCircular(fila);
    return 0;
}