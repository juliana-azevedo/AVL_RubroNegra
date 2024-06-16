#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "arvores_avl_rubroNegra.h"

// ------------------ Definição das estruturas ------------------
struct no_avl
{
    int chave;
    int fb;
    struct no_avl *Fesq;
    struct no_avl *Fdir;
    struct no_avl *pai;
};

struct avl
{
    no_avl *sentinela;
    int numElementos;
};

struct no_rb
{
    int chave;
    char cor;
    struct no_rb *pai;
    struct no_rb *esq;
    struct no_rb *dir;
};

struct rb
{
    no_rb *raiz;
    int numElementos;
};

// ------------- Struct resultado das Analises -------------

Analises *alocaStruct()
{
    Analises *resultado = (Analises *)malloc(sizeof(Analises));
    if (resultado == NULL)
    {
        printf("Erro ao alocar memória\n");
        return NULL;
    }

    resultado->tempo_execucao_insercao_avl = 0.0; 
    resultado->tempo_execucao_insercao_rb = 0.0;
    resultado->tempo_execucao_remocao_avl = 0.0;
    resultado->tempo_execucao_remocao_rb = 0.0;
    resultado->tempo_busca_avl = 0.0;
    resultado->tempo_busca_rb = 0.0;
    resultado->rotacoes_insercao_avl = 0; 
    resultado->rotacoes_insercao_rb = 0;
    resultado->rotacoes_remocao_avl = 0;
    resultado->rotacoes_remocao_rb = 0;

    return resultado;
}

// ------------------ Função de impressão  ------------------
void imprimeResultado(Analises resultado)
{
    printf("Tempo de execucao na insercao da AVL: %f segundos\n", resultado.tempo_execucao_insercao_avl);
    printf("Tempo de execucao na insercao da RB: %f segundos\n", resultado.tempo_execucao_insercao_rb);
    printf("Tempo de execucao na remocao da AVL: %f segundos\n", resultado.tempo_execucao_remocao_avl);
    printf("Tempo de execucao na remocao da RB: %f segundos\n", resultado.tempo_execucao_remocao_rb);
    printf("Tempo de busca AVL: %f segundos\n", resultado.tempo_busca_avl);
    printf("Tempo de busca RB: %f segundos\n", resultado.tempo_busca_rb);
    printf("Rotacoes na insercao da AVL: %d\n", resultado.rotacoes_insercao_avl);
    printf("Rotacoes na insercao da RB: %d\n", resultado.rotacoes_insercao_rb);
    printf("Rotacoes na remocao da AVL: %d\n", resultado.rotacoes_remocao_avl);
    printf("Rotacoes na remocao da RB: %d\n", resultado.rotacoes_remocao_rb);
}

// ------------- Gerador de Vetor ordenado -------------
int *geraVetorOrdenado(int quantidade)
{
    int *vetor = (int *)malloc(quantidade * sizeof(int));
    if (vetor == NULL)
    {
        printf("Erro ao alocar memória.\n");
        exit(1);
    }
    for (int i = 0; i < quantidade; i++)
    {
        vetor[i] = i;
    }
    return vetor;
}

// ------------- Gerador de Vetor aleatório -------------
int *geraVetorAleatorio(int quantidade, int num_iteracoes)
{
    int *vetor = (int *)malloc(num_iteracoes * sizeof(int));
    if (vetor == NULL) 
    {
        printf("Erro ao alocar memória\n");
        exit(1);
    }
    srand(time(NULL));

    for (int i = 0; i < num_iteracoes; ++i)
    {
        vetor[i] = rand() % quantidade; 
    }
    return vetor;
}

//--------------------------- Busca ---------------------------
no_avl *avl_buscaNo(no_avl *raiz, int chave)
{
    if (raiz == NULL || raiz->chave == chave)
        return raiz;
    if (chave < raiz->chave)
        return avl_buscaNo(raiz->Fesq, chave);
    else
        return avl_buscaNo(raiz->Fdir, chave);
}

no_avl *avl_busca(avl *arvore, int chave)
{
    return avl_buscaNo(arvore->sentinela, chave);
}

no_rb *rb_buscaNo(no_rb *raiz, int chave)
{
    if (raiz == NULL || raiz->chave == chave)
        return raiz;
    if (chave < raiz->chave)
        return rb_buscaNo(raiz->esq, chave);
    else
        return rb_buscaNo(raiz->dir, chave);
}

