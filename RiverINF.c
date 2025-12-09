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

    while(modo != END && !WindowShouldClose())
    {
        switch(modo)
        {
        case GAMEPLAY:

            if (jogador.lifes <= 0)
            {
                Reinicia_player(&jogador);
                FaseAtual = 1;
            }

            int resultado = JogarFase(FaseAtual, &jogador);

            if (resultado == 1)
            {
                FaseAtual++;
            }
            else
            {
                if (jogador.lifes <= 0)
                {
                    modo = GAMEOVER;
                }
                else
                {
                    modo = MENU;
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
