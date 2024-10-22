#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "arvores.h"


void executar_operacoes(const char* nome_arquivo, No** raiz_binaria, NoAVL** raiz_balanceada) {
    FILE* arquivo = fopen(nome_arquivo, "r");
    // Caso ocorra algum erro ao abrir o arquivo avisa o usuário e encerra o programa
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }

    char comando; // Referente a "I" e "R"
    int numero; // Referente ao número que será inserido ou removido da árvore
    while (fscanf(arquivo, " %c %d", &comando, &numero) == 2) {
        if (comando == 'I') {
            *raiz_binaria = inserir_na_arvore(*raiz_binaria, numero);
            *raiz_balanceada = inserir_na_arvore_avl(*raiz_balanceada, numero);
        } else if (comando == 'R') {
            *raiz_binaria = remover_da_arvore(*raiz_binaria, numero);
            *raiz_balanceada = remover_da_arvore_avl(*raiz_balanceada, numero);
        }
    }
    fclose(arquivo);
}

double arvore_binaria(int instancia_num) {
    double tempo = 0;
    clock_t begin = clock();

    No* raiz_binaria = NULL;
    NoAVL* raiz_balanceada = NULL;

    char nome_arquivo[10];
    sprintf(nome_arquivo, "instancias/%d", instancia_num);
    executar_operacoes(nome_arquivo, &raiz_binaria, &raiz_balanceada);

    clock_t end = clock();
    // calcula o tempo decorrido encontrando a diferença (end - begin),
    // divide a diferença por CLOCKS_PER_SEC p/ converter em segundos e converte em milissegundos
    tempo += (double)(end - begin) / CLOCKS_PER_SEC * 1000;
    return tempo;
}

double arvore_balanceada(int instancia_num) {
    double tempo = 0;
    clock_t begin = clock();

    No* raiz_binaria = NULL;
    NoAVL* raiz_balanceada = NULL;

    char nome_arquivo[10];
    sprintf(nome_arquivo, "instancias/%d", instancia_num);
    executar_operacoes(nome_arquivo, &raiz_binaria, &raiz_balanceada);

    clock_t end = clock();
    // calcula o tempo decorrido encontrando a diferença (end - begin),
    // divide a diferença por CLOCKS_PER_SEC p/ converter em segundos e converte em milissegundos
    tempo += (double)(end - begin) / CLOCKS_PER_SEC * 1000; 
    return tempo;
}

// Função para criar um novo nó para a árvore não balanceada
No* criar_no(int valor) {
    No* novo_no = (No*)malloc(sizeof(No));
    novo_no->valor = valor;
    novo_no->esquerda = NULL;
    novo_no->direita = NULL;
    return novo_no;
}

// Função para inserir um novo nó na árvore não balanceada
No* inserir_na_arvore(No* raiz, int valor) {
    if (raiz == NULL) {
        return criar_no(valor);
    }
    if (valor < raiz->valor) {
        raiz->esquerda = inserir_na_arvore(raiz->esquerda, valor);
    } else {
        raiz->direita = inserir_na_arvore(raiz->direita, valor);
    }
    return raiz;
}

// Função para remover um nó da árvore não balanceada
No* remover_da_arvore(No* raiz, int valor) {
    if (raiz == NULL) return raiz;

    if (valor < raiz->valor) {
        raiz->esquerda = remover_da_arvore(raiz->esquerda, valor);
    } else if (valor > raiz->valor) {
        raiz->direita = remover_da_arvore(raiz->direita, valor);
    } else {
        if (raiz->esquerda == NULL) {
            No* no_temporario = raiz->direita;
            free(raiz);
            return no_temporario;
        } else if (raiz->direita == NULL) {
            No* no_temporario = raiz->esquerda;
            free(raiz);
            return no_temporario;
        }
        No* no_substituto = raiz->direita;
        while (no_substituto && no_substituto->esquerda != NULL) {
            no_substituto = no_substituto->esquerda;
        }
        raiz->valor = no_substituto->valor;
        raiz->direita = remover_da_arvore(raiz->direita, no_substituto->valor);
    }
    return raiz;
}

// Função para criar um novo nó para a árvore balanceada (AVL)
NoAVL* criar_no_avl(int valor) {
    NoAVL* novo_no = (NoAVL*)malloc(sizeof(NoAVL));
    novo_no->valor = valor;
    novo_no->altura = 1; // Novo nó é adicionado na folha
    novo_no->esquerda = NULL;
    novo_no->direita = NULL;
    return novo_no;
}

// Função para calcular a altura de um nó
int obter_altura(NoAVL* no_atual) {
    if (no_atual == NULL) return 0;
    return no_atual->altura;
}

// Função para calcular o fator de balanceamento
int calcular_fator_balanceamento(NoAVL* no_atual) {
    if (no_atual == NULL) return 0;
    return obter_altura(no_atual->esquerda) - obter_altura(no_atual->direita);
}

