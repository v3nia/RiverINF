#include "raylib.h"
#include "JogarFase.h"
#include <stdbool.h>

// tipo int para retornar a pontuação obtida da fase na main
int JogarFase(int nivel){
   
    int pontuação = 0;
    bool pausa = false;
    bool FaseCompleta = false;

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
        ClearBackground(RAYWHITE);

        CarregaMapa();

        if (pausa == true) {
                // escurece levemente a tela para dar um efeito legalzinho
                DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, 0.5f));
                DrawText("JOGO PAUSADO", 350, 200, 40, YELLOW);
                DrawText("Pressione P para continuar", 280, 250, 20, LIGHTGRAY);
            }
        else{
            // Desenhar elementos do jogo aqui
        }
    }



    return pontuação; 
}