no_rb *rb_busca(rb *arvore, int chave)
{
    return rb_buscaNo(arvore->raiz, chave);
}

int buscarElementosAleatorios_AVL(avl *arv, int valor, Analises *resultado)
{
    avl_busca(arv, valor);
}

int buscarElementosAleatorios_RB(rb *arv, int valor, Analises *resultado)
{
    rb_busca(arv, valor);
}

// -------------------------- Implementações das funções para árvore AVL --------------------------

// -------------- Criar árvore AVL --------------
avl *avl_criaArvore()
{
    avl *arv = (avl *)malloc(sizeof(avl));
    if (arv != NULL)
    {
        arv->sentinela = (no_avl *)malloc(sizeof(no_avl));
        if (arv->sentinela != NULL)
        {
            arv->sentinela->chave = -1000;
            arv->sentinela->Fesq = NULL;
            arv->sentinela->Fdir = NULL;
            arv->sentinela->pai = NULL;
        }
        arv->numElementos = 0;
    }
    return arv;
}

// -------------- Inserir nó na árvore AVL --------------
int avl_insereNo(avl *arv, int valor, Analises *resultado)
{
    if (arv == NULL)
    {
        printf("Erro: Ponteiro para árvore AVL é nulo.\n");
        return 0;
    }

    no_avl *novoNo, *noPai, *noAtual;
    novoNo = (no_avl *)malloc(sizeof(no_avl));

    if (novoNo == NULL)
    {
        return 0;
    }

    novoNo->chave = valor;
    novoNo->Fdir = NULL;
    novoNo->Fesq = NULL;
    novoNo->pai = NULL;

    noAtual = arv->sentinela->Fdir;

    if (noAtual == NULL)
    {
        arv->sentinela->Fdir = novoNo;
        novoNo->pai = arv->sentinela;
        arv->numElementos++;
        return 1;
    }

    noPai = arv->sentinela;

    while (noAtual != NULL)
    {
        noPai = noAtual;

        if (valor < noAtual->chave)
        {
            noAtual = noAtual->Fesq;
        }
        else
        {
            noAtual = noAtual->Fdir;
        }
    }

    novoNo->pai = noPai;
    if (noPai == arv->sentinela)
    {
        arv->sentinela->Fdir = novoNo;
    }
    else if (valor < noPai->chave)
    {
        noPai->Fesq = novoNo;
    }
    else
    {
        noPai->Fdir = novoNo;
    }

    arv->numElementos++;
    atualizaFB_insercao(arv, novoNo, resultado);

    return 1;
}

// -------------- Remover nó na árvore AVL --------------
int avl_removeNo(avl *arv, int valor, Analises *resultado)
{
    no_avl *noRemover = arv->sentinela->Fdir;
    no_avl *pai = NULL;
    no_avl *filho = NULL;

    while (noRemover != NULL && noRemover->chave != valor)
    {
        pai = noRemover;
        if (valor < noRemover->chave)
        {
            noRemover = noRemover->Fesq;
        }
        else
        {
            noRemover = noRemover->Fdir;
        }
    }

    if (noRemover == NULL)
    {
        return 0;
    }

    if (noRemover->Fesq == NULL && noRemover->Fdir == NULL)
    {
        filho = NULL;
        pai = noRemover->pai;
    }
    else if (noRemover->Fesq != NULL && noRemover->Fdir == NULL)
    {
        filho = noRemover->Fesq;
        pai = noRemover->pai;
    }
    else if (noRemover->Fesq == NULL && noRemover->Fdir != NULL)
    {
        filho = noRemover->Fdir;
        pai = noRemover->pai;
    }
    else
    {

        no_avl *sucessor = noRemover->Fdir;
        pai = noRemover;
        while (sucessor->Fesq != NULL)
        {
            pai = sucessor;
            sucessor = sucessor->Fesq;
        }
        noRemover->chave = sucessor->chave;
        noRemover = sucessor;
        filho = noRemover->Fdir;
        valor = sucessor->chave;
    }

    if (noRemover == arv->sentinela->Fdir)
    {
        arv->sentinela->Fdir = filho;
    }
    else if (noRemover == pai->Fesq)
    {
        pai->Fesq = filho;
    }
    else
    {
        pai->Fdir = filho;
    }

    if (filho != NULL)
    {
        filho->pai = pai;
    }

    atualizaFB_remocao(arv, pai, valor, resultado);
    arv->numElementos--;
    free(noRemover);
    return 1;
}

