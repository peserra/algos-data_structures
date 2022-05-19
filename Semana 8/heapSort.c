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

// Devolve o indice do pai de i (i-1)/2 piso
int pai(int i)
{
    return (i - 1) / 2;
}

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
    int n = h->tamanho;
    return (n / 2) - 1;
}

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
void peneirar(Heap *h, int pai)
{
    int e = filhoEsq(pai), d = filhoDir(pai);
    int n = h->quantidade;
    int maiorfilho = e; // por convenção logica, o maior será o esquerdo

    if (e < n) // e < n significa que tem um elemento (indice e = 0, n = 1)
    {
        if(d < n && h->v[d] > h->v[e]) //muda o valor de maiorFilho caso o maior filho seja o direito e tenha mais de um elemento no vetor
        {
            maiorfilho = d;
        }
        if(h->v[maiorfilho] > h->v[pai]) //se o indice que for o maior filho for maior que o pai
        {
            troca(h->v, maiorfilho, pai); //troca os dois
            peneirar(h, maiorfilho); // o indice que essa função vai receber é o que era o maior filho antes da troca
        }
    }
}

// Recebe um ponteiro para um heap.
// Constroi um heap, chamando peneirar() para
// cada um dos pais, do ultimo pai ate a raiz.
void constroiHeap(Heap *h)
{
    for (int i = ultimoPai(h); i > -1; i--)
    {
        peneirar(h, i);
    }
}

// Recebe um vetor e o seu tamanho.
// Imprime o conteudo do vetor.
void imprime(int *v, int n)
{
    for(int i = 0; i < n-1; i++)
    {
        printf("%d ", v[i]);
    }
    if(n>0)
    {
        printf("%d\n", v[n-1]);
    }
}

// Recebe um ponteiro para um heap.
// Ordena as chaves pelo algoritmo HeapSort.
// Imprime o vetor apos chamar constroiHeap().
// A cada iteracao, imprime o vetor apos peneirar().
void heapSort(Heap *h)
{
    int n = h->quantidade;
    constroiHeap(h);
    imprime(h->v,n);
    for(int i = n-1; i > 0; i--)
    {
        troca(h->v, 0, i); //maximo na posição i
        h->quantidade --;
        peneirar(h,0);
        imprime(h->v, n);
    }
}

int main()
{
    int n, i;
    scanf("%d", &n);
    Heap *h = criaHeapVazio(n);
    for (i = 0; i < n; i++)
    {
        scanf("%d", &h->v[i]);
    }
    h->quantidade = n;
    heapSort(h);
    liberaHeap(h);
    return 0;
}