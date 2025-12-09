#include "raylib.h"
#include "menu.h"
#include "JogarFase.h"
#include "Player.h"
#include "Ranking.h"
#include "Mapa.h"
#include "Audio.h"
#include <stdio.h>

int main(void)
{
    const int screenWidth = 960;
    const int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "Aviãozinho do Tráfico");
    SetTargetFPS(60);


    InitAudio();
    CarregarSons();
    CarregarRanking();
    CarregarTexturasMapa();

    GameScreen modo = SPLASH;
    int FaseAtual = 1;

    Player jogador;
    Reinicia_player(&jogador);

    // Passa o &jogador para o funcmenu
    modo = funcmenu(modo, &jogador); 

    while(modo != END && !WindowShouldClose()){
        switch(modo){
            case MENU:
                modo = funcmenu(modo, &jogador);
                break;
            case GAMEPLAY:
                // Se JogarFase retornar 1, passou. Se retornar 0, morreu/saiu
                if (JogarFase(FaseAtual, &jogador) == 1) {
                    FaseAtual++; 
                } else {
                    // Se as vidas acabarem = GAME OVER
                    if (jogador.lifes <= 0) {
                        modo = GAMEOVER;
                    } else {
                        modo = MENU;
                    }
                }
                if (modo != GAMEOVER && modo != MENU) { 
                     
                     modo = funcmenu(modo, &jogador);
                }
            }
            break;

        default:
            modo = funcmenu(modo, &jogador);
            break;
        }
    }


    DescarregarTexturasMapa();
    DescarregarSons();
    CloseWindow();

    return 0;
}