// -------------- Atualiza Fator de Balanceamento na Inserção ---------------
void atualizaFB_insercao(avl *arv, no_avl *novoNo, Analises *resultado)
{
    no_avl *aux;
    aux = novoNo;

    do
    {
        if (aux->chave < aux->pai->chave)
        {
            aux->pai->fb--;
        }
        else
        {
            aux->pai->fb++;
        }
        aux = aux->pai;
    } while (aux->pai != arv->sentinela && aux->fb != 0 && aux->fb != 2 && aux->fb != -2);

    if (aux->fb != -2 || aux->fb != 2)
    {
        balanceamento(arv, aux, resultado, 'I');
    }
}

// -------------- Balanceamento na AVL ---------------
void balanceamento(avl *arv, no_avl *noDesbal, Analises *resultado, char operacao)
{
    arv = arv; // Evita warning de variável não utilizada
    no_avl *filho;

    if (noDesbal->fb == 2)
    {
        filho = noDesbal->Fdir;
        if (filho->fb == -1)
        {
            int fbNeto = filho->Fesq->fb;
            rotacaoDir(filho, resultado, operacao);
            rotacaoEsq(noDesbal, resultado, operacao);
            if (fbNeto == 0)
            { // Ajusta FB
                noDesbal->fb = 0;
                filho->fb = 0;
                fbNeto = 0;
            }
            else if (fbNeto == -1)
            {
                noDesbal->fb = 0;
                filho->fb = 1;
                fbNeto = 0;
            }
            else if (fbNeto == 1)
            {
                noDesbal->fb = -1;
                filho->fb = 0;
                fbNeto = 0;
            }
        }
        else
        {
            int fbFilho = filho->fb;
            rotacaoEsq(noDesbal, resultado, operacao);
            if (fbFilho == 0)
            {
                noDesbal->fb = 1;
                filho->fb = -1;
            }
        }
    }
    else
    {
        if (noDesbal->fb == -2)
        {
            filho = noDesbal->Fesq;
            if (filho->fb == 1)
            {
                int fbNeto = filho->Fdir->fb; // guarda o fb do neto
                rotacaoEsq(filho, resultado, operacao);
                rotacaoDir(noDesbal, resultado, operacao);
                if (fbNeto == 0)
                { // Ajusta FB
                    noDesbal->fb = 0;
                    filho->fb = 0;
                    fbNeto = 0;
                }
                else if (fbNeto == -1)
                {
                    noDesbal->fb = 1;
                    filho->fb = 0;
                    fbNeto = 0;
                }
                else if (fbNeto == 1)
                {
                    noDesbal->fb = 0;
                    filho->fb = -1;
                    fbNeto = 0;
                }
            }
            else
            {
                int fbFilho = filho->fb;
                rotacaoDir(noDesbal, resultado, operacao);
                if (fbFilho == 0)
                {
                    noDesbal->fb = -1;
                    filho->fb = 1;
                }
            }
        }
    }
}

// -------------- Rotação à Direita na AVL ---------------
void rotacaoDir(no_avl *noDesbal, Analises *resultado, char operacao)
{
    no_avl *aux = noDesbal->Fesq;
    noDesbal->Fesq = aux->Fdir;
    if (aux->Fdir != NULL)
        aux->Fdir->pai = noDesbal;
    aux->pai = noDesbal->pai;
    if (noDesbal->pai->Fesq == noDesbal)
        noDesbal->pai->Fesq = aux;
    else
        noDesbal->pai->Fdir = aux;
    aux->Fdir = noDesbal;
    noDesbal->pai = aux;
    noDesbal->fb = 0;
    aux->fb = 0;

    if (operacao == 'I')
    {
        resultado->rotacoes_insercao_avl++; // Incrementa o contador de rotações para inserção
    }
    else
    {
        resultado->rotacoes_remocao_avl++; // Incrementa o contador de rotações para remoção
    }
}

