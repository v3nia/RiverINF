#include "raylib.h"

// Define os estados (telas) do jogo
typedef enum GameScreen
{
    SPLASH,     // Tela inicial "Pressione Enter"
    MENU,       // Menu principal com opcoes
    GAMEPLAY,   // Tela principal do jogo
    RANKING,    // Tela de highscores
    END         // Para sair do loop
} GameScreen;


int main(void)
{
    // --- Inicializacao ---
    const int screenWidth = 960;
    const int screenHeight = 800;
    // Nome trocado na barra de titulo da janela
    InitWindow(screenWidth, screenHeight, "Aviaozinho do Trafico");

    GameScreen currentScreen = SPLASH;

    // Variaveis de controle do Menu
    int selectedOption = 0;
    const int totalMenuOptions = 4;
    const char *menuOptions[] =
    {
        "Novo jogo",
        "Carregar jogo",
        "Ranking",
        "Sair"
    };

    SetTargetFPS(60);

    // --- Loop Principal do Jogo ---
    while (currentScreen != END && !WindowShouldClose())
    {
        // --- Atualizacao (Logica e Input) ---
        switch(currentScreen)
        {
        case SPLASH:
        {
            if (IsKeyPressed(KEY_ENTER))
            {
                currentScreen = MENU;
            }
        }
        break;

        case MENU:
        {
            // Navegacao no Menu
            if (IsKeyPressed(KEY_DOWN))
            {
                selectedOption = (selectedOption + 1) % totalMenuOptions; // Circula para baixo
            }
            if (IsKeyPressed(KEY_UP))
            {
                selectedOption = (selectedOption - 1 + totalMenuOptions) % totalMenuOptions; // Circula para cima
            }

            // Selecao no Menu
            if (IsKeyPressed(KEY_ENTER))
            {
                switch(selectedOption)
                {
                case 0:
                    currentScreen = GAMEPLAY;
                    break; // "Novo jogo"
                case 1: /* Logica de "Carregar Jogo" (Opcional) */
                    break;
                case 2:
                    currentScreen = RANKING;
                    break;  // "Ranking"
                case 3:
                    currentScreen = END;
                    break;      // "Sair"
                }
            }
        }
        break;

        case GAMEPLAY:
        {
            // --- AQUI ENTRA A LOGICA DO JOGO ---

            // Placeholder: ESC volta ao menu (para teste)
            if (IsKeyPressed(KEY_ESCAPE))
            {
                currentScreen = MENU;
            }
        }
        break;

        case RANKING:
        {
            // --- AQUI ENTRA A LOGICA DO RANKING ---

            // Placeholder: ESC volta ao menu
            if (IsKeyPressed(KEY_ESCAPE))
            {
                currentScreen = MENU;
            }
        }
        break;

        case END:
            break;
        }

        // --- Desenho (Renderizacao) ---
        BeginDrawing();

        ClearBackground(BLUE); // Fundo padrao

        switch(currentScreen)
        {
        case SPLASH:
        {
            // Nome trocado na tela Splash
            DrawText("Aviaozinho do Trafico",
                     GetScreenWidth()/2 - MeasureText("Aviaozinho do Trafico", 60)/2,
                     GetScreenHeight()/2 - 100, 60, YELLOW);

            DrawText("Pressione Enter para iniciar",
                     GetScreenWidth()/2 - MeasureText("Pressione Enter para iniciar", 30)/2,
                     GetScreenHeight()/2 + 20, 30, WHITE);

        }
        break;

        case MENU:
        {
            // Nome trocado na tela de Menu
            DrawText("Aviaozinho do Trafico", 20, 20, 40, YELLOW);

            // Desenha as opcoes
            for (int i = 0; i < totalMenuOptions; i++)
            {
                // Destaca a opcao selecionada
                Color color = (i == selectedOption) ? YELLOW : WHITE;

                DrawText(menuOptions[i],
                         GetScreenWidth()/2 - MeasureText(menuOptions[i], 30)/2,
                         300 + i * 50, 30, color);
            }

            // Desenha o seletor
            int posX_seletor = GetScreenWidth()/2 - MeasureText("Carregar jogo", 30)/2 - 40;
            DrawRectangle(posX_seletor, 300 + selectedOption * 50, 20, 20, YELLOW);

        }
        break;

        case GAMEPLAY:
        {
            ClearBackground(DARKGRAY); // Fundo do jogo
            DrawText("JOGO EM ANDAMENTO!", 250, 350, 30, WHITE);
            DrawText("Pressione ESC para voltar ao Menu", 260, 400, 20, WHITE);
        }
        break;

        case RANKING:
        {
            ClearBackground(BLACK); // Fundo do ranking
            DrawText("TELA DE RANKING (HIGHSCORES)", 200, 350, 30, GREEN);
            DrawText("Pressione ESC para voltar ao Menu", 260, 400, 20, WHITE);
        }
        break;

        case END:
            break;
        }

        EndDrawing();
    }

    // --- Finalizacao ---
    CloseWindow();

    return 0;
}
