#include "JogarFase.h"
#include "Projetil.h" 
#include <stdio.h>

void CarregaMapa(int nivel) {
    printf("--- Iniciando Fase %d ---\n", nivel);
}
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "Player.h"

// tipo int para retornar a pontuação obtida da fase na main
int JogarFase(int nivel){
   
    int pontuação = 0;
    bool pausa = false;
    bool FaseCompleta = false;
    char MAPA[] = "RINF_mapas/Fase 1.txt";
    FILE *arquivoMapa;

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

    CarregaMapa(arquivoMapa);{
        arquivoMapa = fopen(MAPA, "r");
        if (arquivoMapa == NULL) {
            printf("Erro ao abrir o arquivo do mapa: %s\n", MAPA);
        }
    }
    
    while(WindowShouldClose() && FaseCompleta == false){

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
        ClearBackground(SKYBLUE);

        if (pausa == true) {
                // escurece levemente a tela para dar um efeito legalzinho
                DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, 0.5f));
                DrawText("JOGO PAUSADO", 350, 200, 40, YELLOW);
                DrawText("Pressione P para continuar", 280, 250, 20, LIGHTGRAY);
            }
        else{
            // Desenhar elementos do jogo aqui
        }

        EndDrawing();
    }
    fclose(arquivoMapa);

    return jogador.score; 
} 
