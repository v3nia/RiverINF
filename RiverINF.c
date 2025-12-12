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
    InitAudioDevice();
    SetTargetFPS(60);

    // Inicializações
    Resources res;
    LoadResources(&res);
    CarregarRanking(); // <-- Carrega o ranking ao abrir o jogo

    Player jogador;
    MapData mapa;
    Projectile projeteis[MAX_PROJETEIS];
    Effect boom[MAX_EXPLOSOES];
    GameScreen telaAtual = SPLASH;
    
    // Variáveis para Digitar o Nome (Input)
    char nomeInput[20] = "JOGADOR";
    int letrasCount = 0;

    //verificador de fase
    int nivelAtual = 1;

    InicializarProjeteis(projeteis);
    InicializarExplosoes(boom);
    InicializarPlayer(&jogador);
    CarregarMapa(&mapa, 1);

    while (!WindowShouldClose()) {
        
        switch (telaAtual) {
            case SPLASH:
                if (IsKeyPressed(KEY_ENTER)) telaAtual = MENU;
                break;
            
            case MENU:
                if (IsKeyPressed(KEY_ENTER)) {
                    nivelAtual = 1;
                    InicializarPlayer(&jogador);
                    InicializarProjeteis(projeteis);
                    CarregarMapa(&mapa, 1);
                    telaAtual = GAMEPLAY;
                }
                if (IsKeyPressed(KEY_R)) telaAtual = RANKING;
                break;

            case GAMEPLAY:
                // pause verificado primeiro, mas nao eh tao relevante
                if (IsKeyPressed(KEY_P)) { 
                    telaAtual = PAUSED;
                }
                // Atualiza Jogador e retorna se chegou no fim
                bool ChegouNoFim = UpdatePlayer(&jogador);
                
                // 2. Atualiza Projéteis, Explosões e Colisões
                if (IsKeyPressed(KEY_SPACE) && jogador.cooldown == 0) {
                    Atirar(projeteis, jogador, res.sfxTiro);
                    jogador.cooldown = 30;
                }
                UpdateProjeteis(projeteis);
                UpdateExplosoes(boom); // (Se já tiveres implementado as explosões)
                
                // Passa as explosões e sons novos para as colisões
                VerificarColisaoTiros(projeteis, &mapa, &jogador, res.sfxExplosao, boom);
                VerificarColisoes(&jogador, &mapa, res.sfxExplosao);
                
                // Pontuação extra por ir mais rapido
                jogador.score += (int)(jogador.speed / 1.0f) - 1;

                if (jogador.score >= jogador.proximaVida) {
                    jogador.vidas++;             // Ganha a vida
                    jogador.proximaVida += 1000; // Define a próxima meta (2000, 3000, etc.)
                }
                // BLOCO A: VITÓRIA (Mudança de Fase)
                if (ChegouNoFim) {
                    jogador.score += 1000; // Prémio por passar de fase
                    nivelAtual++;          // Sobe o nível
                    
                    // Tenta carregar o próximo mapa
                    if (CarregarMapa(&mapa, nivelAtual) == 0) {
                        // Se não existir (ex: Fase 6), volta para a 1 (Loop infinito)
                        nivelAtual = 1;
                        CarregarMapa(&mapa, nivelAtual);
                    }

                    // RESETA POSIÇÃO (Para o início do novo mapa)
                    jogador.y = 2800; 
                    jogador.combustivel = 100.0f;
                    
                    // Limpa os tiros e explosões da fase anterior para não bugar
                    InicializarProjeteis(projeteis);
                    InicializarExplosoes(boom);
                }

                // BLOCO B: DERROTA (Morte)
                // Só entra aqui se as vidas forem ZERO. Não tem relação com chegar ao fim.
                if (jogador.vidas <= 0) {
                    
                    if (VerificarRecorde(jogador.score)) {
                        telaAtual = NEW_RECORD;
                        memset(nomeInput, 0, 20);
                        letrasCount = 0;
                    } else {
                        PlaySound(res.sfxGameOver);
                        telaAtual = GAMEOVER;
                    }
                }
                break;

            case PAUSED:
                // na logica o jogo nao mexe em nada, mas continuara desenhando
                if (IsKeyPressed(KEY_P)) {
                    telaAtual = GAMEPLAY; // Volta a jogar
                }
                // pode voltar ao menu
                if (IsKeyPressed(KEY_M)) {
                    telaAtual = MENU;
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
                DrawTextCentered("Aviãozinho do Tráfico", 200, 50, YELLOW);
                DrawTextCentered("[Enter] Jogar", 400, 30, YELLOW);
                DrawTextCentered("[R] Ranking", 500, 30, YELLOW);
                DrawTextCentered("[Esc] Sair", 600, 30, YELLOW);
                break;

            case GAMEPLAY:
                UpdatePlayer(&jogador);
                VerificarColisoes(&jogador, &mapa, res.sfxExplosao);
                // ... logica score ...

                BeginDrawing();
                ClearBackground(DARKBLUE);


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

                // --- DESENHAR EXPLOSÕES ---
                for(int i=0; i<MAX_EXPLOSOES; i++) {
                    if (boom[i].ativa) {
                        // Desenha na posição X, Y corrigida pela câmera
                        DrawTexture(res.boom, boom[i].x, boom[i].y - cameraY, WHITE);
                    }
                }
                
                if (IsKeyDown(KEY_LEFT)) DrawTexture(res.playerE, jogador.x, jogador.y - cameraY, WHITE);
                else if (IsKeyDown(KEY_RIGHT)) DrawTexture(res.playerD, jogador.x, jogador.y - cameraY, WHITE);
                else DrawTexture(res.player, jogador.x, jogador.y - cameraY, WHITE);
                
                // ... HUD ...
                DrawText(TextFormat("SCORE: %05d", jogador.score), 700, 10, 20, WHITE);
                DrawText(TextFormat("VIDAS: %d", jogador.vidas), 200, 10, 20, GREEN);

                // --- BARRA DE COMBUSTÍVEL ---
                DrawRectangle(400, 10, 200, 20, DARKGRAY);
                
                // Cor muda conforme o nível (Verde > Amarelo > Vermelho)
                Color corCombustivel = GREEN;
                if (jogador.combustivel < 50) corCombustivel = YELLOW;
                if (jogador.combustivel < 25) corCombustivel = RED;

                // Barra atual (Largura = valor do combustivel * 2, pois o max é 100 e a barra tem 200px)
                DrawRectangle(400, 10, (int)(jogador.combustivel * 2), 20, corCombustivel);
                
                // Contorno 
                DrawRectangleLines(400, 10, 200, 20, WHITE);
                DrawText("FUEL", 320, 10, 20, WHITE);
                break;
                
            case PAUSED:
            // quase mesma coisa do gameplay, mas sem atualizar nada
            // e travando a camera
                int camY = (int)jogador.y - 600;
                
                DesenharMapa(&mapa, &res, jogador.y);
                
                // Desenha Jogador (Parado)
                if (IsKeyDown(KEY_LEFT)) DrawTexture(res.playerE, jogador.x, jogador.y - camY, WHITE);
                else if (IsKeyDown(KEY_RIGHT)) DrawTexture(res.playerD, jogador.x, jogador.y - camY, WHITE);
                else DrawTexture(res.player, jogador.x, jogador.y - camY, WHITE);

                DrawProjeteis(projeteis, camY);
                // (Se tiver explosões, desenha aqui também)

                // HUD (Vidas e Score)
                DrawText(TextFormat("SCORE: %05d", jogador.score), 700, 10, 20, WHITE);
                DrawText(TextFormat("VIDAS: %d", jogador.vidas), 200, 10, 20, GREEN);
                
                // BARRA DE COMBUSTIVEL (Cópia visual simples)
                DrawRectangle(400, 10, 200, 20, DARKGRAY);
                DrawRectangle(400, 10, (int)(jogador.combustivel * 2), 20, GREEN);
                DrawRectangleLines(400, 10, 200, 20, WHITE);
                DrawText("FUEL", 320, 10, 20, WHITE);

                // 2. A MÁGICA: O FILTRO ESCURO E O TEXTO
                // Desenha um retângulo preto semitransparente sobre a tela toda
                DrawRectangle(0, 0, SCREEN_W, SCREEN_H, Fade(BLACK, 0.5f));

                DrawText("PAUSADO", 350, 300, 50, WHITE);
                DrawText("Pressione [P] para voltar", 330, 380, 20, LIGHTGRAY);
                DrawText("Pressione [M] para Menu", 340, 410, 20, LIGHTGRAY);
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
    CloseAudioDevice();
    CloseWindow();
    return 0;
}