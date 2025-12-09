#include "JogarFase.h"
#include "Projetil.h"
#include "Mapa.h"
#include "Audio.h"
#include <stdio.h>
#include <string.h>

void VerificarColisoes(Player *p, Projetil tiros[], Obstaculo obstaculos[], bool *faseConcluida)
{
    Rectangle recPlayer = {p->x, p->y, (float)p->width, (float)p->height};

    for (int i = 0; i < MAX_OBSTACULOS; i++)
    {
        if (!obstaculos[i].ativo) continue;

        Rectangle recObstaculo = {obstaculos[i].x, obstaculos[i].y, obstaculos[i].width, obstaculos[i].height};

        bool isFuel = (obstaculos[i].tipo == FUEL_F || obstaculos[i].tipo == FUEL_U ||
                       obstaculos[i].tipo == FUEL_E || obstaculos[i].tipo == FUEL_L);

        if (CheckCollisionRecs(recPlayer, recObstaculo))
        {
            if (isFuel)
            {
                p->fuel += 0.8f;
                if (p->fuel > 100.0f) p->fuel = 100.0f;
            }
            else if (obstaculos[i].tipo != NADA)
            {
                if (p->superAviao == false)
                {
                    p->lifes--;
                    TocarSom(SOM_EXPLOSAO);

                    p->x = 480 - (p->width/2);
                    p->y = 700;
                    p->fuel = 100.0f;
                }
            }
        }

        for (int t = 0; t < MAX_TIROS; t++)
        {
            if (!tiros[t].ativo) continue;

            Rectangle recTiro = {tiros[t].x, tiros[t].y, (float)tiros[t].radius, (float)tiros[t].radius*2};

            if (CheckCollisionRecs(recTiro, recObstaculo))
            {
                if (obstaculos[i].tipo == NADA) continue;

                tiros[t].ativo = false;

                if (obstaculos[i].tipo == TERRA)
                {
                    continue;
                }
                else if (isFuel)
                {
                    obstaculos[i].ativo = false;
                    TocarSom(SOM_EXPLOSAO);
                    p->score -= 10;
                }
                else
                {
                    obstaculos[i].ativo = false;
                    TocarSom(SOM_EXPLOSAO);

                    if (obstaculos[i].tipo == NAVIO) p->score += 30;
                    if (obstaculos[i].tipo == HELICOPTERO) p->score += 60;
                    if (obstaculos[i].tipo == PONTE)
                    {
                        p->score += 200;
                        *faseConcluida = true;
                    }
                }
            }
        }
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

    Projetil tiros[MAX_TIROS];
    InitProjeteis(tiros);

    Obstaculo obstaculos[MAX_OBSTACULOS];
    CarregarObstaculos(obstaculos, MAPA);

    jogador->x = 480 - (jogador->width/2);
    jogador->y = 700;
    jogador->fuel = 100.0f;

    bool faseConcluida = false;
    bool gameOver = false;
    bool sair = false;

    while (!WindowShouldClose() && !faseConcluida && !gameOver && !sair)
    {

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
                TocarSom(SOM_EXPLOSAO);

                jogador->fuel = 100.0f;
                jogador->x = 480 - (jogador->width/2);
                jogador->y = 700;
            }
        }

        VerificarColisoes(jogador, tiros, obstaculos, &faseConcluida);

        if (IsKeyPressed(KEY_ESCAPE)) sair = true;
        if (jogador->lifes <= 0) gameOver = true;

        BeginDrawing();
        ClearBackground(BLUE);

        DrawMapa(obstaculos);

        DrawPlayer(jogador);

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
