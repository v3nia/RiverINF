#include "Ranking.h"

Registro lista[MAX_SCORES]; // Array global com os top 5

// Inicializa o ranking (carrega do arquivo ou zera)
void CarregarRanking() {
    FILE *file = fopen(ARQUIVO_RANKING, "rb");
    if (file == NULL) {
        // Se não existe arquivo, cria lista vazia
        for (int i = 0; i < MAX_SCORES; i++) {
            strcpy(lista[i].nome, "VAZIO");
            lista[i].pontos = 0;
        }
    } else {
        fread(lista, sizeof(Registro), MAX_SCORES, file);
        fclose(file);
    }
}

// Salva a lista atual no arquivo
void SalvarRanking() {
    FILE *file = fopen(ARQUIVO_RANKING, "wb");
    if (file != NULL) {
        fwrite(lista, sizeof(Registro), MAX_SCORES, file);
        fclose(file);
    }
}

// Verifica a pontuacao pra entrar no Top 5
int VerificarRecorde(int score) {
    for (int i = 0; i < MAX_SCORES; i++) {
        if (score > lista[i].pontos) {
            return 1; // Eh recorde!
        }
    }
    return 0; // Não eh recorde
}

// Adiciona o novo recorde e reordena a lista
void AdicionarScore(const char *nome, int score) {
    // Encontrar a posicao
    int pos = -1;
    for (int i = 0; i < MAX_SCORES; i++) {
        if (score > lista[i].pontos) {
            pos = i;
            break;
        }
    }

    if (pos != -1) {
        // Empurrar os outros para baixo 
        for (int i = MAX_SCORES - 1; i > pos; i--) {
            lista[i] = lista[i - 1];
        }
    
        lista[pos].pontos = score;
        strcpy(lista[pos].nome, nome);
        
        SalvarRanking(); 
    }
}

void DesenharTelaRanking() {
    DrawText("TOP 5 JOGADORES", 320, 100, 40, DARKBLUE);
    
    for (int i = 0; i < MAX_SCORES; i++) {
        Color cor = BLACK;
        if (i == 0) cor = GOLD; // O primeiro fica dourado
        
        DrawText(TextFormat("%d. %s", i + 1, lista[i].nome), 250, 200 + (i * 60), 30, cor);
        DrawText(TextFormat("%d", lista[i].pontos), 600, 200 + (i * 60), 30, cor);
    }

    DrawText("Pressione ENTER para voltar", 300, 600, 20, GRAY);
}