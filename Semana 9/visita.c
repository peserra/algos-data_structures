// gcc visita.c -o prog.exe
#include<stdlib.h>
#include<stdio.h>

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


// Recebe um ponteiro para a raiz de uma arvore.
// Imprime as chaves, de acordo com uma visita pre-ordem.
void imprimePreOrdem (Item *r)
{
    if(r != NULL)
    {
        printf("%d ", r->chave);
        imprimePreOrdem(r->esq);
        imprimePreOrdem(r->dir);
    }    
}

// Recebe um ponteiro para a raiz de uma arvore.
// Imprime as chaves, de acordo com uma visita in-ordem.
void imprimeInOrdem (Item *r)
{
    if(r != NULL)
    {
        imprimeInOrdem(r->esq);
        printf("%d ", r->chave);
        imprimeInOrdem(r->dir);
    }    
}

// Recebe um ponteiro para a raiz de uma arvore.
// Imprime as chaves, de acordo com uma visita pos-ordem.
void imprimePosOrdem (Item *r)
{
    if(r != NULL)
    {
        imprimePosOrdem(r->esq);
        imprimePosOrdem(r->dir);
        printf("%d ", r->chave);
    }
}

int main () {
    int n, i, x;
    scanf ("%d", &n);
    Arvore *arv = criaArvoreVazia ();
    for (i = 0; i < n; i++) {
        scanf ("%d", &x);
        inserir (arv, x);
    }
    if (!vazia (arv)) {
        printf ("Pre-ordem: ");
        imprimePreOrdem (arv->raiz);
        printf ("\nIn-ordem: ");
        imprimeInOrdem (arv->raiz);
        printf ("\nPos-ordem: ");
        imprimePosOrdem (arv->raiz);
        printf ("\n");
    }
    liberaArvore (arv);
    return 0;
}

