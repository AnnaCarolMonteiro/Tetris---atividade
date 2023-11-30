#include <stdio.h>
#include <string.h>

#define NUM_JOGADORES 1000
#define NUM_JOGOS 12
#define MAX_CARACTERES_NOME 15

typedef struct {
    char nome[MAX_CARACTERES_NOME + 1];  // +1 para o caractere nulo
    int pontos[NUM_JOGOS];
    int totalPontos;
} Jogador;

void obterPontuacao(int *pontuacao) {
    do {
        printf("Informe a pontuacao (0 a 1000): ");
        scanf("%d", pontuacao);

        if (*pontuacao < 0 || *pontuacao > 1000) {
            printf("Erro: Pontuacao invalida. Tente novamente.\n");
        }
    } while (*pontuacao < 0 || *pontuacao > 1000);
}

void ordenarPontuacoes(int *pontuacoes) {
    // Implementação de um algoritmo de ordenação
    for (int i = 0; i < NUM_JOGOS - 1; i++) {
        for (int j = 0; j < NUM_JOGOS - i - 1; j++) {
            if (pontuacoes[j] > pontuacoes[j + 1]) {
                // Troca as pontuações de posição
                int temp = pontuacoes[j];
                pontuacoes[j] = pontuacoes[j + 1];
                pontuacoes[j + 1] = temp;
            }
        }
    }
}

void ordenarJogadores(Jogador *jogadores, int numJogadores) {
    // Implementação de um algoritmo de ordenação (ex: Bubble Sort)
    for (int i = 0; i < numJogadores - 1; i++) {
        for (int j = 0; j < numJogadores - i - 1; j++) {
            if (jogadores[j].totalPontos < jogadores[j + 1].totalPontos) {
                // aqui acontece a troca de posição
                Jogador temp = jogadores[j];
                jogadores[j] = jogadores[j + 1];
                jogadores[j + 1] = temp;
            }
        }
    }
}

int main() {
    Jogador jogadores[NUM_JOGADORES];
    int numJogadoresAtual = 0;
    int adicionarMaisJogadores;

    do {
        printf("Informe o nome do jogador (maximo de 15 caracteres): ");
        fgets(jogadores[numJogadoresAtual].nome, sizeof jogadores[numJogadoresAtual].nome, stdin);
        jogadores[numJogadoresAtual].nome[strcspn(jogadores[numJogadoresAtual].nome, "\n")] = 0; // Aqui removemos a quebra de linha

        // o nome terá até 15 caracteres
        if (strlen(jogadores[numJogadoresAtual].nome) > MAX_CARACTERES_NOME) {
            jogadores[numJogadoresAtual].nome[MAX_CARACTERES_NOME] = '\0';
        }

        for (int i = 0; i < NUM_JOGOS; i++) {
            printf("Informe a pontuacao do jogo %d para %s\n", i + 1, jogadores[numJogadoresAtual].nome);
            obterPontuacao(&jogadores[numJogadoresAtual].pontos[i]);
        }

        // Duda aqui vai ordenar as pontuações do jogador em ordem crescente
        ordenarPontuacoes(jogadores[numJogadoresAtual].pontos);

        // Aqui calcula a pontuação total do jogador desconsiderando a maior e a menor pontuação
        jogadores[numJogadoresAtual].totalPontos = 0;
        for (int i = 1; i < NUM_JOGOS - 1; i++) {
            jogadores[numJogadoresAtual].totalPontos += jogadores[numJogadoresAtual].pontos[i];
        }

        numJogadoresAtual++;

        printf("Deseja adicionar mais jogadores? (1 para sim, 0 para nao): ");
        scanf("%d", &adicionarMaisJogadores);
    } while (adicionarMaisJogadores == 1 && numJogadoresAtual < NUM_JOGADORES);

    // Aqui vai ordenar os jogadores com base na pontuação total
    ordenarJogadores(jogadores, numJogadoresAtual);

    // Aqui o código vai imprimir a classificação
    printf("\nClassificacao:\n");
    for (int i = 0; i < numJogadoresAtual; i++) {
        printf("%d Lugar: %s - Pontuacao: %d\n", i + 1, jogadores[i].nome, jogadores[i].totalPontos);
    }

    return 0;
}
