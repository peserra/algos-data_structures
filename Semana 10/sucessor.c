// gcc sucessor.c -o prog.exe
#include <stdio.h>
#include <stdlib.h>
// ESTRUTURAS
typedef struct tItem
{
    int chave;
    struct tItem *pai, *esq, *dir;
} Item;

typedef struct tArvore
{
    int quantidade;
    Item *raiz;
} Arvore;

// CRIAR VAZIOS
Item *criaItem(int x)
{
    Item *novo = malloc(sizeof(Item));
    novo->chave = x;
    novo->pai = novo->esq = novo->dir = NULL;
    return novo;
}

Arvore *criaArvoreVazia()
{
    Arvore *arvore = malloc(sizeof(Arvore));
    arvore->raiz = NULL;
    arvore->quantidade = 0;
    return arvore;
}

// LIBERAR
void liberaPosOrdem(Item *raiz)
{
    if (raiz != NULL)
    {
        liberaPosOrdem(raiz->esq);
        liberaPosOrdem(raiz->dir);
        printf("libera: %d\n", raiz->chave); // para mostrar qual raiz esta sendo liberada
        free(raiz);
    }
}

void liberaArvore(Arvore *arvore)
{
    liberaPosOrdem(arvore->raiz);
    free(arvore);
}

// VAZIA
int vazia(Arvore *arvore)
{
    return arvore->raiz == NULL; // 1 quando condição é TRUE
}

// IMPRIMIR
void imprimeInOrdem(Item *raiz)
{
    if (raiz != NULL)
    {
        imprimeInOrdem(raiz->esq);
        printf("%d ", raiz->chave);
        imprimeInOrdem(raiz->dir);
    }
}

void imprimir(Arvore *arvore)
{
    if (!vazia(arvore))
    {
        imprimeInOrdem(arvore->raiz);
        printf("\n");
    }
}

// BUSCAR POSICAO E INSERIR
Item *buscaPosicao(Arvore *arvore, int x)
{
    Item *atual = arvore->raiz, *anterior = NULL;
    while (atual != NULL)
    {
        anterior = atual;
        if (x == atual->chave)
        {
            return atual; // caso ja tenha a chave buscada na arvore, retorna atual
        }
        else if (x < atual->chave)
        {
            atual = atual->esq;
        }
        else
        {
            atual = atual->dir;
        }
    }
    return anterior; // retorna o pai do item buscado
}

void inserir(Arvore *arvore, int x)
{
    Item *novo = criaItem(x);
    // caso 1: arvore vazia
    if (vazia(arvore))
    {
        arvore->raiz = novo;
        arvore->quantidade = 1;
    }
    else
    {
        // caso 2: busca posicao de insercao
        Item *atual = buscaPosicao(arvore, x);
        // ignorar chaves repetidas
        if (atual->chave == x)
        {
            free(novo);
        }
        else
        {
            if (x < atual->chave)
            {
                atual->esq = novo;
            }
            else
            {
                atual->dir = novo;
            }
            novo->pai = atual;
            arvore->quantidade++;
        }
    }
}

// SUCESSOR
//  Recebe ponteiro para um item e devolve o item de menor chave na subarvore.
Item *minimoRecursivo(Item *item)
{
    if (item != NULL)
    {
        if (item->esq) // desce recursivamente pelo filho esquerdo
        {
            minimoRecursivo(item->esq);
        }
        else
        {
            return item;
        }
    }
}

/*  Recebe um ponteiro para um item
    Caso exista na arvore, calcula seu sucessor
    Devolve o ponteiro para o sucessor, ou Null caso nao exxista
*/
Item *sucessor(Item *item)
{
    if (item->dir) // menor chave da subarvore da direita
    {
        return minimoRecursivo(item->dir);
    }
    else
    {
        return NULL;
    }
}

// MAIN
int main()
{
    int n, i, x;
    scanf("%d", &n);
    Arvore *arv = criaArvoreVazia();
    for (i = 0; i < n; i++)
    {
        scanf("%d", &x);
        inserir(arv, x);
    }
    while (scanf("%d", &x) != EOF)
    {
        Item *it = buscaPosicao(arv, x);
        if (it != NULL && it->chave == x)
        {
            Item *suc = sucessor(it);
            if (suc != NULL)
            {
                printf("Sucessor de %d: %d\n", x, suc->chave);
            }
            else
            {
                printf("Nao ha sucessor para a chave pesquisada.\n");
            }
        }
        else
        {
            printf("chave nao encontrada.\n");
        }        
    }
    liberaArvore(arv);
    return 0;
}