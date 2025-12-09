#include "JogarFase.h"
#include "Projetil.h" 
#include <stdio.h>

void CarregaMapa(int nivel) {
    printf("--- Iniciando Fase %d ---\n", nivel);
}

int JogarFase(int nivel, Player *jogador) {
    
    CarregaMapa(nivel);
    
   
    Projetil tiros[MAX_TIROS];
    InitProjeteis(tiros);
    

    bool faseConcluida = false;
    bool gameOver = false;
    bool sair = false;

    while (!WindowShouldClose() && !faseConcluida && !gameOver && !sair) {
        
       
        UpdatePlayer(jogador);
        
        
        if (IsKeyPressed(KEY_SPACE)) {
            Atirar(tiros, jogador);
        }
        UpdateProjeteis(tiros); 
        

        if (IsKeyPressed(KEY_ENTER)) faseConcluida = true;
        if (IsKeyPressed(KEY_ESCAPE)) sair = true;
        if (jogador->lifes <= 0) gameOver = true;

        
        BeginDrawing();
            ClearBackground(RAYWHITE);
            
            DrawPlayer(jogador);       
            
            
            DrawProjeteis(tiros);
            
            
            DrawText(TextFormat("FASE: %d", nivel), 20, 20, 20, BLACK);
            DrawText(TextFormat("VIDAS: %d", jogador->lifes), 20, 50, 20, RED);

            if (gameOver) DrawText("GAME OVER", 350, 400, 50, RED);

        EndDrawing();
    }

    if (faseConcluida) return 1;
    return 0;
}