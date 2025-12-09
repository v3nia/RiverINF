#include "JogarFase.h"
#include "Projetil.h" 
#include "Inimigo.h" 
#include <stdio.h>
#include <string.h>

int JogarFase(int nivel, Player *jogador) {

    char MAPA[50]; 

    // Seleciona o arquivo
    switch (nivel) {
        case 1: strcpy(MAPA, "RINF_mapas/Fase 1.txt"); break;
        case 2: strcpy(MAPA, "RINF_mapas/Fase 2.txt"); break;
        default: strcpy(MAPA, "RINF_mapas/Fase 1.txt"); break;
    }

   
    Projetil tiros[MAX_TIROS];
    InitProjeteis(tiros);

    
    Inimigo inimigos[MAX_INIMIGOS];
    CarregarInimigos(inimigos, MAPA); 
    

    
    jogador->x = 480 - (jogador->width/2);
    jogador->y = 720;

    bool faseConcluida = false;
    bool gameOver = false;
    bool sair = false;

    while (!WindowShouldClose() && !faseConcluida && !gameOver && !sair) {
        
    
        UpdatePlayer(jogador);
        
        // Tiro com Espaço ou K
        if (IsKeyDown(KEY_SPACE) || IsKeyDown(KEY_K)) {
            if (PodeAtirar(jogador)) {
                Atirar(tiros, jogador);
            }
        }
        UpdateProjeteis(tiros); 

        // Cheats e Saída
        if (IsKeyPressed(KEY_ENTER)) faseConcluida = true; // Cheat de passar fase
        if (IsKeyPressed(KEY_ESCAPE)) sair = true;
        if (jogador->lifes <= 0) gameOver = true;

        
        BeginDrawing();
            // Fundo Azul (Agua)
            ClearBackground(BLUE); 
            
            // Desenha o Mapa (Terra, Inimigos, Pontes)
            DrawInimigos(inimigos);

            // Entidade
            DrawPlayer(jogador);       
            DrawProjeteis(tiros);
            
            // HUD
            DrawRectangle(0, 0, 960, 40, DARKGRAY); 
            DrawText(TextFormat("FASE: %d", nivel), 20, 10, 20, WHITE);
            DrawText(TextFormat("VIDAS: %d", jogador->lifes), 200, 10, 20, RED);
            DrawText(TextFormat("COMB: %.0f", jogador->fuel), 400, 10, 20, YELLOW);
            DrawText(TextFormat("SCORE: %d", jogador->score), 700, 10, 20, WHITE);

            if (gameOver) DrawText("GAME OVER", 350, 400, 50, RED);

        EndDrawing();
    }

    if (faseConcluida) return 1;
    return 0;
}