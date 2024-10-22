#ifndef _H_ARVORES
#define _H_ARVORES

// Estrutura da árvore não balanceada
typedef struct No {
    int valor;
    struct No* esquerda;
    struct No* direita;
} No;

// Estrutura da árvore balanceada (AVL)
typedef struct NoAVL {
    int valor;
    int altura;
    struct NoAVL* esquerda;
    struct NoAVL* direita;
} NoAVL;

// árvore binária não balanceada
No* inserir_na_arvore(No* raiz, int valor);
No* remover_da_arvore(No* raiz, int valor);

// árvore balanceada (AVL)
NoAVL* inserir_na_arvore_avl(NoAVL* raiz, int valor);
NoAVL* remover_da_arvore_avl(NoAVL* raiz, int valor);

void executar_operacoes(const char* nome_arquivo, No** raiz_binaria, NoAVL** raiz_balanceada);

double arvore_binaria(int instancia_num);
double arvore_balanceada(int instancia_num);

#endif // _H_ARVORES
