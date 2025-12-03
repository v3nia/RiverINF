#ifndef menu_h
#define menu_h

// Define os estados (telas) do jogo
typedef enum GameScreen
{
    SPLASH,     // Tela inicial "Pressione Enter" 
    MENU,       // Menu principal com opcoes      
    GAMEPLAY,   // Tela principal do jogo         
    RANKING,    // Tela de highscores             
    END         // Para sair do loop              
} GameScreen;

GameScreen funcmenu(GameScreen currentScreen);


#endif