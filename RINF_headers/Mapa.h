#ifndef MAPA_H
#define MAPA_H

#include "raylib.h"
#include <stdio.h>

typedef struct {
    Texture2D Terra;
    Texture2D Navio;
    Texture2D Helicoptero;
    Texture2D CombustivelF;
    Texture2D CombustivelU;
    Texture2D CombustivelE;
    Texture2D CombustivelL;
    Texture2D Ponte;
} TexturasMapa;

void CarregaMapa(FILE *arquivo, Rectangle* Combustivel[], Rectangle* Obstaculo[]); 

void DesenhaMapa(FILE *arquivo, TexturasMapa texturas);

typedef struct Obstaculo
{
    float x;
    float y;
    float width;
    float height;
    bool ativo;
    TipoObstaculo tipo;
} Obstaculo;



void InitObstaculos(Obstaculo obstaculos[]);
void CarregarObstaculos(Obstaculo obstaculos[], const char* nomeArquivo);


void CarregarTexturasMapa(void);
void DescarregarTexturasMapa(void);


void DrawMapa(Obstaculo obstaculos[]);

#endif
