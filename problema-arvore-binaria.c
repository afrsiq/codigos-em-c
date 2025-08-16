#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct No {
    char dado;
    struct No *esq, *dir;
}No;

No *criarNo(char dado){
    No *novo = (No*)malloc(sizeof(No));
    novo->dado = dado;
    novo->esq = novo->dir = NULL;
    return novo;
}

int encontrarPosicao(char *infixo, char elemento, int inicio, int fim){
    for (int i = inicio; i <= fim; i++) {
        if (infixo[i] == elemento) return i;
    }
    return -1;
}

No *construirArvore(char *prefixo, char *infixo, int *indicePre, int inicioIn, int fimIn){
    if (inicioIn > fimIn) return NULL;

    No *raiz = criarNo(prefixo[*indicePre]);
    (*indicePre)++;

    if (inicioIn == fimIn) return raiz;

    int posicao = encontrarPosicao(infixo, raiz->dado, inicioIn, fimIn);

    raiz->esq = construirArvore(prefixo, infixo, indicePre, inicioIn, posicao - 1);
    raiz->dir = construirArvore(prefixo, infixo, indicePre, posicao + 1, fimIn);

    return raiz;
}

void imprimirPosfixo(No *raiz){
    if (raiz == NULL) return;
    imprimirPosfixo(raiz->esq);
    imprimirPosfixo(raiz->dir);
    printf("%c", raiz->dado);
}

void liberarArvore(No *raiz){
    if (raiz == NULL) return;
    liberarArvore(raiz->esq);
    liberarArvore(raiz->dir);
    free(raiz);
}

int main(){
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++){
        char prefixo[52], infixo[52];
        scanf("%s %s", prefixo, infixo);

        int tamanho = strlen(prefixo);
        int indicePre = 0;

        No *raiz = construirArvore(prefixo, infixo, &indicePre, 0, tamanho - 1);

        imprimirPosfixo(raiz);
        printf("\n");

        liberarArvore(raiz);
    }

    return 0;
}
