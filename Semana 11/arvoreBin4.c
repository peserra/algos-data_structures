// gcc arvoreBin4.c -o prog.exe
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// ESTRUTURAS
typedef struct tItem
{
    char palavra[20];
    int chave;
    struct tItem *pai, *esq, *dir;
} Item;

typedef struct tArvore
{
    int quantidade;
    Item *raiz;
} Arvore;

// CRIAR VAZIOS
Item *criaItem(char *x)
{
    Item *novo = malloc(sizeof(Item));
    strcpy(novo->palavra, x);
    int soma = 0;
    for (int i = 0; i < 20; i++)
    {
        soma += novo->palavra[i];
    }
    novo->chave = soma;
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
void PreOrdem(Item *raiz)
{
    if (raiz != NULL)
    {
        printf("[%d]:%s\n", raiz->chave, raiz->palavra);
        PreOrdem(raiz->esq);
        PreOrdem(raiz->dir);
    }
}
void imprimirPreOrdem(Arvore *arvore)
{
    if (!vazia(arvore))
    {
        PreOrdem(arvore->raiz);
        printf("\n");
    }
}
void InOrdem(Item *raiz)
{
    if (raiz != NULL)
    {
        InOrdem(raiz->esq);
        printf("[%d]:%s\n", raiz->chave, raiz->palavra);
        InOrdem(raiz->dir);
    }
}
void imprimirInOrdem(Arvore *arvore)
{
    if (!vazia(arvore))
    {
        InOrdem(arvore->raiz);
        printf("\n");
    }
}
void PosOrdem(Item *raiz)
{
    if (raiz != NULL)
    {
        PosOrdem(raiz->esq);
        PosOrdem(raiz->dir);
        printf("[%d]:%s\n", raiz->chave, raiz->palavra);
    }
}
void imprimirPosOrdem(Arvore *arvore)
{
    if (!vazia(arvore))
    {
        PosOrdem(arvore->raiz);
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

void inserir(Arvore *arvore, char *x)
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
        Item *atual = buscaPosicao(arvore, novo->chave);
        // ignorar chaves repetidas
        if (atual->chave == novo->chave)
        {
            free(novo);
        }
        else
        {
            if (novo->chave < atual->chave)
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

// FUCOES EXTRAS
int isFolha(Item *item)
{
    return item != NULL && item->esq == NULL && item->dir == NULL;
}
int isRaiz(Item *item)
{
    return item != NULL && item->pai == NULL;
}
int isFilhoEsquerdo(Item *item)
{
    return !isRaiz(item) && (item->pai)->esq == item;
}
int isFilhoDireito(Item *item)
{
    return !isRaiz(item) && (item->pai)->dir == item;
}
int apenasUmFilho(Item *item)
{
    return !isFolha(item) && (item->esq == NULL || item->dir == NULL);
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

// ORGANIZAR OS PONTEIROS
void ajustaPonteiros(Arvore *arvore, Item *atual, Item *neto)
{
    if (isFilhoEsquerdo(atual))
    {
        // esquerdo do pai do atual (avo) = neto
        (atual->pai)->esq = neto;
    }
    else if (isFilhoDireito(atual))
    {
        // direito do pai do atual (avo) = neto
        (atual->pai)->dir = neto;
    }
    else
    {
        // atual é raiz, ultimo elemento foi removido
        arvore->raiz = neto;
    }
    if (neto != NULL)
    {
        neto->pai = atual->pai;
    }
}
// REMOVER
/*
    Recebe ponteiro para uma arvore e uma chave
    Remove a chave da arvore, caso exista
    Ignora chaves inexistentes
    caso 1: remove uma folha
    caso 2: o item removido tem apenas 1 filho
    caso 3: o item removido tem dois filhos e deve ser substituido pelo sucessor
*/
void remover(Arvore *arvore, char *x)
{
    if (!vazia(arvore))
    {
        int id = 0;
        for (int i = 0; i < strlen(x); i++)
        {
            id += x[i];
        }
        // printf("ID:%d\n", id); //debug
        Item *atual = buscaPosicao(arvore, id);

        if (strcmp(atual->palavra,x) == 0) // encontrou chave x, tem que remover
        {
            //printf("ENTROU AQUI\n"); //debug
            // caso 1: se atual é folha
            if (isFolha(atual))
            {
                ajustaPonteiros(arvore, atual, NULL);
            }
            // caso 2: tem apenas 1 filho
            else if (apenasUmFilho(atual))
            {
                Item *neto = atual->esq;
                if (neto == NULL)
                {
                    neto = atual->dir;
                }
                ajustaPonteiros(arvore, atual, neto);
            }
            // caso 3: tem dois filhos
            else
            {
                // substitui item removido pelo sucessor
                Item *suc = sucessor(atual);
                Item *neto = suc->dir; // suc nao tem filho esquerdo
                // remove "suc"
                ajustaPonteiros(arvore, suc, neto);
                // substitui atual <-> suc
                // filhos de "suc"
                suc->esq = atual->esq;
                suc->dir = atual->dir;
                if (suc->esq != NULL)
                {
                    (suc->esq)->pai = suc;
                }
                if (suc->dir != NULL)
                {
                    (suc->dir)->pai = suc;
                }
                // pai
                ajustaPonteiros(arvore, atual, suc);
            }
            //printf("*REMOVIDO* %s\n", atual->palavra); //debug
            arvore->quantidade--;
            free(atual);
        }
    }
}

// MAIN
int main()
{
    char op[20];
    char palavra[20];
    Arvore *arv = criaArvoreVazia();
    while (scanf("%s", op) != EOF)
    {
        if (strcmp(op, "insert") == 0)
        {
            scanf(" %s", palavra);
            inserir(arv, palavra);
        }
        else if (strcmp(op, "delete") == 0)
        {
            scanf(" %s", palavra);
            remover(arv, palavra);
            // printf("\n");
        }
        else if (strcmp(op, "pre-order") == 0)
        {
            imprimirPreOrdem(arv);
        }
        else if (strcmp(op, "in-order") == 0)
        {
            imprimirInOrdem(arv);
        }
        else if (strcmp(op, "post-order") == 0)
        {
            imprimirPosOrdem(arv);
        }
    }
    liberaArvore(arv);
    return 0;
}