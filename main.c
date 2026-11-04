#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO_LINHA 128

/* Lê uma linha e remove a quebra de linha, se houver. */
int ler_linha(char linha[], size_t tamanho) {
    if (fgets(linha, tamanho, stdin) == NULL) {
        return 0;
    }

    size_t comprimento = strlen(linha);

    if (comprimento > 0 && linha[comprimento - 1] == '\n') {
        linha[comprimento - 1] = '\0';
    } else {
        /* Descarta o restante caso a entrada seja maior que o vetor. */
        int caractere;
        while ((caractere = getchar()) != '\n' && caractere != EOF) {
        }
    }

    return 1;
}

/* Verifica se há apenas espaços depois do valor informado. */
int somente_espacos(const char *texto) {
    while (*texto != '\0') {
        if (!isspace((unsigned char)*texto)) {
            return 0;
        }
        texto++;
    }

    return 1;
}

/* Lê e valida uma opção inteira entre 1 e 5. */
int ler_opcao(int *opcao) {
    char linha[TAMANHO_LINHA];

    while (1) {
        printf("Opção: ");

        if (!ler_linha(linha, sizeof(linha))) {
            return 0;
        }

        char *fim;
        errno = 0;
        long valor = strtol(linha, &fim, 10);

        if (linha == fim || errno == ERANGE ||
            !somente_espacos(fim) || valor < 1 || valor > 5) {
            printf("Opção inválida. Digite um número inteiro entre 1 e 5.\n");
            continue;
        }

        *opcao = (int)valor;
        return 1;
    }
}

/* Lê um número decimal ou inteiro. */
int ler_numero(const char *mensagem, double *numero) {
    char linha[TAMANHO_LINHA];

    while (1) {
        printf("%s", mensagem);

        if (!ler_linha(linha, sizeof(linha))) {
            return 0;
        }

        char *fim;
        errno = 0;
        double valor = strtod(linha, &fim);

        if (linha == fim || errno == ERANGE ||
            !somente_espacos(fim) || !isfinite(valor)) {
            printf("Entrada inválida. Digite um número válido.\n");
            continue;
        }

        *numero = valor;
        return 1;
    }
}

/* Pergunta novamente até receber 's' ou 'n'. */
int deseja_continuar(void) {
    char linha[TAMANHO_LINHA];

    while (1) {
        printf("Deseja realizar outra operação? (s/n): ");

        if (!ler_linha(linha, sizeof(linha))) {
            return 0;
        }

        if (linha[0] != '\0' && somente_espacos(linha + 1)) {
            char resposta = (char)tolower((unsigned char)linha[0]);

            if (resposta == 's') {
                return 1;
            }
            if (resposta == 'n') {
                return 0;
            }
        }

        printf("Resposta inválida. Por favor, digite 's' para sim ou 'n' para não.\n");
    }
}

int main(void) {
    int continuar = 1;

    while (continuar) {
        int opcao;

        printf("===============================\n");
        printf("   Calculadora Simples\n");
        printf("===============================\n");
        printf("Selecione uma operação:\n");
        printf("1. Adição\n");
        printf("2. Subtração\n");
        printf("3. Multiplicação\n");
        printf("4. Divisão\n");
        printf("5. Sair\n");

        if (!ler_opcao(&opcao)) {
            break;
        }

        if (opcao == 5) {
            break;
        }

        double numero1;
        double numero2;

        if (!ler_numero("Digite o primeiro número: ", &numero1) ||
            !ler_numero("Digite o segundo número: ", &numero2)) {
            break;
        }

        char operador;

        switch (opcao) {
            case 1:
                operador = '+';
                printf("Resultado: %g %c %g = %g\n",
                       numero1, operador, numero2, numero1 + numero2);
                break;

            case 2:
                operador = '-';
                printf("Resultado: %g %c %g = %g\n",
                       numero1, operador, numero2, numero1 - numero2);
                break;

            case 3:
                operador = '*';
                printf("Resultado: %g %c %g = %g\n",
                       numero1, operador, numero2, numero1 * numero2);
                break;

            case 4:
                operador = '/';

                if (numero2 == 0.0) {
                    printf("Erro: Divisão por zero não é permitida.\n");
                } else {
                    printf("Resultado: %g %c %g = %g\n",
                           numero1, operador, numero2, numero1 / numero2);
                }
                break;
        }

        continuar = deseja_continuar();
    }

    printf("Obrigado por usar a calculadora! Até a próxima.\n");
    return 0;
}