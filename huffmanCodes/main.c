// Vinicius Araujo 2210392
// Felipe Cancella 2210487

#include "no.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int* ocorrencias(FILE* arq);

void comprimidoBin(char* text, Cod* huffmanCodes, int numCodes);

void binComprimidoBin(char* text, Cod* huffmanCodes, int numCodes);

void textoBin(char* text, char* filename);

int main(void) {

    No* lista;
    lista = lista_cria();

    FILE* arq = fopen("arq.txt", "r");
    if (arq == NULL) {
        printf("erro ao abrir o arquivo");
        exit(1);
    }
    int* vetor = (int*)malloc(sizeof(int) * 256);

    vetor = ocorrencias(arq);

    // Imprime a ocorrencia de cada letra
    /*printf("Caractere \t Ocorrências\n");
    for (int i = 0; i < 256; i++) {
        if (vetor[i] > 0) {
          printf("%c    \t %d\n", i, vetor[i]);
        }
    }*/

    for (int i = 0; i < 256; i++) {
        if (vetor[i] > 0) {
            lista = insere(lista, i, vetor[i]);
        }
    }

    printf("\nVETOR -");
    for (No* p = lista; p != NULL; p = p->prox) {
        printf("\n %c - %d", p->carac, p->qnt);
    }

    lista = arvoriza(lista);

    printf("\n\nVETOR ARVORIZADO -\n");
    imprimeArv(lista);

    int numCaracs = contarFolhas(lista);

    Cod* huffmanCodes = (Cod*)malloc(sizeof(Cod) * numCaracs);

    int cont = 0;
    char caminho[256];
    assignHuffmanCodes(lista, caminho, 0, huffmanCodes, &cont);

    printf("\nVetor codigos\n");
    for (int i = 0; i < numCaracs; i++) {
        printf("%c -- %s\n", huffmanCodes[i].carac, huffmanCodes[i].codigo);
    }

    rewind(arq);
    fseek(arq, 0, SEEK_END);
    long tamanhoArq = ftell(arq);
    rewind(arq);

    char caractere;
    char* text = (char*)malloc((tamanhoArq + 1) * sizeof(char));
    int i = 0;
    while ((caractere = fgetc(arq)) != EOF && i < tamanhoArq) {
        text[i] = caractere;
        i++;
    }
    text[tamanhoArq] = '\0'; // Adiciona o caractere nulo ao final do vetor (text)
    // Fecha o arquivo
    fclose(arq);

    comprimidoBin(text, huffmanCodes, cont);
    binComprimidoBin(text, huffmanCodes, cont);
    textoBin(text, "naocomprimido.txt");

    free(text);
    free(huffmanCodes);
    return 0;
}

int* ocorrencias(FILE* arq) {
    int* vetor = (int*)calloc(256, sizeof(int));

    char ch;

    while ((ch = fgetc(arq)) != EOF) {
        vetor[ch]++;
    }

    return vetor;
}

void comprimidoBin(char* text, Cod* huffmanCodes, int numCodes) {
    FILE* file = fopen("comprimido.txt", "w");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    for (int i = 0; text[i] != '\0'; i++) {
        char caracAtual = text[i];
        for (int j = 0; j < numCodes; j++) {
            if (huffmanCodes[j].carac == caracAtual) {
                fputs(huffmanCodes[j].codigo, file);
                break;
            }
        }
    }
    fclose(file);

    printf("Texto comprimido e salvo em 'comprimido.txt'.\n");
}

void binComprimidoBin(char* text, Cod* huffmanCodes, int numCodes) {
    
    FILE* file = fopen("comprimido.bin", "wb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    for (int i = 0; text[i] != '\0'; i++) {
        char caracAtual = text[i];
        for (int j = 0; j < numCodes; j++) {
            if (huffmanCodes[j].carac == caracAtual) {
                fwrite(huffmanCodes[j].codigo, sizeof(char), strlen(huffmanCodes[j].codigo), file);
                break;
            }
        }
    }

    fclose(file);

    printf("Texto comprimido salvo em 'comprimido.bin'.\n");
}

void textoBin(char* text, char* nomearq) {
    FILE* file = fopen(nomearq, "w");
    if (file == NULL) {
        printf("Erro ao abrir arquivo.\n");
        return;
    }

    for (int i = 0; text[i] != '\0'; i++) {
        char caracAtual = text[i];

        for (int j = 7; j >= 0; j--) {

            int bit = (caracAtual >> j) & 1;

            fprintf(file, "%d", bit);
        }
    }

    fclose(file);

    printf("Texto escrito em binario e salvo em 'naocomprimido.txt'.\n");
}