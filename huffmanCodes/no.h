//Vinicius Araujo 2210392
//Felipe Cancella 2210487

//Struct no
//estrutura utilizada para fila e arvore no algoritmo de huffman
typedef struct no No;

struct no
{
    char carac;
    int qnt;
    No* dir;
    No* esq;
    No* prox;
};

typedef struct cod Cod;

//estrutura para armazenar o codigo e o respectivo codigo
struct cod
{
    char carac;
    char* codigo;
};

//Funcao insere
//Insere novo no na lista de acordo com sua frequencia
//recebe a cabeca da lista encadeda, o caractere em questao, e sua ocorrencia
No* insere(No* lista, char letra, int quantidade);

//Funcao lista_cria
//Cria uma lista encadeada vazia
No* lista_cria(void);

//Recebe uma lista e "tranforma" ela em uma arvore juntando os 2 primeiros elementos
No* arvoriza(No* lista);

//imprime a arvore em pre ordem
//recebe a raiz da arvore
void imprimeArv(No* arv);

//conta o numero de caracteres (folhas)
//recebe a raiz da arvore
int contarFolhas(No* raiz);

//declara os codigos e seus respectivos caracteres em um vetor de Cod
//recebe a raiz da arvore, uma string que vai guardar cada caminho durante a recursao, um int que guarda o nivel da arvore durante cada recursao, o vetor de Cod's que guarda cada letra e seu codigo/caminho, e um contador que é guardado durante as recursoes
void assignHuffmanCodes(No* arv, char* caminho, int nivel, Cod* huffmanCodes, int* cont);