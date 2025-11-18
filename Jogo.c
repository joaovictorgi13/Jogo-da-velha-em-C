#include <stdio.h>
#include <stdlib.h>

// Função que desenha o tabuleiro na tela
void desenharTabuleiro(char tabuleiro[3][3]) {
    system("cls"); // Limpa a tela
    printf("\n");

    // Loop para imprimir cada linha do tabuleiro
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {// Loop para imprimir colunas
            printf(" %c ", tabuleiro[i][j]); // Imprime o caractere (posição ou X/O)
            if (j < 2) printf("|");          // Barras verticais
        }

        printf("\n");
        if (i < 2) printf("---+---+---\n"); // Linha separadora
    }
    printf("\n");
}

// Coloca a jogada no tabuleiro
char jogar(char tabuleiro[3][3], int posicao, char jogadorAtual) {
    // Calcula linha e coluna usando a posição (1-9)
    int linha = (posicao - 1) / 3;
    int coluna = (posicao - 1) % 3;

    // Se já estiver ocupado, retorna 1
    if (tabuleiro[linha][coluna] == 'X' || tabuleiro[linha][coluna] == 'O')
        return 1;

    // Caso contrário, marca a jogada
    tabuleiro[linha][coluna] = jogadorAtual;
    return 0; 
}

// Verifica se alguém venceu
char verificaVitoria(char tabuleiro[3][3]) {

    // Verifica linhas e colunas
    for (int i = 0; i < 3; i++) {

        // Verifica linha i
        if (tabuleiro[i][0] == tabuleiro[i][1] &&
            tabuleiro[i][1] == tabuleiro[i][2])
            return 1;

        // Verifica coluna i
        if (tabuleiro[0][i] == tabuleiro[1][i] &&
            tabuleiro[1][i] == tabuleiro[2][i])
            return 1;
    }

    // Verifica diagonal principal
    if (tabuleiro[0][0] == tabuleiro[1][1] &&
        tabuleiro[1][1] == tabuleiro[2][2])
        return 1;

    // Verifica diagonal secundária
    if (tabuleiro[0][2] == tabuleiro[1][1] &&
        tabuleiro[1][1] == tabuleiro[2][0])
        return 1;

    return 0; // Ninguém venceu ainda
}

int main(int argc, char *argv[]) {
    // Tabuleiro inicial — cada posição contém um número
    char tabuleiro[3][3] = {
        {'1', '2', '3'},
        {'4', '5', '6'},
        {'7', '8', '9'}
    };

    int jogada = 0;   // Conta número de jogadas realizadas
    int posicao;      // Posição que o jogador escolhe
    int leitura;      // Controle de leitura do scanf

    // Máximo de 9 jogadas — se ninguém vencer, é empate
    while (jogada < 9) {

        desenharTabuleiro(tabuleiro);

        // Alternância entre jogadores X e O
        char jogadorAtual = (jogada % 2 == 0) ? 'X' : 'O';

        printf("Jogador %c, escolha uma posicao (1-9): ", jogadorAtual);

        // Lê a entrada e verifica se é válida
        leitura = scanf("%d", &posicao);

        // Verifica se o usuário digitou algo NÃO numérico
        if (leitura != 1) {
            int c;
            // Limpa buffer do teclado
            while ((c = getchar()) != '\n' && c != EOF);
            
            printf("Entrada invalida! Digite um numero entre 1 e 9.\n");
            printf("Pressione Enter para continuar...");
            getchar();
            continue;
        }

        // Limpa buffer após ler número
        int c;
        while ((c = getchar()) != '\n' && c != EOF);

        // Verifica se está entre 1 e 9
        if (posicao < 1 || posicao > 9) {
            printf("Posicao invalida! Escolha um numero entre 1 e 9.\n");
            printf("Pressione Enter para continuar...");
            getchar();
            continue;
        }

        // Verifica se a posição já está ocupada
        if (jogar(tabuleiro, posicao, jogadorAtual)) {
            printf("Posicao ja ocupada! Tente novamente.\n");
            printf("Pressione Enter para continuar...");
            getchar();
            continue;
        }

        // Após uma jogada válida, verifica se o jogador venceu
        if (verificaVitoria(tabuleiro)) {
            desenharTabuleiro(tabuleiro);
            printf("Jogador %c venceu!!!\n", jogadorAtual);
            break;
        }

        jogada++; // Próxima jogada
    }

    // Se terminou 9 jogadas e ninguém ganhou → empate
    if (jogada == 9 && !verificaVitoria(tabuleiro)) {
        desenharTabuleiro(tabuleiro);
        printf("Empate!!\n");
    }

    printf("Fim de Jogo! Pressione Enter para sair...");
    getchar(); // Pausa final

    return 0;
}
