#include "raylib.h"
#include "menu.h"

GameScreen funcmenu(void)
{
    // --- Inicializacao ---
    const int screenWidth = 960;
    const int screenHeight = 800;
    // Nome trocado na barra de titulo da janela
    InitWindow(screenWidth, screenHeight, "Aviãozinho do Tráfico");

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
    while (currentScreen != END)
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
            if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S))
            {
                selectedOption = (selectedOption + 1) % totalMenuOptions; // Circula para baixo
            }
            if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W))
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
            return currentScreen; // retorna na main para ser implementado
        }
        break;

        case RANKING:
        {
            return currentScreen; // retorna na main para ser implementado
        }
        break;

        case END:
            break;
        }

        // --- Desenho (Renderizacao) ---
        BeginDrawing();

        ClearBackground(BLUE); // Fundo padrao

        if(currentScreen == SPLASH){
            // Nome trocado na tela Splash
            DrawText("Aviãozinho do Tráfico",
                     GetScreenWidth()/2 - MeasureText("Aviãozinho do Tráfico", 60)/2,
                     GetScreenHeight()/2 - 100, 60, YELLOW);

            DrawText("Pressione Enter para iniciar",
                     GetScreenWidth()/2 - MeasureText("Pressione Enter para iniciar", 30)/2,
                     GetScreenHeight()/2 + 20, 30, WHITE);
        }
        else{
            // Nome trocado na tela de Menu
            DrawText("Aviãozinho do Tráfico", 20, 20, 40, YELLOW);

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
        EndDrawing();
    }

    // --- Finalizacao ---
    CloseWindow();

    return currentScreen;
}
