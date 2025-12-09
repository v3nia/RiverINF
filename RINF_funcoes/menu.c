#include "menu.h"
#include "raylib.h"
#include "Ranking.h" 

// Variavel pra colocar nome no ranking
char nomeInput[20] = "";
int letrasCount = 0;

GameScreen funcmenu(GameScreen currentScreen, Player *jogador) {
    
    // LÓGICA 
    switch(currentScreen) {
        case SPLASH:
            if (IsKeyPressed(KEY_ENTER)) return MENU;
            break;

        case MENU:
            if (IsKeyPressed(KEY_ENTER)) return GAMEPLAY;
            if (IsKeyPressed(KEY_R)) return RANKING; // Atalho R para ranking
            if (IsKeyPressed(KEY_ESCAPE)) return END;
            break;

        case RANKING:
            if (IsKeyPressed(KEY_ENTER)) return MENU;
            break;

        case GAMEOVER:
            // Lógica de digitar o nome se for recorde
            if (VerificarRecorde(jogador->score)) {
                // Captura teclas digitadas
                int key = GetCharPressed();
                while (key > 0) {
                    if ((key >= 32) && (key <= 125) && (letrasCount < 10)) {
                        nomeInput[letrasCount] = (char)key;
                        nomeInput[letrasCount + 1] = '\0'; // Finaliza string
                        letrasCount++;
                    }
                    key = GetCharPressed();
                }
                // Backspace para apagar
                if (IsKeyPressed(KEY_BACKSPACE)) {
                    letrasCount--;
                    if (letrasCount < 0) letrasCount = 0;
                    nomeInput[letrasCount] = '\0';
                }

                // ENTER para Salvar
                if (IsKeyPressed(KEY_ENTER) && letrasCount > 0) {
                    AdicionarScore(nomeInput, jogador->score);
                    // Reseta variaveis
                    letrasCount = 0;
                    memset(nomeInput, 0, 20);
                    return RANKING; // Vai para tela de ranking 
                }
            } else {
                // Se não foi recorde, só aperta enter pra sair
                if (IsKeyPressed(KEY_ENTER)) return MENU;
            }
            break;
            
        default: break;
    }

    // DESENHO 
    BeginDrawing();
        ClearBackground(RAYWHITE);

        if (currentScreen == SPLASH) {
            DrawText("AVIÃOZINHO DO TRÁFICO", 200, 300, 40, DARKGRAY);
            DrawText("ENTER para iniciar", 350, 400, 20, DARKGRAY);
        }
        else if (currentScreen == MENU) {
            DrawText("MENU PRINCIPAL", 300, 200, 40, DARKBLUE);
            DrawText("[ENTER] Jogar", 320, 350, 20, BLACK);
            DrawText("[R] Ver Ranking", 320, 400, 20, BLACK);
            DrawText("[ESC] Sair", 320, 450, 20, BLACK);
        }
        else if (currentScreen == RANKING) {
            DesenharTelaRanking(); // Funcao no Ranking.c
        }
        else if (currentScreen == GAMEOVER) {
            DrawText("FIM DE JOGO!", 350, 150, 40, RED);
            DrawText(TextFormat("Sua Pontuação: %d", jogador->score), 320, 220, 30, BLACK);

            if (VerificarRecorde(jogador->score)) {
                DrawText("NOVO RECORDE!", 360, 300, 30, GOLD);
                DrawText("Digite seu nome e aperte ENTER:", 250, 350, 20, DARKGRAY);
                
                // Caixa de texto
                DrawRectangleLines(300, 380, 300, 50, BLACK);
                DrawText(nomeInput, 310, 390, 30, MAROON);
            } else {
                DrawText("Aperte ENTER para voltar", 300, 400, 20, GRAY);
            }
        }

    EndDrawing();

    return currentScreen;
}