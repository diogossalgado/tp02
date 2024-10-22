#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvores.h"

int main(int argc, char* argv[]) {
    // Leitor de instâncias (não modificado)
    int instancia_num = -1;
    instancia_num = atoi(argv[1]);
    if (instancia_num <= 0 || instancia_num > 10) {
        printf("Para executar o codigo, digite ./arvores x\nonde x eh um numero entre 1 e 10 que simboliza a instancia utilizada\n");
        exit(0);
    }

    double tempo_n_balanceada = arvore_binaria(instancia_num);
    double tempo_balanceada = arvore_balanceada(instancia_num);


    // imprime a nao balanceada e depois a balanceada
    printf("%f\n%f\n", tempo_n_balanceada, tempo_balanceada);

    return (1);
}
