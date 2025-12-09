#ifndef MENU_H
#define MENU_H

#include "Player.h" 

typedef enum GameScreen { 
    SPLASH, 
    MENU, 
    GAMEPLAY, 
    GAMEOVER, 
    RANKING, 
    END 
} GameScreen;


GameScreen funcmenu(GameScreen currentScreen, Player *jogador);

#endif