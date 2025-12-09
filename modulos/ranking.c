#include "definicoes.h"
#include "ranking.h"

// Variável global APENAS dentro deste arquivo (static) para guardar a lista

// Inicializa o ranking (carrega do arquivo ou zera)
void CarregarRanking() {
    FILE *file = fopen(ARQUIVO_RANKING, "rb");
    if (file == NULL) {
        // Se não existe, cria lista vazia
        for (int i = 0; i < MAX_SCORES; i++) {
            strcpy(lista[i].nome, "---");
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

// Verifica se a pontuação entra no Top 5
bool VerificarRecorde(int score) {
    if (score <= 0) return false;
    for (int i = 0; i < MAX_SCORES; i++) {
        if (score > lista[i].pontos) {
            return true; // É recorde!
        }
    }
    return false;
}

// Adiciona o novo recorde e reordena a lista
void AdicionarScore(const char *nome, int score) {
    int pos = -1;
    // Descobre a posição
    for (int i = 0; i < MAX_SCORES; i++) {
        if (score > lista[i].pontos) {
            pos = i;
            break;
        }
    }

    if (pos != -1) {
        // Empurra os outros para baixo
        for (int i = MAX_SCORES - 1; i > pos; i--) {
            lista[i] = lista[i - 1];
        }
        // Insere o novo
        lista[pos].pontos = score;
        strcpy(lista[pos].nome, nome);
        
        SalvarRanking(); 
    }
}

// Apenas desenha a tabela (sem lógica de loop)
void DesenharTelaRanking() {
    DrawText("TOP 5 PILOTOS", 350, 150, 40, GOLD);

    for (int i = 0; i < MAX_SCORES; i++) {
        Color cor = WHITE;
        if (i == 0) cor = YELLOW; // O primeiro fica amarelo
        
        DrawText(TextFormat("%d. %s", i + 1, lista[i].nome), 300, 250 + (i * 60), 30, cor);
        DrawText(TextFormat("%05d", lista[i].pontos), 600, 250 + (i * 60), 30, cor);
    }

    DrawText("Pressione [ENTER] para Voltar", 300, 600, 20, GRAY);
}