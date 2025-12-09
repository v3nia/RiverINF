#include "definicoes.h"
#include "recursos.h"
#include "logica.h"
#include "ranking.h" 

// texto para quem tem toc
void DrawTextCentered(const char* text, int y, int fontSize, Color color) {
    int textWidth = MeasureText(text, fontSize);
    DrawText(text, (SCREEN_W - textWidth) / 2, y, fontSize, color);
}

int main(void) {
    InitWindow(SCREEN_W, SCREEN_H, "Aviãozinha do Tráfico");
    SetTargetFPS(60);

    // Inicializações
    Resources res;
    LoadResources(&res);
    CarregarRanking(); // <-- Carrega o ranking ao abrir o jogo

    Player jogador;
    MapData mapa;
    Projectile projeteis[MAX_PROJETEIS];
    GameScreen telaAtual = SPLASH;
    
    // Variáveis para Digitar o Nome (Input)
    char nomeInput[20] = "JOGADOR";
    int letrasCount = 0;

    InicializarProjeteis(projeteis);
    InicializarPlayer(&jogador);
    CarregarMapa(&mapa, 1);

    while (!WindowShouldClose()) {
        
        switch (telaAtual) {
            case SPLASH:
                if (IsKeyPressed(KEY_ENTER)) telaAtual = MENU;
                break;
            
            case MENU:
                if (IsKeyPressed(KEY_ENTER)) {
                    InicializarPlayer(&jogador);
                    InicializarProjeteis(projeteis);
                    CarregarMapa(&mapa, 1);
                    telaAtual = GAMEPLAY;
                }
                if (IsKeyPressed(KEY_R)) telaAtual = RANKING;
                break;

            case GAMEPLAY:
                // Atualiza Jogador e retorna se chegou no fim
                bool ChegouNoFim = UpdatePlayer(&jogador);
                // verifica se a fase acabou
                if (jogador.vidas <= 0 || ChegouNoFim) {
                    
                    if (ChegouNoFim) {
                        jogador.score += 1000; 
                        jogador.y = 700; // reseta a posição do jogador
                    }

                    if (VerificarRecorde(jogador.score)) {
                        telaAtual = NEW_RECORD;
                        memset(nomeInput, 0, 20);
                        letrasCount = 0;
                    } else {
                        telaAtual = GAMEOVER;
                    }
                } // olha o tamanho dessa garantia, porque o recorde tava bugando de novo
                
                // Lógica de Tiro
                if (IsKeyPressed(KEY_SPACE) && jogador.cooldown == 0) {
                    Atirar(projeteis, jogador);
                    jogador.cooldown = 30; // Cooldown de 0.5s
                }
                UpdateProjeteis(projeteis);
                VerificarColisaoTiros(projeteis, &mapa, &jogador);
                VerificarColisoes(&jogador, &mapa);
                
                // Pontuação extra por andar
                if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) jogador.score++;

                // --- LÓGICA DE MORTE OU VITÓRIA ---
                // Se morreu OU chegou no fim
                if (jogador.vidas <= 0 || ChegouNoFim) {

                    // Verifica Ranking imediatamente e muda de tela
                    //(ele tava bugando e pedindo 5 vezes o nome)
                    if (VerificarRecorde(jogador.score)) {
                        telaAtual = NEW_RECORD;
                        memset(nomeInput, 0, 20);
                        letrasCount = 0;
                    } else {
                        telaAtual = GAMEOVER;
                    }
                }
                break;

            case NEW_RECORD:
                int key = GetCharPressed(); //top coisas chatas apesar de facil
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
        ClearBackground(BLUE);

        switch (telaAtual) {
            case SPLASH:
                DrawTextCentered("Aviãozinha do Tráfico", 300, 70, GOLD);
                DrawTextCentered("Pressione ENTER", 400, 30, GOLD);
                break;

            case MENU:
                DrawTextCentered("MENU PRINCIPAL", 200, 60, YELLOW);
                DrawTextCentered("[Enter] Jogar", 300, 30, YELLOW);
                DrawTextCentered("[R] Ranking", 350, 30, YELLOW);
                DrawTextCentered("[Esc] Sair", 400, 30, YELLOW);
                break;

            case GAMEPLAY:
                UpdatePlayer(&jogador);
                VerificarColisoes(&jogador, &mapa);
                // ... logica score ...

                BeginDrawing();
                ClearBackground(BLUE);


                DesenharMapa(&mapa, &res, jogador.y);
                
                int cameraY = (int)jogador.y - 600;
                
                if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
                    DrawTexture(res.playerE, jogador.x, jogador.y - cameraY, WHITE);
                } 
                // Verifica Setinha Direita OU tecla 'D'
                else if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
                    DrawTexture(res.playerD, jogador.x, jogador.y - cameraY, WHITE);
                } 
                // Se nada apertado, desenha o normal
                else {
                    DrawTexture(res.player, jogador.x, jogador.y - cameraY, WHITE);
                }
                DrawProjeteis(projeteis, cameraY);
                
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