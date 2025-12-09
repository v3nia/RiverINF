#include "definicoes.h"
// Inclua os módulos
#include "recursos.h"
#include "logica.h"
#include "ranking.h" // <-- Inclua o ranking aqui

int main(void) {
    InitWindow(SCREEN_W, SCREEN_H, "River Raid - Final");
    SetTargetFPS(60);

    // Inicializações
    Resources res;
    LoadResources(&res);
    CarregarRanking(); // <-- Carrega o ranking ao abrir o jogo

    Player jogador;
    MapData mapa;
    GameScreen telaAtual = SPLASH;
    
    // Variáveis para Digitar o Nome (Input)
    char nomeInput[20] = "JOGADOR";
    int letrasCount = 0;

    InicializarPlayer(&jogador);
    CarregarMapa(&mapa, 1);

    while (!WindowShouldClose()) {
        
        // --- UPDATE ---
        switch (telaAtual) {
            case SPLASH:
                if (IsKeyPressed(KEY_ENTER)) telaAtual = MENU;
                break;
            
            case MENU:
                if (IsKeyPressed(KEY_ENTER)) {
                    InicializarPlayer(&jogador); // Reseta score e vidas
                    telaAtual = GAMEPLAY;
                }
                if (IsKeyPressed(KEY_R)) telaAtual = RANKING;
                break;

            case GAMEPLAY:
                UpdatePlayer(&jogador);
                VerificarColisoes(&jogador, &mapa);
                
                if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) jogador.score++;

                if (jogador.vidas <= 0) {
                    // Verifica se bateu recorde ao morrer
                    if (VerificarRecorde(jogador.score)) {
                        telaAtual = NEW_RECORD;
                        // Reseta variáveis de input
                        memset(nomeInput, 0, 20);
                        letrasCount = 0;
                    } else {
                        telaAtual = GAMEOVER;
                    }
                }
                break;

            case NEW_RECORD:
                // --- Lógica de Digitação (Raylib Standard) ---
                int key = GetCharPressed();
                while (key > 0) {
                    if ((key >= 32) && (key <= 125) && (letrasCount < 15)) {
                        nomeInput[letrasCount] = (char)key;
                        nomeInput[letrasCount + 1] = '\0';
                        letrasCount++;
                    }
                    key = GetCharPressed();
                }
                if (IsKeyPressed(KEY_BACKSPACE)) {
                    letrasCount--;
                    if (letrasCount < 0) letrasCount = 0;
                    nomeInput[letrasCount] = '\0';
                }
                if (IsKeyPressed(KEY_ENTER) && letrasCount > 0) {
                    AdicionarScore(nomeInput, jogador.score);
                    telaAtual = RANKING; // Vai para a tela de ranking mostrar o feito
                }
                break;

            case GAMEOVER:
                if (IsKeyPressed(KEY_ENTER)) telaAtual = MENU;
                break;

            case RANKING:
                if (IsKeyPressed(KEY_ENTER)) telaAtual = MENU;
                break;
                
            default: break;
        }

        // --- DRAW ---
        BeginDrawing();
        ClearBackground(RAYWHITE);

        switch (telaAtual) {
            case SPLASH:
                DrawText("Aviãozinha do Tráfico", 300, 300, 50, BLUE);
                DrawText("Pressione ENTER", 350, 400, 20, DARKGRAY);
                break;

            case MENU:
                DrawText("MENU PRINCIPAL", 300, 200, 40, DARKBLUE);
                DrawText("[ENTER] Jogar", 320, 300, 20, BLACK);
                DrawText("[R] Ranking", 320, 350, 20, BLACK);
                break;

            case GAMEPLAY:
                UpdatePlayer(&jogador);
                VerificarColisoes(&jogador, &mapa);
                // ... logica score ...

                BeginDrawing();
                ClearBackground(BLUE);


                DesenharMapa(&mapa, &res, jogador.y);
                
                // O Player é desenhado variadamente baseado na posição Y
                
                float screenPlayerY = 600; // Posição fixa visual na tela (parte de baixo)

                // Se o mapa desce (cameraY), o jogador tem que ser desenhado
                // na coordenada: Mundo - Camera
                int cameraY = (int)jogador.y - 600;
                
                if (IsKeyDown(KEY_LEFT)) DrawTexture(res.playerE, jogador.x, jogador.y - cameraY, WHITE);
                else if (IsKeyDown(KEY_RIGHT)) DrawTexture(res.playerD, jogador.x, jogador.y - cameraY, WHITE);
                else DrawTexture(res.player, jogador.x, jogador.y - cameraY, WHITE);
                
                // ... HUD ...
                DrawText(TextFormat("SCORE: %05d", jogador.score), 700, 10, 20, WHITE);
                DrawText(TextFormat("VIDAS: %d", jogador.vidas), 200, 10, 20, GREEN);
                break;

            case NEW_RECORD:
                ClearBackground(BLACK);
                DrawText("NOVO RECORDE!", 300, 200, 40, GREEN);
                DrawText(TextFormat("PONTOS: %d", jogador.score), 350, 280, 30, WHITE);
                
                DrawText("Digite seu nome:", 350, 400, 20, GRAY);
                DrawRectangle(340, 430, 300, 50, DARKGRAY);
                DrawText(nomeInput, 350, 440, 30, WHITE);
                
                if (letrasCount < 15 && (GetTime() * 2 - (int)(GetTime() * 2)) < 0.5f) {
                     DrawText("_", 350 + MeasureText(nomeInput, 30), 440, 30, RED); // Cursor piscando
                }
                DrawText("Pressione ENTER para Salvar", 300, 600, 20, GRAY);
                break;

            case GAMEOVER:
                DrawText("GAME OVER", 350, 300, 50, RED);
                DrawText(TextFormat("Score Final: %d", jogador.score), 380, 380, 20, BLACK);
                DrawText("Pressione ENTER", 390, 450, 20, GRAY);
                break;

            case RANKING:
                ClearBackground(BLACK);
                DesenharTelaRanking();
                break;
        }

        EndDrawing();
    }

    UnloadResources(&res);
    CloseWindow();
    return 0;
}