// Funções de rotação para balanceamento da árvore AVL
NoAVL* balancear_direita(NoAVL* raiz) {
    NoAVL* nova_raiz = raiz->esquerda;
    NoAVL* no_temporario = nova_raiz->direita;

    nova_raiz->direita = raiz;
    raiz->esquerda = no_temporario;

    raiz->altura = 1 + (obter_altura(raiz->esquerda) > obter_altura(raiz->direita) ? obter_altura(raiz->esquerda) : obter_altura(raiz->direita));
    nova_raiz->altura = 1 + (obter_altura(nova_raiz->esquerda) > obter_altura(nova_raiz->direita) ? obter_altura(nova_raiz->esquerda) : obter_altura(nova_raiz->direita));

    return nova_raiz;
}

NoAVL* balancear_esquerda(NoAVL* raiz) {
    NoAVL* nova_raiz = raiz->direita;
    NoAVL* no_temporario = nova_raiz->esquerda;

    nova_raiz->esquerda = raiz;
    raiz->direita = no_temporario;

    raiz->altura = 1 + (obter_altura(raiz->esquerda) > obter_altura(raiz->direita) ? obter_altura(raiz->esquerda) : obter_altura(raiz->direita));
    nova_raiz->altura = 1 + (obter_altura(nova_raiz->esquerda) > obter_altura(nova_raiz->direita) ? obter_altura(nova_raiz->esquerda) : obter_altura(nova_raiz->direita));

    return nova_raiz;
}

// Função para inserir um nó na árvore AVL
NoAVL* inserir_na_arvore_avl(NoAVL* raiz, int valor) {
    if (raiz == NULL) return criar_no_avl(valor);

    if (valor < raiz->valor) {
        raiz->esquerda = inserir_na_arvore_avl(raiz->esquerda, valor);
    } else {
        raiz->direita = inserir_na_arvore_avl(raiz->direita, valor);
    }

    raiz->altura = 1 + (obter_altura(raiz->esquerda) > obter_altura(raiz->direita) ? obter_altura(raiz->esquerda) : obter_altura(raiz->direita));

    int fator = calcular_fator_balanceamento(raiz);

    if (fator > 1 && valor < raiz->esquerda->valor) {
        return balancear_direita(raiz);
    }

    if (fator < -1 && valor > raiz->direita->valor) {
        return balancear_esquerda(raiz);
    }

    if (fator > 1 && valor > raiz->esquerda->valor) {
        raiz->esquerda = balancear_esquerda(raiz->esquerda);
        return balancear_direita(raiz);
    }

    if (fator < -1 && valor < raiz->direita->valor) {
        raiz->direita = balancear_direita(raiz->direita);
        return balancear_esquerda(raiz);
    }

    return raiz;
}

// Função para remover um nó da árvore AVL
NoAVL* remover_da_arvore_avl(NoAVL* raiz, int valor) {
    if (raiz == NULL) return raiz;

    if (valor < raiz->valor) {
        raiz->esquerda = remover_da_arvore_avl(raiz->esquerda, valor);
    } else if (valor > raiz->valor) {
        raiz->direita = remover_da_arvore_avl(raiz->direita, valor);
    } else {
        if (raiz->esquerda == NULL) {
            NoAVL* no_temporario = raiz->direita;
            free(raiz);
            return no_temporario;
        } else if (raiz->direita == NULL) {
            NoAVL* no_temporario = raiz->esquerda;
            free(raiz);
            return no_temporario;
        }

        NoAVL* no_substituto = raiz->direita;
        while (no_substituto && no_substituto->esquerda != NULL) {
            no_substituto = no_substituto->esquerda;
        }
        raiz->valor = no_substituto->valor;
        raiz->direita = remover_da_arvore_avl(raiz->direita, no_substituto->valor);
    }

    raiz->altura = 1 + (obter_altura(raiz->esquerda) > obter_altura(raiz->direita) ? obter_altura(raiz->esquerda) : obter_altura(raiz->direita));

    int fator = calcular_fator_balanceamento(raiz);

    if (fator > 1 && calcular_fator_balanceamento(raiz->esquerda) >= 0) {
        return balancear_direita(raiz);
    }

    if (fator < -1 && calcular_fator_balanceamento(raiz->direita) <= 0) {
        return balancear_esquerda(raiz);
    }

    if (fator > 1 && calcular_fator_balanceamento(raiz->esquerda) < 0) {
        raiz->esquerda = balancear_esquerda(raiz->esquerda);
        return balancear_direita(raiz);
    }

    if (fator < -1 && calcular_fator_balanceamento(raiz->direita) > 0) {
        raiz->direita = balancear_direita(raiz->direita);
        return balancear_esquerda(raiz);
    }

    return raiz;
}
