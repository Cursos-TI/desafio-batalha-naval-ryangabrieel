#include <stdio.h>

#define TAM_TABULEIRO 10
#define TAM_HABILIDADE 5

// Função para inicializar o tabuleiro com água (0)
void inicializarTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            tabuleiro[i][j] = 0;
        }
    }

    // Exemplo: adiciona alguns navios manualmente
    tabuleiro[2][2] = 3;
    tabuleiro[4][5] = 3;
    tabuleiro[7][7] = 3;
}

// Função para criar matriz Cone (tipo pirâmide invertida)
void criarMatrizCone(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE]) {
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            int meio = TAM_HABILIDADE / 2;
            habilidade[i][j] = (j >= meio - i && j <= meio + i) ? 1 : 0;
        }
    }
}

// Função para criar matriz Cruz
void criarMatrizCruz(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE]) {
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            habilidade[i][j] = (i == TAM_HABILIDADE / 2 || j == TAM_HABILIDADE / 2) ? 1 : 0;
        }
    }
}

// Função para criar matriz Octaedro (losango)
void criarMatrizOctaedro(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE]) {
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            int meio = TAM_HABILIDADE / 2;
            habilidade[i][j] = (abs(i - meio) + abs(j - meio) <= meio) ? 1 : 0;
        }
    }
}

// Sobrepõe a habilidade no tabuleiro com valor 5
void aplicarHabilidadeNoTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO],
                                   int habilidade[TAM_HABILIDADE][TAM_HABILIDADE],
                                   int origemLinha, int origemColuna) {
    int offset = TAM_HABILIDADE / 2;

    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            if (habilidade[i][j] == 1) {
                int linha = origemLinha + i - offset;
                int coluna = origemColuna + j - offset;

                // Verifica se está dentro dos limites
                if (linha >= 0 && linha < TAM_TABULEIRO &&
                    coluna >= 0 && coluna < TAM_TABULEIRO) {
                    if (tabuleiro[linha][coluna] != 3) {
                        tabuleiro[linha][coluna] = 5;
                    }
                }
            }
        }
    }
}

// Exibe o tabuleiro formatado
void exibirTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    printf("Tabuleiro:\n");
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            switch(tabuleiro[i][j]) {
                case 0: printf("~ "); break;  // Água
                case 3: printf("N "); break;  // Navio
                case 5: printf("* "); break;  // Área afetada
                default: printf("? "); break;
            }
        }
        printf("\n");
    }
}

int main() {
    int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO];
    int habilidade[TAM_HABILIDADE][TAM_HABILIDADE];

    inicializarTabuleiro(tabuleiro);

    // Aplica Cone
    criarMatrizCone(habilidade);
    aplicarHabilidadeNoTabuleiro(tabuleiro, habilidade, 3, 3);

    // Aplica Cruz
    criarMatrizCruz(habilidade);
    aplicarHabilidadeNoTabuleiro(tabuleiro, habilidade, 6, 6);

    // Aplica Octaedro
    criarMatrizOctaedro(habilidade);
    aplicarHabilidadeNoTabuleiro(tabuleiro, habilidade, 1, 8);

    // Exibe resultado final
    exibirTabuleiro(tabuleiro);

    return 0;
}
