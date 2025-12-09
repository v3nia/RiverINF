#ifndef INIMIGO_H
#define INIMIGO_H

#include "raylib.h"
#include <stdio.h>

void CarregaMapa(FILE *arquivo, Rectangle* Combustivel[], Rectangle* Obstaculo[]); 

void DesenhaMapa(FILE *arquivo);

typedef enum {
    NADA,
    TERRA,
    NAVIO,
    HELICOPTERO,
    FUEL_F,
    FUEL_U,
    FUEL_E,
    FUEL_L,
    PONTE
} TipoObstaculo;

#endif