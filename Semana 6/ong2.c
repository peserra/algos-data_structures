// gcc ong.c -o prog.exe
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tItem
{
    char nome[100];   // vai ser usado para verificar se ja existe na lista
    int numPesquisas; // vai ser usado para ordenar na lista
    struct tItem *ant, *prox;

} Item;

typedef struct tLista
{
    Item *primeiro, *ultimo;
    int quantidade;

} Lista;

Lista *criaListaVazia()
{
    Lista *lista = malloc(sizeof(Lista));
    lista->primeiro = lista->ultimo = NULL;
    lista->quantidade = 0;
    return lista;
}

Item *criaItem(char *palavra) // cria um item que tem a palavra pesquisada
{
    Item *item = malloc(sizeof(Item));
    strcpy(item->nome, palavra);
    item->ant = item->prox = NULL;
    return item;
}

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

int vazia(Lista *lista)
{
    return lista->primeiro == NULL;
}
void imprimir(Lista *lista)
{
    Item *atual = lista->primeiro;
    while (atual != NULL)
    {
        printf("%s [%d]\n", atual->nome, atual->numPesquisas);
        atual = atual->prox;
    }
    
}

//TEM ALGUM BUG ESTRANHO NA HORA QUE INSERE O CRUZEIRO 2 VEZES

Item *buscaPosicao(Lista *lista, char *palavra) // busca palavra na lista para verificar se precisa remover o item
{
    Item *atual = lista->primeiro;
    while (atual != NULL && strcmp(palavra, atual->nome) != 0) // enquanto atual nao for nulo e as palavra != palavra do item na lista
    {
        atual = atual->prox;
    }
    return atual; // retorna um ponteiro que aponta para a palavra que ja existe na lista (para remover quando numero aumentar)
}

void removerRepetido(Lista *lista, Item *palavra) // recebe uma lista e um ponteiro para uma palavra nessa lista
{
    if (!vazia(lista))
    {
        // remove do inicio
        if (palavra->ant == NULL)
        {
            lista->primeiro = palavra->prox;
            if (palavra->prox != NULL) // se lista nao tem so um elemento
            {
                (palavra->prox)->ant = NULL;
            }
            else
            {
                lista->ultimo = NULL; // lista esvaziou
            }
        }
        // remove do fim
        else if (palavra->prox == NULL)
        {
            (palavra->ant)->prox = NULL;
            lista->ultimo = palavra->ant;
        }
        // remove do meio
        else
        {
            (palavra->ant)->prox = palavra->prox;
            (palavra->prox)->ant = palavra->ant;
        }
        lista->quantidade--;
        free(palavra);
    }
}

void inserirPalavra(Lista *lista, Item *palavra, Item *novo) //lista,palavra que ja existe, item novo
{
    novo->numPesquisas = palavra->numPesquisas;
    Item *atual = lista->primeiro;
    while (atual != NULL && atual->numPesquisas >= novo->numPesquisas)
    {
        atual = atual->prox;
    }
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

void listar(Lista *lista, char *palavra)
{
    Item *novo = criaItem(palavra);
    if (vazia(lista))
    {
        lista->primeiro = lista->ultimo = novo;
        lista->quantidade++;
        novo->numPesquisas = 1;
    }
    else
    {
        Item *buscar = buscaPosicao(lista, palavra);
        // buscar aqui pode ser null (nao tem o nome na lista) ou pode apontar pro item na lista

        if (buscar != NULL) // palavra ja encontrada na lista
        {
            buscar->numPesquisas++;
            inserirPalavra(lista, buscar, novo);
            removerRepetido(lista, buscar);
        }
        else // buscar == NULL não tem palavra na lista, insere no fim (tem que ser o else)
        {
            (lista->ultimo)->prox = novo;
            novo->ant = lista->ultimo;
            lista->ultimo = novo;
            novo->numPesquisas = 1;
        }
    }
}

int main()
{
    char palavra[100];
    Lista *lista = criaListaVazia();
    while (scanf(" %s", palavra) != EOF)
    {
        // testar se ja tem na lista
        // testar para inserir na nova posicao se precisar, com numero de pesquisa
        listar(lista, palavra);     
       
        
    }
    imprimir(lista);
    free(lista);
    return 0;
}