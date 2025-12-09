#ifndef MAPA_H
#define MAPA_H

#include "raylib.h"
#include <stdio.h>

#define MAX_OBSTACULOS 500


typedef enum TipoObstaculo
{
    TERRA = 'T',
    NAVIO = 'N',
    HELICOPTERO = 'X',
    PONTE = 'P',
    FUEL_F = 'F',
    FUEL_U = 'U',
    FUEL_E = 'E',
    FUEL_L = 'L',
    NADA = ' '
} TipoObstaculo;

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
