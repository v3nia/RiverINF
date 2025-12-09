#include "JogarFase.h"
#include "Projetil.h" 
#include <stdio.h>
#include <string.h>

int JogarFase(int nivel, Player *jogador) {

        FILE *arquivoMapa;
    char MAPA[] = "RINF_mapas/Fase 1.txt";

    //define qual fase vai ser carregada
    switch (nivel) {
        case 1:
            strcpy(MAPA, "RINF_mapas/Fase 1.txt");
            break;
        case 2:
            strcpy(MAPA, "RINF_mapas/Fase 2.txt");
            break;
        case 3:
            strcpy(MAPA, "RINF_mapas/Fase 3.txt");
            break;
        case 4:
            strcpy(MAPA, "RINF_mapas/Fase 4.txt");
            break;
        case 5:
            strcpy(MAPA, "RINF_mapas/Fase 5.txt");
            break;
    }

    
   
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
            ClearBackground(DARKBLUE);
            
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