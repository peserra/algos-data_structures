// compilar: gcc lde.c -o prog.exe
#include <stdio.h>
#include <stdlib.h>
// estrutura do item (nó) da lista
typedef struct tItem
{
    int chave;
    struct tItem *prox; // ponteiro para proximo da lista
} Item;

// estrutura da própria lista
typedef struct tLista
{
    Item *inicio;   // ponteiro para o inicio da lista
    int quantidade; // qtde de elementos na lista
} Lista;

// Aloca memoria para criar uma lista inicialmente vazia.
// Devolve o ponteiro para a lista alocada, com os campos inicializados:
// inicio vazio e quantidade zero.
Lista *criaListaVazia()
{
    Lista *lista = malloc(sizeof(Lista)); // aloca memoria para a estrutura
    lista->inicio = NULL;                 // inicio vazio
    lista->quantidade = 0;                // quantidade zero
    return lista;                         // devolve poonteiro
}

// Recebe um inteiro x.
// Aloca memoria para criar um novo item.
// Inicializa o valor da chave com x e o ponteiro prox com vazio.
Item *criaItem(int x)
{
    Item *item = malloc(sizeof(Item)); // aloca memoria para um item
    item->chave = x;                   // valor inical da chave é x
    item->prox = NULL;                 // valor inicial do proximo é NULL
    return item;                       // retorna ponteiro
}

// Deve-se liberar primeiro a cadeia de itens.
// Depois, no final, liberar o ponteiro da lista.
void liberaLista(Lista *lista)
{
    // percorre a lista para liberar cada celula
    Item *atual = lista->inicio, *anterior = NULL; // valores iniciais dos ponteiros "atual" e "anterior"
    while (atual != NULL)
    {
        anterior = atual;
        atual = atual->prox;
        free(anterior);
        // quando chega no ultimo elemento (atual == NULL) o anterior dele (ultimo elemento) é liberado
    }
    free(lista); // libera a estrutura da lista
}

// Recebe um ponteiro para uma lista.
// Devolve 1 se lista vazia, 0 caso contrario.
int vazia(Lista *lista)
{
    return lista->inicio == NULL;
}

// Imprime o conteudo da lista.
void imprimir(Lista *lista)
{
    // tem que percorrer a lista para imprimir:
    Item *atual = lista->inicio;
    // pode precisar adicionar condição (!vazia)  aqui
    //  para imprimir item_1 item _2 ... item_n\n
    while (atual != NULL && atual->prox != NULL) // percorre até penultimo elemento
    {
        printf("%d ", atual->chave);
        atual = atual->prox;
    }
    if (atual != NULL) // ultimo elemento
    {
        printf("%d\n", atual->chave);
    }
}

// Recebe o ponteiro da lista e uma chave x.
// Devolve 1 se a lista contem a chave x, ou 0 caso contrario.
int buscar(Lista *lista, int x)
{
    Item *atual = lista->inicio;
    while (atual != NULL && x > atual->chave) // enquanto (nao é o fim da lista e x > elemento atual)
    {
        atual = atual->prox; // percorre a lista
    }
    if (atual == NULL) // percorreu a lista e nao encontrou chave
    {
        return 0;
    }
    return atual->chave == x; // retorna 1 pois chave foi encontrada
}

// Recebe um ponteiro para uma lista e uma chave x.
// Insere x na lista, caso ja nao exista.
// Ignora insercao de chaves repetidas.
// Deve tratar os 4 casos:
// (1) insercao em uma lista vazia;
// Se a lista nao estiver vazia, deve-se buscar a posicao de insercao.
// (2) insercao no fim da lista;
// (3) insercao no inicio da lista;
// (4) insercao no meio da lista.
void inserir(Lista *lista, int x)
{
    Item *novo = criaItem(x);

    // caso 1: lista vazia
    if (vazia(lista))
    {
        lista->inicio = novo;
        lista->quantidade = 1;
    }
    // se nao for vazia
    else
    {
        // busca posição
        Item *atual = lista->inicio, *anterior = NULL;
        while (atual != NULL && x > atual->chave) // percorre enquanto lista !vazia e atual >= x
        {
            anterior = atual;
            atual = atual->prox;
        }
        // ignorar chave repetida
        if (atual != NULL && atual->chave == x)
        {
            free(novo);
        }
        // se chave nao for repetida
        else
        {
            // caso 2: insere no fim
            if (atual == NULL)
            {
                anterior->prox = novo;
            }
            // caso 3: insere no começo
            else if (anterior == NULL)
            {
                lista->inicio = novo;
                novo->prox = atual;
            }
            // caso 4: insere no meio da lista
            else
            {
                anterior->prox = novo;
                novo->prox = atual;
            }
            lista->quantidade++;
        }
    }
}

// Recebe um ponteiro para uma lista e uma chave x.
// Se a lista nao estiver vazia, remove x da lista, caso exista.
// Deve tratar os 3 casos:
// (1) remocao do inicio da lista;
// (2) remocao do fim da lista;
// (3) remocao do meio da lista.
void remover(Lista *lista, int x)
{
    Item *atual = lista->inicio, *anterior = NULL;
    // busca o item
    while (atual != NULL && x > atual->chave) // percorre enquanto lista !vazia e atual >= x
    {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual != NULL && atual->chave == x) // encontrou a chave
    {
        // caso 1: remover do inicio
        // tem que vir primeiro para tratar do caso da lista com 1 elemento só
        if(anterior == NULL)
        {
            lista->inicio = atual->prox;
        }
        // caso 2: remover do final
        else if (atual->prox == NULL)
        {
            anterior->prox = NULL;
        }
        
        // caso 3: remover do meio
        else
        {
            anterior->prox = atual->prox;
        }
        free(atual);
        lista->quantidade--;
    }
}

// main
int main()
{
    char op;
    int x;
    Lista *lista = criaListaVazia();
    while (scanf(" %c", &op) != EOF)
    { // leitura com um espaco em branco antes de %c até fim do arquivo
        switch (op)
        {
        case 'I':
            scanf("%d", &x);
            inserir(lista, x);
            break;
        case 'R':
            scanf("%d", &x);
            remover(lista, x);
            break;
        case 'B':
            scanf("%d", &x);
            if (buscar(lista, x))
            {
                printf("SIM\n");
            }
            else
            {
                printf("NAO\n");
            }
            break;
        case 'L':
            imprimir(lista);
            break;
        }
    }
    liberaLista(lista);
    return 0;
}
