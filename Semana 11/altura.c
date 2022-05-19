//gcc altura.c -o prog.exe
#include <stdio.h>
#include <stdlib.h>

typedef struct tItem
{
    int chave;
    struct tItem *pai, *esq, *dir;
} Item;

typedef struct tArvore
{
    Item *raiz;
    int quantidade;
} Arvore;

// Recebe uma chave x.
// Aloca memoria para um novo item, inicializa campos:
// chave x e ponteiros todos NULL.
// Devolve o ponteiro alocado.
Item *criaItem(int x)
{
    Item *item = malloc(sizeof(Item));
    item->chave = x;
    item->pai = item->dir = item->esq = NULL;
    return item;
}
// Aloca memoria para uma arvore.
// Inicializa arvore vazia: raiz vazia e qtde zero.
// Devolve o ponteiro alocado.
Arvore *criaArvoreVazia()
{
    Arvore *arvore = malloc(sizeof(Arvore));
    arvore->raiz = NULL;
    arvore->quantidade = 0;
    return arvore;
}
void liberaPosOrdem(Item *i)
{
    if (i != NULL)
    {
        liberaPosOrdem(i->esq);
        liberaPosOrdem(i->dir);
        //printf("libera: %d\n", i->chave);
        free(i);
    }
}

// Recebe um ponteiro para uma arvore.
// Libera memoria: libera itens da arvore e finalmente a estrutura da arvore.
//      libera em pós ordem nesse exercicio
void liberaArvore(Arvore *arvore)
{
    liberaPosOrdem(arvore->raiz);
    free(arvore);
}

// Recebe um ponteiro para uma arvore.
// Devolve 1 se arvore vazia, 0 caso contrario.
int vazia(Arvore *arv)
{
    return arv->raiz == NULL;
}

void imprimeInOrdem(Item *i)
{
    if(i != NULL)
    {
        imprimeInOrdem(i->esq);
        printf("%d ", i->chave);
        imprimeInOrdem(i->dir);
    }
} 

// Recebe um ponteiro para uma arvore.
// Imprime o conteudo da arvore "em ordem".
void imprimir(Arvore *arv)
{
    if(!vazia(arv))
    {
        imprimeInOrdem(arv->raiz);
        printf("\n");
    }
}
// Recebe um ponteiro para arvore e uma chave x
// Assume que arvore nao é vazia
// Devolve o pai da posicao de insercao, ou o ponteiro do item com chave x
Item *buscaPosicao(Arvore *arv, int x)
{
    Item *atual = arv->raiz, *anterior = NULL; // ponteiros para buscar posicao
    while (atual != NULL)
    {
        anterior = atual;
        if (x == atual->chave) // se a chave for repetida, insere no mesmo lugar
        {
            return atual;
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
    return anterior;
}

// Recebe um ponteiro para uma arvore e uma chave x.
// Insere uma nova chave na arvore.
// Ignora chaves repetidas.
void inserir(Arvore *arv, int x)
{
    Item *novo = criaItem(x);
    // caso 1:
    if (vazia(arv))
    {
        arv->raiz = novo;
        arv->quantidade = 1;
    }
    //caso 2
    else
    {   //busque posicao de insercao
        Item *atual = buscaPosicao(arv, x); 
        //se a chave for repetida, ignore
        if(atual->chave == x)
        {
            free(novo);
        }
        else
        {   // se x for menor que o atual, insira a esquerda
            if(x < atual->chave)
            {
                atual->esq = novo; //esse atual esta com o valor de anterior (retornado na buscaposicao)
            }
            // se nao, insira a direita
            else
            {
                atual->dir = novo;
            }
            //ajusta o pai do novo item
            novo->pai = atual;
            //incrementa quantidade da arvore
            arv->quantidade++;
        }
    }
}

int alturaRecursiva(Item *i)
{
    Item *atual = i;
    int esquerda, direita;
    if(atual == NULL) //se a arvore for vazia, nao temm altura
    {
        return -1;
    }
    else
    {
        esquerda = alturaRecursiva(atual->esq);
        direita = alturaRecursiva(atual->dir);
        if(esquerda > direita)
        {
            return esquerda + 1;
        }
        else
        {
            return direita + 1;
        }
    }
}

int altura(Arvore *arv)
{
    if(!vazia(arv))
    {
        return alturaRecursiva(arv->raiz);
    }
}

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
    //imprimir(arv);
    int alturaArvore = altura(arv);
    printf("%d\n", alturaArvore); 
    liberaArvore(arv);
    return 0;
}
