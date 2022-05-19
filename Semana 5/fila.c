// compilar: gcc fila.c -o prog.exe
#include <stdio.h>
#include <stdlib.h>

typedef struct tItem {
    int chave;
    struct tItem *prox;  // ponteiro para proximo na lista
} Item;

typedef struct tFila {
    Item *inicio, *fim;   // ponteiro para o inicio e fim da fila
} Fila;

// Aloca memoria para criar uma fila inicialmente vazia.
// Devolve o ponteiro para a fila alocada, com os campos inicializados:
// inicio e fim vazios.
Fila * criaFilaVazia ()
{
    Fila *fila = malloc (sizeof(Fila));
    fila->inicio = fila->fim = NULL;
    return fila;
}

// Recebe um inteiro x.
// Aloca memoria para criar um novo item.
// Inicializa o valor da chave com x e o ponteiro prox com vazio.
Item * criaItem (int x)
{
    Item *item = malloc(sizeof(Item));
    item->chave = x;
    item->prox = NULL;
    return item;
}

// Deve-se liberar primeiro a cadeia de itens.
// Depois, no final, liberar o ponteiro da fila.
void liberaFila (Fila *fila)
{
    Item *atual = fila->inicio, *anterior = NULL; 
    while (atual != NULL)
    {
        anterior = atual;
        atual = atual->prox;
        free(anterior);
    }
    free(fila);
}

// Recebe um ponteiro para uma fila.
// Devolve 1 se fila vazia, 0 caso contrario.
int vazia (Fila *fila)
{
    return fila->inicio == NULL;
}

// Imprime o conteudo da fila, do topo para a base.
void imprimir (Fila *fila)
{
    Item *atual = fila->inicio;
    while(atual != NULL && atual->prox != NULL)
    {
        printf("%d ", atual->chave);
        atual = atual->prox;
    }
    if (atual != NULL)
    {
        printf("%d\n", atual->chave);
    }
}

// Recebe um ponteiro para uma fila e uma chave x.
// Insere x no fim da fila.
void enfileirar (Fila *fila, int x)
{
    Item *novo = criaItem(x);
    // caso 1: fila vazia
    if(vazia(fila))
    {
        fila->inicio = fila->fim = novo;
    }
    // fila nao mais vazia
    else
    {
        (fila->fim)->prox = novo;
        fila->fim = novo;
    }

}

// Recebe um ponteiro para uma fila.
// Se fila nao vazia, remove elemento do inicio da fila.
// Devolve a chave removida.
// Devolve -1 se fila vazia.
int desenfileirar (Fila *fila)
{
    if (!vazia(fila))
    {
        Item *remover = fila->inicio;   // guarda o ponteiro para inicio
        int x = remover->chave;         // guarda chave para inicio
        fila->inicio = remover->prox;   // novo inicio recebe o proximo do antigo inicio
        if (fila->inicio == NULL)
        {
            fila->fim = NULL;
        }
        free(remover);
        return x;
    }
    return -1;
}

int main()
{
    char op;
    int x;
    Fila *fila = criaFilaVazia();
    while (scanf(" %c", &op) != EOF)
    { // leitura com espaco em branco antes de %c
        switch (op)
        {
        case 'E':
            scanf("%d", &x);
            enfileirar(fila, x);
            break;
        case 'D':
            x = desenfileirar(fila);
            if (x >= 0)
            {
                printf("<%d>\n", x);
            }
            break;
        case 'M':
            imprimir(fila);
            break;
        }
    }
    liberaFila(fila);
    return 0;
}