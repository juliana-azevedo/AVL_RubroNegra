#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "arvores_avl_rubroNegra.h"

int main()
{
    int quantidade = 10000;
    int num_iteracoes = 1000;
    int *vetor = geraVetorOrdenado(quantidade);
    int *vetor_aleatorio = geraVetorAleatorio(quantidade, num_iteracoes);

    avl *arvore_avl = avl_criaArvore();
    rb *arvore_rb = rubroNegra_criaArvore();
    Analises *resultado = alocaStruct();

    // --------------- Inserção em AVL ---------------
    clock_t inicio_avl_ins = clock();
    for (int i = 0; i < quantidade; i++)
    {
        avl_insereNo(arvore_avl, vetor[i], resultado);
    }
    clock_t fim_avl_ins = clock();

    // --------------- Inserção em Rubro-Negra ---------------
    clock_t inicio_rb_ins = clock();
    for (int i = 0; i < quantidade; i++)
    {
        rubroNegra_insereNo(arvore_rb, vetor[i], resultado);
    }
    clock_t fim_rb_ins = clock();

    // --------------------Cálculo dos tempos de execução--------------------

    resultado->tempo_execucao_insercao_avl = (double)(fim_avl_ins - inicio_avl_ins) / CLOCKS_PER_SEC;
    resultado->tempo_execucao_insercao_rb = (double)(fim_rb_ins - inicio_rb_ins) / CLOCKS_PER_SEC;

    // -------------------------- Busca de elementos aleatórios AVL --------------------------

    clock_t inicioAleatorio_avl_ins = clock();
    for (int i = 0; i < num_iteracoes; i++)
    {
        buscarElementosAleatorios_AVL(arvore_avl, vetor[i], resultado);
    }
    clock_t fimAleatorio_avl_ins = clock();

    // -------------------------- Busca de elementos aleatórios Rubro-Negra --------------------------
    clock_t inicioAleatorio_rb_ins = clock();
    for (int i = 0; i < num_iteracoes; i++)
    {
        buscarElementosAleatorios_RB(arvore_rb, vetor[i], resultado);
    }
    clock_t fimAleatorio_rb_ins = clock();

    // --------------------Cálculo dos tempos de execução--------------------
    resultado->tempo_busca_avl = (double)(fimAleatorio_avl_ins - inicioAleatorio_avl_ins) / CLOCKS_PER_SEC;
    resultado->tempo_busca_rb = (double)(fimAleatorio_rb_ins - inicioAleatorio_rb_ins) / CLOCKS_PER_SEC;

    // -------------------------- Remoção em AVL e Rubro-Negra --------------------------

    // --------------- Remoção em AVL ---------------
    clock_t inicio_avl_rem = clock();
    for (int i = 0; i < quantidade; i++)
    {
        avl_removeNo(arvore_avl, vetor[i], resultado);
    }
    clock_t fim_avl_rem = clock();

    // --------------- Remoção em Rubro-Negra ---------------

    clock_t inicio_rb_rem = clock();
    for (int i = 0; i < quantidade; i++)
    {
        rubroNegra_removeNo(arvore_rb, vetor[i], resultado);
    }
    clock_t fim_rb_rem = clock();

    // --------------------Cálculo dos tempos de execução--------------------

    resultado->tempo_execucao_remocao_avl = (double)(fim_avl_rem - inicio_avl_rem) / CLOCKS_PER_SEC;
    resultado->tempo_execucao_remocao_rb = (double)(fim_rb_rem - inicio_rb_rem) / CLOCKS_PER_SEC;

    // -------------------------- Impressão dos resultados --------------------------
    imprimeResultado(*resultado);

    // -------------------------- Liberação de memória --------------------------
    free(vetor);
    free(vetor_aleatorio);
    avl_liberaArvore(arvore_avl);
    rb_liberaArvore(arvore_rb);
    free(resultado);

    return 0;
}
