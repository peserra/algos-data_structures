// gcc ldde.c -o prog.exe
#include <stdio.h>
#include <stdlib.h>
typedef struct tItem
{
    int chave;
    struct tItem *ant, *prox; // ponteiros para anterior e proximo na lista
} Item;

typedef struct tLista
{
    Item *primeiro, *ultimo; // ponteiros para as extremidades a lista
    int quantidade;          // qtde de elementos na lista
} Lista;

// Aloca memoria para criar uma lista inicialmente vazia.
// Devolve o ponteiro para a lista alocada, com os campos inicializados:
// primeiro e ultimo vazios, e quantidade zero.
Lista *criaListaVazia()
{
    Lista *lista = malloc(sizeof(Lista));
    lista->primeiro = lista->ultimo = NULL;
    lista->quantidade = 0;
    return lista;
}

// Recebe um inteiro x.
// Aloca memoria para criar um novo item.
// Inicializa o valor da chave com x e os ponteiros ant e prox com vazio.
Item *criaItem(int x)
{
    Item *item = malloc(sizeof(Item));
    item->chave = x;
    item->ant = item->prox = NULL;
    return item;
}

// Deve-se liberar primeiro a cadeia de itens.
// Depois, no final, liberar o ponteiro da lista.
void liberaLista(Lista *lista)
{
    Item *anterior = NULL, *atual = lista->primeiro;
    while (atual != NULL)
    {
        anterior = atual;
        atual = atual->prox;
        free(anterior);
    }
    free(lista);
}

// Recebe um ponteiro para uma lista.
// Devolve 1 se lista vazia, 0 caso contrario.
int vazia(Lista *lista)
{
    return lista->primeiro == NULL;
}

// Imprime o conteudo da lista, do incio para o fim.
void imprimir(Lista *lista)
{
    Item *atual = lista->primeiro;
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

// Imprime o conteudo da lista, do fim para o incio.
void imprimirReverso(Lista *lista)
{
    Item *atual = lista->ultimo;
    while (atual != NULL && atual->ant != NULL)
    {
        printf("%d ", atual->chave);
        atual = atual->ant;
    }
    if (atual != NULL)
    {
        printf("%d\n", atual->chave);
    }
}
// recebe ponteiro para lista e chave x
// busca posicao para inserir ou remover
// devolve ponteiro do item com chave <= x
Item *buscaPosicao(Lista *lista, int x)
{
    Item *atual = lista->primeiro;
    while (atual != NULL && x > atual->chave)
    {
        atual = atual->prox;
    }
    return atual;
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
        lista->primeiro = lista->ultimo = novo;
        lista->quantidade++;
    }
    else
    {
        Item *atual = buscaPosicao(lista, x);
        // ignora repetições
        if (atual != NULL && atual->chave == x)
        {
            free(novo);
        }
        else
        {
            // caso 2: insere  no fim
            if (atual == NULL)
            {
                (lista->ultimo)->prox = novo; // proximo do ultimo aponta para o novo
                novo->ant = lista->ultimo;    // anterior do novo é ultimo anterior
                lista->ultimo = novo;         // ultimo da lista é o novo elemento
            }
            // caso 3: insere  no começo
            else if (atual->ant == NULL) // se a busca retornou o primeiro elemento, o anterior dele é nulo
            {
                lista->primeiro = novo; // primeiro da lista aponta novo
                atual->ant = novo;      // anterior do atual (agora o segundo elemento) aponta para o novo primeiro da lista
            }
            // caso 4: isere no meio
            else
            {
                (atual->ant)->prox = novo; // o próximo do anterior do atual é o novo
                novo->ant = atual->ant;    // o anterior do novo é o anterior do atual (lembrando que o atual é o valor que x <= aquele valor)
                atual->ant = novo;         // anterior do atual é o novo
            }
            novo->prox = atual;
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
    if (!vazia(lista))
    {
        Item *atual = buscaPosicao(lista, x);
        if (atual != NULL && atual->chave == x) // encontra a chave x
        {
            // remove do inicio
            if (atual->ant == NULL)
            {
                lista->primeiro = atual->prox;
                if (atual->prox != NULL)    // se lista nao tem so um elemento
                {
                    (atual->prox)->ant = NULL;
                }
                else
                {
                    lista->ultimo = NULL;   // lista esvaziou
                }
            }
            // remove do fim
            else if (atual->prox == NULL)
            {
                (atual->ant)->prox = NULL;
                lista->ultimo = atual->ant;
            }
            // remove do meio
            else
            {
                (atual->ant)->prox = atual->prox;
                (atual->prox)->ant = atual->ant;
            }
            lista->quantidade--;
            free(atual);
        }
    }
}

int main ()
{
    char op;
    int x;
    Lista *lista = criaListaVazia();
    while(scanf(" %c", &op) != EOF)
    {
        switch(op)
        {
            case 'I':
                scanf("%d", &x);
                inserir(lista, x);
                break;
            case 'E':
                scanf("%d", &x);
                remover(lista, x);
                break;
            case 'M':
                imprimir(lista);
                break;
            case 'R':
                imprimirReverso(lista);
                break;            
        }

    }
    liberaLista(lista);
    return 0;
}