// -------------- Rotação à Esquerda na AVL ---------------
void rotacaoEsq(no_avl *noDesbal, Analises *resultado, char operacao)
{
    no_avl *aux = noDesbal->Fdir;
    noDesbal->Fdir = aux->Fesq;
    if (aux->Fesq != NULL)
        aux->Fesq->pai = noDesbal;
    aux->pai = noDesbal->pai;
    if (noDesbal->pai->Fesq == noDesbal)
        noDesbal->pai->Fesq = aux;
    else
        noDesbal->pai->Fdir = aux;
    aux->Fesq = noDesbal;
    noDesbal->pai = aux;
    noDesbal->fb = 0;
    aux->fb = 0;

    if (operacao == 'I')
    {
        resultado->rotacoes_insercao_avl++;
    }
    else
    {
        resultado->rotacoes_remocao_avl++;
    }
}

// -------------- Atualiza Fator de Balanceamento na Remoção da AVL ---------------
void atualizaFB_remocao(avl *arv, no_avl *pai, int chaveRemovida, Analises *resultado)
{
    if (pai == arv->sentinela)
        return;

    no_avl *aux = pai;

    if (chaveRemovida >= aux->chave)
        aux->fb--;
    else
        aux->fb++;

    while (aux != arv->sentinela->Fdir && aux->fb == 0)
    {
        if (aux->chave >= aux->pai->chave)
        {
            aux->pai->fb--;
        }
        else
        {
            aux->pai->fb++;
        }

        aux = aux->pai;
    }

    if (aux->fb == 2 || aux->fb == -2)
    {
        balanceamento(arv, aux, resultado, 'R');
        if (aux->pai->fb == 0 && aux->pai->pai != arv->sentinela)
        {
            atualizaFB_remocao(arv, aux->pai->pai, aux->pai->chave, resultado);
        }
    }
}

// -------------------------- Implementações das funções para árvore Rubro-Negra --------------------------

// -------------- Criar árvore Rubro-Negra --------------
rb *rubroNegra_criaArvore()
{
    rb *arv = (rb *)malloc(sizeof(rb));
    if (arv != NULL)
    {
        arv->raiz = NULL;
        arv->numElementos = 0;
    }
    return arv;
}

// -------------- Inserir nó na árvore Rubro-Negra --------------
int rubroNegra_insereNo(rb *arv, int valor, Analises *resultado)
{

    if (arv == NULL)
        return 0;

    no_rb *novoNo = (no_rb *)malloc(sizeof(no_rb));
    if (novoNo == NULL)
        return 0;

    novoNo->chave = valor;
    novoNo->cor = 'V';
    novoNo->esq = NULL;
    novoNo->dir = NULL;
    novoNo->pai = NULL;

    if (arv->raiz == NULL)
    {
        novoNo->cor = 'P';
        arv->raiz = novoNo;
        arv->numElementos++;
        return 1;
    }

    no_rb *atual = arv->raiz;
    no_rb *ant = NULL;

    while (atual != NULL)
    {
        ant = atual;

        if (valor == atual->chave)
        {
            free(novoNo);
            return 0;
        }
        else if (valor < atual->chave)
        {
            atual = atual->esq;
        }
        else
        {
            atual = atual->dir;
        }
    }

    novoNo->pai = ant;
    if (valor < ant->chave)
    {
        ant->esq = novoNo;
    }
    else
    {
        ant->dir = novoNo;
    }

    arv->numElementos++;
    balanceamentoInsercao(arv, novoNo, resultado, 1);
    return 1;
}

