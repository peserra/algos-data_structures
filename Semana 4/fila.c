// gcc fila.c -o prog.exe
#include <stdio.h>
#include <stdlib.h>

typedef struct tFila {
    int *itens;       // ponteiro (vetor) de inteiros
    int inicio, fim;  // fila: acesso sempre pelo inicio e fim
    int tamanho;      // tamanho maximo alocado
} Fila;

// Recebe o tamanho alocado para o vetor.
// Devolve um ponteiro para Fila.
Fila * criaFilaVazia (int tamanho)
{
    Fila * fila = malloc(sizeof(Fila));
    fila->tamanho = tamanho;
    fila->itens = malloc(sizeof(int) * tamanho);
    fila->inicio = -1;
    fila->fim = -1;
}

// Libera memoria: liberar fila->itens primeiro, depois a fila.
void liberaFila (Fila *fila)
{
    free(fila->itens);
    free(fila);
}

// Devolve 1 se Fila cheia, 0 caso contrario.
int cheia (Fila *fila)
{
    return fila->fim == fila->tamanho-1;
}

// Devolve 1 se Fila vazia, 0 caso contrario.
int vazia (Fila *fila)
{
    return fila->fim == -1;
}

// Insere uma chave x no fim da Fila, caso nao esteja cheia.
void enfileirar (Fila *fila, int x)
{
    if(!cheia(fila))
    {
        if(vazia(fila))
        {
            fila->inicio++;
        }
               
        fila->fim++;
        fila->itens[fila->fim] = x;      
    }
}

// Remove uma chave do inicio da Fila, caso nao esteja vazia.
// Devolve a chave removida, ou -1 caso contrario.
int desenfileirar (Fila *fila)
{
    if(!vazia(fila))
    {
        int x = fila->itens[fila->inicio];
        fila->inicio++;
        if(fila->inicio > fila->fim)
        {
            fila->inicio = fila->fim = -1;
        }
        return x;
    }
    return -1;
}

int main () {
    char op;
    int x, n, valor;
    scanf ("%d", &n);
    Fila *fila = criaFilaVazia(n);
    while (scanf (" %c", &op) != EOF) {
        switch (op) {
            case 'E': scanf ("%d", &x);
                      enfileirar(fila, x);
                      break; 
            case 'D': 
                valor = desenfileirar(fila);
                if (valor >= 0)
                {
                    printf("%d\n", valor);
                }
                break; 
        }
    }
    free(fila);
    return 0;
}