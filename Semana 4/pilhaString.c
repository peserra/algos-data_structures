// gcc pilhaInt.c -o prog.exe
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tPilha
{
    char **itens; // ponteiro "matriz" de chars
    int topo;     // pilha: acesso sempre pelo topo
    int tamanho;  // tamanho maximo alocado
} Pilha;

// Recebe o tamanho alocado para o vetor.
// Devolve um ponteiro para Pilha.
Pilha *criaPilhaVazia(int tamanho)
{
    Pilha *pilha = malloc(sizeof(Pilha));
    pilha->tamanho = tamanho;
    pilha->itens = malloc(sizeof(char *) * tamanho); // aloca um vetor de vetores de tamanho <tamanho> que recebe ponteiros de chars
    for (int i = 0; i < tamanho; i++)
    {
        pilha->itens[i] = malloc(sizeof(char) * 100); // aloca memoria para cada elemento de pilha itens (tamanho 100)
    }
    pilha->topo = -1;
    return pilha;
}

// Libera memoria: liberar pilha->itens primeiro, depois a pilha.
void liberaPilha(Pilha *pilha)
{
    // precisa liberar cada campo da matriz char **
    for (int i = 0; i < pilha->tamanho; i++)
    {
        free(pilha->itens[i]); // libera cada vetor em pilha.itens
    }
    free(pilha->itens); // libera o vetor pilha.itens
    free(pilha);        // libera a pilha
}

// Devolve 1 se Pilha cheia, 0 caso contrario.
int cheia(Pilha *pilha)
{
    return pilha->topo == pilha->tamanho - 1;
}

// Devolve 1 se Pilha vazia, 0 caso contrario.
int vazia(Pilha *pilha)
{
    return pilha->topo == -1;
}

// Insere uma chave x no topo da Pilha, caso nao esteja cheia.
void empilha(Pilha *pilha, char *x)
{
    if (!cheia(pilha))
    {
        pilha->topo++;
        strcpy(pilha->itens[pilha->topo], x);
    }
}

// Remove uma chave do topo da Pilha, caso nao esteja vazia.
// Devolve a chave removida, ou -1 caso contrario.
char *desempilha(Pilha *pilha)
{
    if (!vazia(pilha))
    {
        char *x;
        x = pilha->itens[pilha->topo];
        pilha->topo--;
        return x;
    }
    return ""; // return de string nula
}

void exibeTopo(Pilha *pilha)
{
    if (!vazia(pilha))
    {
        printf("%s\n", pilha->itens[pilha->topo]);
    }
}

// Imprime os elementos da pilha, um por linha, do topo para a base.
void imprimePilhaTopo(Pilha *pilha)
{
    if(!vazia(pilha))
    {
        for (int i = pilha->topo; i > 0; i--)
        {
            printf("%s ", pilha->itens[i]);
        }  
        printf("%s\n", pilha->itens[0]);

    }
    
    
}

// Imprime os elementos da pilha, um por linha, da base para o topo.
void imprimePilhaBase(Pilha *pilha)
{
    for (int i = 0; i <= pilha->topo - 1; i++)
    {
        printf("%s ", pilha->itens[i]);
    }
    if (pilha->tamanho > 0)
    {
        printf("%s\n", pilha->itens[pilha->topo]);
    }
}

int main()
{
    char op;
    char x[100]; //strings
    int n;
    scanf("%d", &n); // tamanho alocado para a pilha
    Pilha *pilha = criaPilhaVazia(n);
    while (scanf(" %c", &op) != EOF)
    {
        switch (op)
        {
        case 'E':
            scanf("%s", x);
            empilha(pilha, x);
            break;
        case 'D':
            strcpy(x, desempilha(pilha));
            break;
        case 'T':
            exibeTopo(pilha);
            break;
        case 'B':
            imprimePilhaBase(pilha);
            break;
        case 'X':            
            imprimePilhaTopo(pilha);            
            break;
        }
    }
    liberaPilha(pilha);
    return 0;
}
