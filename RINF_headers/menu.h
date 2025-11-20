#ifndef menu_h
#define menu_h

// Define os estados (telas) do jogo
typedef enum GameScreen
{
    SPLASH,     // Tela inicial "Pressione Enter" | = 0
    MENU,       // Menu principal com opcoes      | = 1
    GAMEPLAY,   // Tela principal do jogo         | = 2
    RANKING,    // Tela de highscores             | = 3   
    END         // Para sair do loop              | = 4
} GameScreen;

GameScreen funcmenu(void);


#endif // menu.h