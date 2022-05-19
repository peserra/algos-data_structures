#include <stdio.h>
#include <stdlib.h>

typedef struct tHeap
{
    int *v;
    int tamanho;    // tamanho do vetor alocado
    int quantidade; // qtde elementos inseridos
} Heap;

// Recebe o tamanho do vetor para o heap.
// Aloca um heap, aloca o vetor do heap, ajusta o tamanho,
// a quantidade inicia com zero.
// Devolve um ponteiro para o heap recem-criado.
Heap *criaHeapVazio(int tam)
{
    Heap *h = malloc(sizeof(Heap));
    h->v = malloc(sizeof(int) * tam);
    h->tamanho = tam;
    h->quantidade = 0;
    return h;
}

// Recebe um ponteiro para um heap.
// Libera o vetor e depois o ponteiro do heap.
void liberaHeap(Heap *h)
{
    free(h->v);
    free(h);
}

// Devolve o indice do pai de i.
int pai(int i)
{
    return (i - 1) / 2;
}

// Devolve o indice do filho esquerdo de i.
int filhoEsq(int i)
{
    return 2 * i + 1;
}

// Devolve o indice do filho direito de i.
int filhoDir(int i)
{
    return 2 * i + 2;
}

// Recebe um ponteiro para um heap.
// Devolve o indice do ultimo pai: chao(n/2)-1,
// onde n é a quantidade de elementos do heap.
int ultimoPai(Heap *h)
{
    int n = h->quantidade;
    return n / 2 - 1;
}

// Troca v[i] <-> v[j] em um vetor
void troca(int *v, int i, int j)
{
    int tmp = v[i];
    v[i] = v[j];
    v[j] = tmp;
}
// Recebe um ponteiro para um heap e um indice pai.
// Se a chave do pai eh menor que a de algum filho,
// faz a troca e chama recursivamente.
// A troca deve ser feita pela chave do maior filho.
// No caso de empate, prefira trocar com o filho esquerdo.
void desceChave(Heap *h, int pai)
{
    int e = filhoEsq(pai), d = filhoDir(pai);
    int n = h->quantidade;
    int menorFilho = e; // por convenção logica, o maior será o esquerdo

    if (e < n) // e < n significa que tem um elemento (indice e = 0, n = 1)
    {
        if (d < n && h->v[d] < h->v[e]) // muda o valor de maiorFilho caso o maior filho seja o direito e tenha mais de um elemento no vetor
        {
            menorFilho = d;
        }
        if (h->v[menorFilho] < h->v[pai]) // se o indice que for o maior filho for maior que o pai
        {
            troca(h->v, menorFilho, pai); // troca os dois
            desceChave(h, menorFilho);    // o indice que essa função vai recebeer é o que era o maior filho antes da troca
        }
    }
}
// Recebe um ponteiro para um heap.
// Constroi um heap, chamando desceChave() para cada um dos pais, do ultimo pai ate a raiz.
void constroiHeap(Heap *h)
{
    for (int i = ultimoPai(h); i > -1; i--)
    {
        desceChave(h, i);
    }
}
// Recebe um vetor e o seu tamanho.
// Imprime o conteudo do vetor.
void imprime(int *v, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        printf("%d ", v[i]);
    }
    if (n > 0)
    {
        printf("%d\n", v[n - 1]);
    }
}
// Recebe um ponteiro para um heap.
// Devolve 1 se heap vazio, 0 caso contrario.
int vazio(Heap *h)
{
    if (h->quantidade == 0)
    {
        return 1;
    }
    return 0;
}

// Recebe um ponteiro para um heap.
// Devolve 1 se heap cheio, 0 caso contrario.
int cheio(Heap *h)
{
    return h->quantidade == h->tamanho;
}

// Apos inserir uma nova chave em um heap, pode ser necessario
// "subir" esta nova chave para manter a propriedade estrutural do heap.
// Este procedimento recursivo recebe o ponteiro para o heap e o indice i.
void sobeChave(Heap *h, int i)
{
    int p = pai(i);                 // p é o pai do indice i
    if (i > 0 && h->v[i] < h->v[p]) // se i não tem pai e i > que seu pai
    {
        troca(h->v, i, p);
        sobeChave(h, p);
    }
}

// Recebe um ponteiro para um heap e uma chave x.
// Insere a chave no fim do vetor e chama sobeChave().
void inserir(Heap *h, int x)
{
    if (!cheio(h))
    {
        h->v[h->quantidade++] = x;
        sobeChave(h, h->quantidade - 1);
    }
}

// Recebe um ponteiro para um heap.
// Assume que o heap nao esta vazio.
// Remove a chave da raiz e devolve o seu valor.
// Para remover a raiz, troque as chaves da raiz com o ultimo elemento.
// Depois, chame desceChave() para a nova raiz.
int extraiMinimo(Heap *h)
{
    int minimo = h->v[0]; // maximo sempre está na raiz do heap
    h->quantidade--;
    if (!vazio(h)) // se heap na vazio, verifica se desce a chave a partir do primeiro
    {
        troca(h->v, 0, h->quantidade);
        desceChave(h, 0);
    }
    return minimo;
}

// Recebe um ponteiro para um heap e uma chave x.
// Procura o indice i da chave x.
// Se encontrar, remove x do heap.
// Para remover x, troque as chaves de i com o ultimo elemento.
// Depois, chame desceChave() para i.
void remover(Heap *h, int x)
{
    int n = h->tamanho;

    for (int i = 0; i < n; i++)
    {
        if (h->v[i] == x)
        {
            h->quantidade--;
            if (!vazio(h))
            {
                troca(h->v, i, h->quantidade);
                desceChave(h, i);
            }
            break;
        }
    }    
}

int main()
{
    int tam;
    scanf("%d", &tam);
    Heap *h = criaHeapVazio(tam);
    char op;
    int x;
    while (scanf(" %c", &op) != EOF)
    {
        switch (op)
        {
        case 'I':
            scanf("%d", &x);
            inserir(h, x);
            break;
        case 'R':
            scanf("%d", &x);
            remover(h, x);
            break;
        case 'E':
            if (!vazio(h))
            {
                x = extraiMinimo(h);
                printf("[%d]\n", x);
            }
            break;
        case 'P':
            if (!vazio(h))
            {
                imprime(h->v, h->quantidade);
            }
            break;
        }
    }
    liberaHeap(h);
    return 0;
}