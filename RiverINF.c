#include "raylib.h"
#include <string.h>
#include <stdbool.h>
#include "menu.h"
#include "JogarFase.h"
#include "Player.h"

int main(void){
    
    GameScreen modo;
    int FaseAtual = 1;
    Player jogador;
    Reinicia_player();

    // --- Inicializacao ---
    const int screenWidth = 960;
    const int screenHeight = 800;

    // Nome trocado na barra de titulo da janela
    InitWindow(screenWidth, screenHeight, "Aviãozinho do Tráfico");
    SetTargetFPS(60);

    modo = funcmenu(SPLASH);

    // --- Loop Principal do Jogo ---
    while(modo != END && WindowShouldClose() == false){
        switch(modo){
            case GAMEPLAY:
                JogarFase(FaseAtual);
                modo = funcmenu(MENU);
                break;
            case RANKING:
                modo = funcmenu(MENU);
                break;
            default:
                modo = funcmenu(modo);
                break;
        }
    }

    return 0;
}

/* adicionar as funcoes:
CarregaMapa
Texturas (so definicoes)

Loop principal reinicia a cada fase*/