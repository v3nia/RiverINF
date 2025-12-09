#include "JogarFase.h"
#include "Projetil.h"
#include "Mapa.h"
#include <stdio.h>
#include <string.h>

void VerificarColisoes(Player *p, Projetil tiros[])
{
    Rectangle *Combustivel[300];
    Rectangle *Obstaculo[80*24];   
    
    Rectangle recPlayer = {p->x, p->y, (float)p->width, (float)p->height};
    FILE *arquivo = fopen("RINF_mapas/Fase 1.txt", "r");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo do mapa para colisões!\n");
        return;
    }
    CarregaMapa(arquivo, Combustivel, Obstaculo);
   
    for(int i = 0; i < 80*24; i++){
        if (CheckCollisionRecs(recPlayer, *Obstaculo[i]) == true)
        (p->lifes -= 1);
    }
    for(int i = 0; i < 300; i++){
        if (CheckCollisionRecs(recPlayer, *Combustivel[i]) == true)
        (p->fuel += 1.0f);
    }

}

int JogarFase(int nivel, Player *jogador)
{
    char MAPA[50];

    switch (nivel)
    {
    case 1:
        strcpy(MAPA, "RINF_mapas/Fase 1.txt");
        break;
    case 2:
        strcpy(MAPA, "RINF_mapas/Fase 2.txt");
        break;
    default:
        strcpy(MAPA, "RINF_mapas/Fase 1.txt");
        break;
    }

    TexturasMapa Temas;
    Temas.Terra = LoadTexture("Sprites/T.png");
    Temas.Navio = LoadTexture("Sprites/N.png");
    Temas.Helicoptero = LoadTexture("Sprites/x.png");
    Temas.CombustivelF = LoadTexture("Sprites/F.png");
    Temas.CombustivelU = LoadTexture("Sprites/U.png");
    Temas.CombustivelE = LoadTexture("Sprites/E.png");
    Temas.CombustivelL = LoadTexture("Sprites/L.png");
    Temas.Ponte = LoadTexture("Sprites/P.png");

    Projetil tiros[MAX_TIROS];
    InitProjeteis(tiros);

    jogador->x = 480 - (jogador->width/2);
    jogador->y = 700;
    jogador->fuel = 100.0f;

    bool faseConcluida = false;
    bool gameOver = false;
    bool sair = false;

    while (!WindowShouldClose() && !faseConcluida && !gameOver && !sair)
    {
        FILE *arquivo = fopen(MAPA, "r");   
        UpdatePlayer(jogador);

        if (IsKeyPressed(KEY_I)) jogador->superAviao = !jogador->superAviao;
        if (IsKeyPressed(KEY_F)) jogador->nitrado = !jogador->nitrado;

        if (IsKeyDown(KEY_SPACE) || IsKeyDown(KEY_K))
        {
            if (PodeAtirar(jogador))
            {
                Atirar(tiros, jogador);
                TocarSom(SOM_TIRO);
            }
        }
        UpdateProjeteis(tiros);

        if (jogador->nitrado == false)
        {
            jogador->fuel -= 0.05f;
        }
        else
        {
            jogador->fuel = 100.0f;
        }

        if (jogador->fuel <= 0)
        {
            jogador->fuel = 0;
            if (jogador->superAviao == false)
            {
                jogador->lifes--;
                jogador->fuel = 100.0f;
                jogador->x = 480 - (jogador->width/2);
                jogador->y = 700;
            }
        }

        VerificarColisoes(jogador, tiros);

        if (IsKeyPressed(KEY_ESCAPE)) sair = true;
        if (jogador->lifes <= 0) gameOver = true;

        BeginDrawing();
        ClearBackground(BLUE);
        DesenhaMapa(arquivo, Temas);

        if (jogador->superAviao)
        {
            DrawCircleLines((int)jogador->x + jogador->width/2, (int)jogador->y + jogador->height/2, 40, GOLD);
        }

        DrawProjeteis(tiros);

        DrawRectangle(0, 0, 960, 40, DARKGRAY);
        DrawText(TextFormat("FASE: %d", nivel), 20, 10, 20, WHITE);
        DrawText(TextFormat("VIDAS: %d", jogador->lifes), 200, 10, 20, GREEN);

        Color corFuel = (jogador->fuel < 30) ? RED : YELLOW;
        if (jogador->nitrado) corFuel = SKYBLUE;
        DrawText(TextFormat("COMB: %.0f", jogador->fuel), 400, 10, 20, corFuel);

        DrawText(TextFormat("SCORE: %d", jogador->score), 700, 10, 20, WHITE);

        if (jogador->superAviao)
        {
            DrawText("MODO SUPER AVIAOZINHO", 680, 50, 20, GOLD);
        }
        if (jogador->nitrado)
        {
            DrawText("NITRADO ATIVADO", 750, 70, 20, SKYBLUE);
        }

        if (gameOver) DrawText("GAME OVER", 350, 400, 50, RED);

        EndDrawing();
    }

    if (faseConcluida) return 1;
    return 0;
}
