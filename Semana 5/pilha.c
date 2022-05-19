// compilar: gcc pilha.c -o prog.exe
#include <stdio.h>
#include <stdlib.h>

typedef struct tItem
{
    int chave;
    struct tItem *prox; // ponteiro para proximo na lista
} Item;

typedef struct tPilha
{
    Item *topo;     // ponteiro para o topo da pilha
    int quantidade; // qtde de elementos na pilha
} Pilha;

// Aloca memoria para criar uma pilha inicialmente vazia.
// Devolve o ponteiro para a pilha alocada, com os campos inicializados:
// topo vazio e quantidade zero.
Pilha *criaPilhaVazia()
{
    Pilha *pilha = malloc(sizeof(Pilha));
    pilha->topo = NULL;
    pilha->quantidade = 0;
    return pilha;
}

// Recebe um inteiro x.
// Aloca memoria para criar um novo item.
// Inicializa o valor da chave com x e o ponteiro prox com vazio.
Item *criaItem(int x)
{
    Item *item = malloc(sizeof(Item));
    item->chave = x;
    item->prox = NULL;
    return item;
}

// Deve-se liberar primeiro a cadeia de itens.
// Depois, no final, liberar o ponteiro da pilha.
void liberaPilha(Pilha *pilha)
{
    Item *anterior = NULL, *atual = pilha->topo;
    while (atual != NULL)
    {
        anterior = atual;
        atual = atual->prox;
        free(anterior);
    }
    free(pilha);
}

// Recebe um ponteiro para uma pilha.
// Devolve 1 se pilha vazia, 0 caso contrario.
int vazia(Pilha *pilha)
{
    return pilha->topo == NULL;
}

// Imprime o conteudo da pilha, do topo para a base.
void imprimir(Pilha *pilha)
{
    Item *atual = pilha->topo;
    while (atual != NULL && atual->prox != NULL)
    {
        printf("%d ", atual->chave);
        atual = atual->prox;
    }
    if (atual != NULL)
    {
        printf("%d\n", atual->chave);
    }
}

// Recebe um ponteiro para uma pilha e uma chave x.
// Insere x no topo da pilha.
void empilha(Pilha *pilha, int x)
{
    Item *novo = criaItem(x);
    novo->prox = pilha->topo; // antigo topo
    pilha->topo = novo;       // novo topo
    pilha->quantidade++;
}

// Recebe um ponteiro para uma pilha.
// Se pilha nao vazia, remove elemento do topo da pilha.
// Devolve a chave removida.
// Devolve -1 se pilha vazia.
int desempilha(Pilha *pilha)
{
    if (!vazia(pilha))
    {
        Item *remover = pilha->topo;
        int x = remover->chave;
        pilha->topo = remover->prox;
        pilha->quantidade--;
        free(remover);
        return x;
    }
    return -1;
}

int main()
{
    char op;
    int x;
    Pilha *pilha = criaPilhaVazia();
    while (scanf(" %c", &op) != EOF)
    { // leitura com espaco em branco antes de %c
        switch (op)
        {
        case 'E':
            scanf("%d", &x);
            empilha(pilha, x);
            break;
        case 'D':
            x = desempilha(pilha);
            if (x >= 0)
            {
                printf("[%d]\n", x);
            }
            break;
        case 'M':
            imprimir(pilha);
            break;
        }
    }
    liberaPilha(pilha);
    return 0;
}