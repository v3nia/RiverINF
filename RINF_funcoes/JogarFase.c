#include "JogarFase.h"
#include "Projetil.h" 
#include "Inimigo.h" 
#include <stdio.h>
#include <string.h>

void VerificarColisoes(Player *p, Projetil tiros[], Inimigo inimigos[], bool *faseConcluida)
{

    Rectangle recPlayer = {p->x, p->y, (float)p->width, (float)p->height};

    for (int i = 0; i < MAX_INIMIGOS; i++)
    {
        if (!inimigos[i].ativo) continue;

        Rectangle recInimigo = {inimigos[i].x, inimigos[i].y, inimigos[i].width, inimigos[i].height};

        //  PLAYER x OBJETOS
        if (CheckCollisionRecs(recPlayer, recInimigo))
        {

            if (inimigos[i].tipo == COMBUSTIVEL)
            {

                p->fuel += 0.8f;
                if (p->fuel > 100.0f) p->fuel = 100.0f;
            }
            else if (inimigos[i].tipo != NADA)
            {

                p->lifes--;


                p->x = 480 - (p->width/2);
                p->y = 700;
                p->fuel = 100.0f;
            }
        }

        // TIRO x OBJETOS
        for (int t = 0; t < MAX_TIROS; t++)
        {
            if (!tiros[t].ativo) continue;

            Rectangle recTiro = {tiros[t].x, tiros[t].y, (float)tiros[t].radius, (float)tiros[t].radius*2};

            if (CheckCollisionRecs(recTiro, recInimigo))
            {


                if (inimigos[i].tipo == NADA) continue;

                tiros[t].ativo = false;

                if (inimigos[i].tipo == TERRA)
                {
                    continue;
                }
                else if (inimigos[i].tipo == COMBUSTIVEL)
                {

                    inimigos[i].ativo = false;
                    p->score -= 10;
                }
                else
                {

                    inimigos[i].ativo = false;


                    if (inimigos[i].tipo == NAVIO) p->score += 30;
                    if (inimigos[i].tipo == HELICOPTERO) p->score += 60;

                    if (inimigos[i].tipo == PONTE)
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

    
    Inimigo inimigos[MAX_INIMIGOS];
    CarregarInimigos(inimigos, MAPA); 
    

    
    jogador->x = 480 - (jogador->width/2);
    jogador->y = 720;

    bool faseConcluida = false;
    bool gameOver = false;
    bool sair = false;

    while (!WindowShouldClose() && !faseConcluida && !gameOver && !sair) {

        UpdatePlayer(jogador);
            if (IsKeyDown(KEY_SPACE) || IsKeyDown(KEY_K)) {
                if (PodeAtirar(jogador)) {
                    Atirar(tiros, jogador);
                }
        }

        UpdateProjeteis(tiros);

        jogador->fuel -= 0.05f;

        if (jogador->fuel <= 0)
        {
            // Pane seca
            jogador->fuel = 0;
            jogador->lifes--;


            jogador->fuel = 100.0f;
            jogador->x = 480 - (jogador->width/2);
            jogador->y = 700;
        }


        VerificarColisoes(jogador, tiros, inimigos, &faseConcluida);

        if (IsKeyPressed(KEY_ESCAPE)) sair = true;
        if (jogador->lifes <= 0) gameOver = true;

        // Cheats e Saída
        if (IsKeyPressed(KEY_ENTER)) faseConcluida = true; // Cheat de passar fase
        if (IsKeyPressed(KEY_ESCAPE)) sair = true;
        if (jogador->lifes <= 0) gameOver = true;

        
        BeginDrawing();
            // Fundo Azul (Agua)
            ClearBackground(BLUE); 
            
            // Desenha o Mapa (Terra, Inimigos, Pontes)
            DrawInimigos(inimigos);

            // Entidade
            DrawPlayer(jogador);       
            DrawProjeteis(tiros);
            
            // HUD
            DrawRectangle(0, 0, 960, 40, DARKGRAY); 
            DrawText(TextFormat("FASE: %d", nivel), 20, 10, 20, WHITE);
            DrawText(TextFormat("VIDAS: %d", jogador->lifes), 200, 10, 20, RED);

            Color corFuel = YELLOW;
            if (jogador->fuel < 30) corFuel = RED;
            DrawText(TextFormat("COMB: %.0f", jogador->fuel), 400, 10, 20, corFuel);

            DrawText(TextFormat("SCORE: %d", jogador->score), 700, 10, 20, WHITE);

            if (gameOver) DrawText("GAME OVER", 350, 400, 50, RED);

            EndDrawing();
        
    }
    if (faseConcluida) return 1;
    return 0;
}