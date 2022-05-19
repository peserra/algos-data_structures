// gcc LES.c -o prog.exe
#include <stdio.h>
#include <stdlib.h>
typedef struct tPilha {
    int *itens;     // ponteiro (vetor) de inteiros
    int topo;       // pilha: acesso sempre pelo topo
    int tamanho;    // tamanho maximo alocado
} Pilha;

// Recebe o tamanho alocado para o vetor.
// Devolve um ponteiro para Pilha.
Pilha * criaPilhaVazia (int tamanho)
{
    Pilha *pilha = malloc(sizeof(Pilha));
    pilha->tamanho = tamanho;
    pilha->itens = malloc(sizeof(int)*tamanho);
    pilha->topo = -1;
    return pilha;
}

// Libera memoria: liberar pilha->itens primeiro, depois a pilha.
void liberaPilha (Pilha *pilha)
{
    free(pilha->itens);
    free(pilha);
}

// Devolve 1 se Pilha cheia, 0 caso contrario.
int cheia (Pilha *pilha)
{
    return pilha->topo == pilha->tamanho-1;
}

// Devolve 1 se Pilha vazia, 0 caso contrario.
int vazia (Pilha *pilha)
{
    return pilha->topo == -1;
}

// Insere uma chave x no topo da Pilha, caso nao esteja cheia.
void empilha (Pilha *pilha, int x)
{
    if(!cheia(pilha))
    {
        pilha->topo++;
        pilha->itens[pilha->topo] = x;  
        
    }
}

// Remove uma chave do topo da Pilha, caso nao esteja vazia.
// Devolve a chave removida, ou -1 caso contrario.
int desempilha (Pilha *pilha)
{
    if(!vazia(pilha))
    {
        int x;
        x = pilha->itens[pilha->topo];
        pilha->topo--;
        return x;
    }
    return -1;
}

// Imprime os elementos da pilha, um por linha, do topo para a base.
void imprimePilhaTopo (Pilha *pilha)
{
    for(int i = pilha->topo; i >= 0; i--)
    {
        printf("%d\n", pilha->itens[i]);
    }
}

// Imprime os elementos da pilha, um por linha, da base para o topo.
void imprimePilhaBase (Pilha *pilha)
{
    for (int i = 0; i <= pilha->topo; i++)
    {
        printf("%d\n", pilha->itens[i]);
    }
}

int main () {
    char op;
    int n, x;
    scanf ("%d", &n); // tamanho alocado para a pilha
    Pilha *pilha = criaPilhaVazia(n);
    while (scanf (" %c", &op) != EOF) {
        switch (op) {
            case 'E': scanf ("%d", &x);
                      empilha(pilha,x);
                      break;
            case 'D': desempilha(pilha);
                      break;
            case 'T': imprimePilhaTopo(pilha);
                      break;
            case 'B': imprimePilhaBase(pilha);
                      break;
        }
    }
    liberaPilha(pilha);
    return 0;
}