// -------------- Balanceamento na Inserção da Rubro-Negra --------------
void balanceamentoInsercao(rb *arv, no_rb *noDesbal, Analises *resultado, int operacao)
{
    while (noDesbal->pai != NULL && noDesbal->pai->cor == 'V')
    {
        if (noDesbal->pai == noDesbal->pai->pai->esq)
        {
            no_rb *tio = noDesbal->pai->pai->dir;

            if (tio != NULL && tio->cor == 'V')
            {
                noDesbal->pai->cor = 'P';
                tio->cor = 'P';
                noDesbal->pai->pai->cor = 'V';
                noDesbal = noDesbal->pai->pai;
            }
            else
            {
                if (noDesbal == noDesbal->pai->dir)
                {
                    noDesbal = noDesbal->pai;
                    rotacaoEsqRB(arv, noDesbal, resultado, operacao);
                }

                noDesbal->pai->cor = 'P';
                noDesbal->pai->pai->cor = 'V';
                rotacaoDirRB(arv, noDesbal->pai->pai, resultado, operacao);
            }
        }
        else
        {
            no_rb *tio = noDesbal->pai->pai->esq;

            if (tio != NULL && tio->cor == 'V')
            {
                noDesbal->pai->cor = 'P';
                tio->cor = 'P';
                noDesbal->pai->pai->cor = 'V';
                noDesbal = noDesbal->pai->pai;
            }
            else
            {
                if (noDesbal == noDesbal->pai->esq)
                {
                    noDesbal = noDesbal->pai;
                    rotacaoDirRB(arv, noDesbal, resultado, operacao);
                }

                noDesbal->pai->cor = 'P';
                noDesbal->pai->pai->cor = 'V';
                rotacaoEsqRB(arv, noDesbal->pai->pai, resultado, operacao);
            }
        }
    }

    arv->raiz->cor = 'P';
}

// -------------- Rotação à Direita na Rubro-Negra --------------
void rotacaoDirRB(rb *arv, no_rb *noDesbal, Analises *resultado, int operacao)
{

    if (operacao == 1)
    {
        resultado->rotacoes_insercao_rb++; // Incrementa o contador de rotações para inserção
    }
    else
    {
        resultado->rotacoes_remocao_rb++; // Incrementa o contador de rotações para remoção
    }

    no_rb *filhoEsq = noDesbal->esq;
    noDesbal->esq = filhoEsq->dir;

    if (filhoEsq->dir != NULL)
    {
        filhoEsq->dir->pai = noDesbal;
    }

    filhoEsq->pai = noDesbal->pai;

    if (noDesbal->pai == NULL)
    {
        arv->raiz = filhoEsq;
    }
    else if (noDesbal == noDesbal->pai->esq)
    {
        noDesbal->pai->esq = filhoEsq;
    }
    else
    {
        noDesbal->pai->dir = filhoEsq;
    }

    filhoEsq->dir = noDesbal;
    noDesbal->pai = filhoEsq;
}

// -------------- Rotação à Esquerda na Rubro-Negra --------------
void rotacaoEsqRB(rb *arv, no_rb *noDesbal, Analises *resultado, int operacao)
{
    if (operacao == 1)
    {
        resultado->rotacoes_insercao_rb++; // Incrementa o contador de rotações para inserção
    }
    else
    {
        resultado->rotacoes_remocao_rb++; // Incrementa o contador de rotações para remoção
    }

    no_rb *filhoDir = noDesbal->dir;
    noDesbal->dir = filhoDir->esq;

    if (filhoDir->esq != NULL)
    {
        filhoDir->esq->pai = noDesbal;
    }

    filhoDir->pai = noDesbal->pai;

    if (noDesbal->pai == NULL)
    {
        arv->raiz = filhoDir;
    }
    else if (noDesbal == noDesbal->pai->esq)
    {
        noDesbal->pai->esq = filhoDir;
    }
    else
    {
        noDesbal->pai->dir = filhoDir;
    }

    filhoDir->esq = noDesbal;
    noDesbal->pai = filhoDir;
}

// -------------- Remover nó na árvore Rubro-Negra --------------
int rubroNegra_removeNo(rb *arv, int valor, Analises *resultado)
{

    char c;
    if (arv == NULL || arv->raiz == NULL)
        return 0;

    no_rb *noRemover = arv->raiz;
    while (noRemover != NULL && noRemover->chave != valor)
    {
        if (valor < noRemover->chave)
            noRemover = noRemover->esq;
        else
            noRemover = noRemover->dir;
    }

    if (noRemover == NULL)
    {
        return -1; // Valor não encontrado
    }

    if (noRemover->esq != NULL && noRemover->dir != NULL)
    {
        no_rb *sucessor = noRemover->dir;
        while (sucessor->esq != NULL)
            sucessor = sucessor->esq;

        noRemover->chave = sucessor->chave;
        noRemover = sucessor;
    }

    no_rb *filho = (noRemover->esq != NULL) ? noRemover->esq : noRemover->dir;

    if (noRemover->cor == 'P')
    {
        if (filho == NULL || filho->cor == 'P')
        {
            balanceamentoRemocao(arv, noRemover, noRemover->pai, valor, resultado);
        }
        else
        {
            filho->cor = 'P';
        }
    }

    if (noRemover->pai == NULL)
    {
        arv->raiz = filho;
        if (filho != NULL)
        {
            filho->pai = NULL;
        }
    }
    else
    {
        if (noRemover == noRemover->pai->esq)
            noRemover->pai->esq = filho;
        else
            noRemover->pai->dir = filho;

        if (filho != NULL)
            filho->pai = noRemover->pai;
    }

    free(noRemover);
    arv->numElementos--;
    return 1;
}

