#ifndef MENU_H
#define MENU_H

#include "Player.h" // Precisamos saber o score do player

typedef enum GameScreen { 
    SPLASH, 
    MENU, 
    GAMEPLAY, 
    GAMEOVER, // <--- Novo estado
    RANKING, 
    END 
} GameScreen;

// Atualizei a função para receber o ponteiro do Player (para ler o score e salvar nome)
GameScreen funcmenu(GameScreen currentScreen, Player *jogador);

#endif