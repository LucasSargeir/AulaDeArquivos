#ifndef __ARVORE_B__
#define __ARVORE_B__

#define TAM_CHAVE 15   // tamanho de cada chave
#define TAM_PAG 2048  // a arvore possuirá 300 chaves

#include <stdio.h>

typedef struct _ArvoreB ArvoreB;
typedef struct _ArvoreB_Cabecalho ArvoreB_Cabecalho;
typedef struct _ArvoreB_Elemento ArvoreB_Elemento;
typedef struct _ArvoreB_Pagina ArvoreB_Pagina;

struct _ArvoreB_Cabecalho
{
    long raiz;  // a raiz fica numa estrutura de cabecalho
};

struct _ArvoreB
{
    ArvoreB_Cabecalho* cabecalho;
    FILE* f;    
};

struct _ArvoreB_Elemento
{
    char chave[TAM_CHAVE];  // guardar as chaves 
    long posicaoRegistro;   // posicao das chaves no arquivo de dados
    long paginaDireita;
};

struct _ArvoreB_Pagina
{
    int quantidadeElementos;    // quantidade de elementos EFETIVAMENTE armazenados
    long paginaEsquerda;  // sempre trabalhamos com a chave e seu ponteiro esquerdo (estrutura da página)
    ArvoreB_Elemento elementos[TAM_PAG]; // cada elemento da página tem chave, sua posicao e a pagina Direita
};

#endif