// -------------- Balanceamento na Remoção da Rubro-Negra --------------
void balanceamentoRemocao(rb *arv, no_rb *noDesbal, no_rb *pai, int valor, Analises *resultado)
{
    int operacao = 2;

    while (noDesbal != arv->raiz && (noDesbal == NULL || noDesbal->cor == 'P'))
    {
        if (noDesbal == pai->esq)
        {
            no_rb *irmao = pai->dir;

            if (irmao->cor == 'V')
            {
                irmao->cor = 'P';
                pai->cor = 'V';
                rotacaoEsqRB(arv, pai, resultado, operacao);
                irmao = pai->dir;
            }

            if ((irmao->esq == NULL || irmao->esq->cor == 'P') && (irmao->dir == NULL || irmao->dir->cor == 'P'))
            {
                irmao->cor = 'V';
                noDesbal = pai;
                pai = noDesbal->pai;
            }
            else
            {
                if (irmao->dir == NULL || irmao->dir->cor == 'P')
                {
                    irmao->esq->cor = 'P';
                    irmao->cor = 'V';
                    rotacaoDirRB(arv, irmao, resultado, operacao);
                    irmao = pai->dir;
                }

                irmao->cor = pai->cor;
                pai->cor = 'P';
                if (irmao->dir != NULL)
                {
                    irmao->dir->cor = 'P';
                }
                rotacaoEsqRB(arv, pai, resultado, operacao);
                noDesbal = arv->raiz;
            }
        }
        else
        {
            no_rb *irmao = pai->esq;

            if (irmao->cor == 'V')
            {
                irmao->cor = 'P';
                pai->cor = 'V';
                rotacaoDirRB(arv, pai, resultado, operacao);
                irmao = pai->esq;
            }

            if ((irmao->dir == NULL || irmao->dir->cor == 'P') && (irmao->esq == NULL || irmao->esq->cor == 'P'))
            {
                irmao->cor = 'V';
                noDesbal = pai;
                pai = noDesbal->pai;
            }
            else
            {
                if (irmao->esq == NULL || irmao->esq->cor == 'P')
                {
                    irmao->dir->cor = 'P';
                    irmao->cor = 'V';
                    rotacaoEsqRB(arv, irmao, resultado, operacao);
                    irmao = pai->esq;
                }

                irmao->cor = pai->cor;
                pai->cor = 'P';
                if (irmao->esq != NULL)
                {
                    irmao->esq->cor = 'P';
                }
                rotacaoDirRB(arv, pai, resultado, operacao);
                noDesbal = arv->raiz;
            }
        }
    }

    if (noDesbal != NULL)
    {
        noDesbal->cor = 'P';
    }
}

// -------------------------- Liberar memória das árvores AVL e Rubro-Negra --------------------------
void avl_liberaNo(no_avl *no)
{
    if (no != NULL)
    {
        avl_liberaNo(no->Fesq);
        avl_liberaNo(no->Fdir);
        free(no);
    }
}

void avl_liberaArvore(avl *arvore)
{
    if (arvore != NULL)
    {
        avl_liberaNo(arvore->sentinela->Fdir);
        free(arvore->sentinela);
        free(arvore);
    }
}

void rb_liberaNo(no_rb *no)
{
    if (no != NULL)
    {
        rb_liberaNo(no->esq);
        rb_liberaNo(no->dir);
        free(no);
    }
}

void rb_liberaArvore(rb *arvore)
{
    if (arvore != NULL)
    {
        rb_liberaNo(arvore->raiz);
        free(arvore);
    }
}

