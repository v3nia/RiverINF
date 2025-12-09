#include "raylib.h"
#include "JogarFase.h"
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

        // logica de pause
        if(IsKeyPressed(KEY_P) || IsKeyPressed(KEY_ENTER)){
            pausa = !pausa; //alterna o estado de pausa
        }

        // o jogo em si, ou seja, só roda quando nao esta pausado
        if(pausa == false){
            
        }

        // a magica acontecendo, vou ver se coloco funcao desenha mapa ou implemento aqui mesmo
        BeginDrawing();
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