//
//

#ifndef INC_7_AVL_AVL_H
#define INC_7_AVL_AVL_H

// Declaração das estruturas
typedef struct no_avl no_avl;
typedef struct avl avl;
typedef struct no_rb no_rb;
typedef struct rb rb;

typedef struct Analises
{
    double tempo_execucao_insercao_avl;
    double tempo_execucao_remocao_avl;
    int rotacoes_insercao_avl;
    int rotacoes_remocao_avl;
    double tempo_execucao_insercao_rb;
    double tempo_execucao_remocao_rb;
    double tempo_busca_avl;
    double tempo_busca_rb;
    int rotacoes_insercao_rb;
    int rotacoes_remocao_rb;
} Analises;

Analises *alocaStruct();

// -------------------------- Implementações das funções para árvore AVL --------------------------
avl *avl_criaArvore();
int avl_insereNo(avl *arv, int valor, Analises *resultado);
int avl_removeNo(avl *arv, int valor, Analises *resultado);
void atualizaFB_insercao(avl *arv, no_avl *novoNo, Analises *resultado);
void balanceamento(avl *arv, no_avl *noDesbal, Analises *resultado, char operacao);
void rotacaoDir(no_avl *noDesbal, Analises *resultado, char operacao);
void rotacaoEsq(no_avl *noDesbal, Analises *resultado, char operacao);
void atualizaFB_remocao(avl *arv, no_avl *pai, int chaveRemovida, Analises *resultado);

// -------------------------- Implementações das funções para árvore Rubro-Negra --------------------------

rb *rubroNegra_criaArvore();
int rubroNegra_insereNo(rb *arv, int valor, Analises *resultado);
void balanceamentoInsercao(rb *arv, no_rb *noDesbal, Analises *resultado, int operacao);
void rotacaoDirRB(rb *arv, no_rb *noDesbal, Analises *resultado, int operacao);
void rotacaoEsqRB(rb *arv, no_rb *noDesbal, Analises *resultado, int operacao);
int rubroNegra_removeNo(rb *arv, int valor, Analises *resultado);
void balanceamentoRemocao(rb *arv, no_rb *noDesbal, no_rb *pai, int valor, Analises *resultado);

// --------------------------------- Funções de impressão e manipulação ---------------------------------
int *geraVetorOrdenado(int quantidade);
int *geraVetorAleatorio(int quantidade, int num_iteracoes);
void imprimeResultado(Analises resultado);

// -------------------------- Funções de busca em árvores AVL e Rubro-Negra --------------------------
no_avl *avl_buscaNo(no_avl *raiz, int chave);
no_avl *avl_busca(avl *arvore, int chave);
no_rb *rb_buscaNo(no_rb *raiz, int chave);
no_rb *rb_busca(rb *arvore, int chave);
int buscarElementosAleatorios_AVL(avl *arv, int valor, Analises *resultado);
int buscarElementosAleatorios_RB(rb *arv, int valor, Analises *resultado);

// -------------------------- Liberar memória das árvores AVL e Rubro-Negra --------------------------
void avl_liberaNo(no_avl *no);
void rb_liberaNo(no_rb *no);
void avl_liberaArvore(avl *arvore);
void rb_liberaArvore(rb *arvore);

#endif // INC_7_AVL_AVL_H
