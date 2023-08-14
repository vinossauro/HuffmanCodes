//Vinicius Araujo 2210392
//Felipe Cancella 2210487

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "no.h"

// insere o nó na lista de acordo com sua ocorrencia
No* insere(No* lista, char letra, int quantidade)
{
    No* novo = (No*)malloc(sizeof(No));
    novo->carac = letra;
    novo->qnt = quantidade;
    novo->prox = NULL;
    novo->esq = NULL;
    novo->dir = NULL;

    No* p = lista;
    No* ant = NULL;

    // percorre a lista até encontrar onde inserir o novo nó
    while (p != NULL && quantidade >= p->qnt) {
        ant = p;
        p = p->prox;
    }

    novo->prox = p;

    // caso especial: insere no inicio da lista
    if (ant == NULL) {
        return novo;
    }

    // insere no meio ou no final da lista
    ant->prox = novo;

    return lista;

}

// cria uma nova lista vazia
No* lista_cria(void)
{
    return NULL;
}


// Transforma a lista encadeada em uma arvore binaria (heap)
No* arvoriza(struct no* lista) {
    while (lista->prox != NULL) {
        // Criação do novo nó
        No* novo = (struct no*)malloc(sizeof(struct no));
        novo->carac = '+';
        novo->qnt = lista->qnt + lista->prox->qnt;
        novo->prox = NULL;
        novo->esq = lista;
        novo->dir = lista->prox;

        // Remoção dos dois primeiros nós da lista
        No* temp = lista->prox;
        lista = temp->prox;

        // Inserção do novo nó na lista (soma dos dois primeiros)
        if (lista == NULL || novo->qnt <= lista->qnt) {
            novo->prox = lista;
            lista = novo;
        }
        else {
            struct no* atual = lista;
            while (atual->prox != NULL && novo->qnt > atual->prox->qnt) {
                atual = atual->prox;
            }
            novo->prox = atual->prox;
            atual->prox = novo;
        }
    }

    return lista;
}

// Imprime a arvore binaria (pré-ordem)
void imprimeArv(No* arv) {
    if (arv != NULL) {
        printf("%-5c %d\n", arv->carac, arv->qnt);
        imprimeArv(arv->esq);
        imprimeArv(arv->dir);
    }
}

// Função para contar o número de folhas/caracteres diferentes
int contarFolhas(No* raiz)
{
    if (raiz == NULL) {
        return 0;
    }
    if (raiz->esq == NULL && raiz->dir == NULL) {
        return 1;
    }
    int folhasEsq = contarFolhas(raiz->esq);
    int folhasDir = contarFolhas(raiz->dir);
    return folhasEsq + folhasDir;
}

// Calcula o caminho para cada caractere diferente e guarda em um vetor de Cod's
void assignHuffmanCodes(No* arv, char* caminho, int nivel, Cod* huffmanCodes, int* cont)
{
    //sempre que chegar em uma folha (letra), bota essa letra no vetor huffmanCodes
    if (arv->esq == NULL && arv->dir == NULL) {
        caminho[nivel] = '\0';
        huffmanCodes[*cont].carac = arv->carac;   //Bota no indice (cont) a nossa letra
        huffmanCodes[*cont].codigo = strdup(caminho); //Bota no indice a string que guarda o caminho/codigo
        (*cont)++;
    }
    else {
        if (arv->esq != NULL) {
            caminho[nivel] = '0';
            assignHuffmanCodes(arv->esq, caminho, nivel + 1, huffmanCodes, cont);
        }

        if (arv->dir != NULL) {
            caminho[nivel] = '1';
            assignHuffmanCodes(arv->dir, caminho, nivel + 1, huffmanCodes, cont);
        }
    }
}
