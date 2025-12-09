#ifndef INIMIGO_H
#define INIMIGO_H

#include "raylib.h"
#include <stdio.h>

#define MAX_INIMIGOS 200 // Limite de objetos (Memoria)

// Tipos de objetos do mapa 
typedef enum TipoInimigo {
    TERRA = 'T',
    NAVIO = 'N',
    HELICOPTERO = 'X',
    COMBUSTIVEL = 'G',
    PONTE = 'P',
    NADA = ' ' // Agua
} TipoInimigo;

typedef struct Inimigo {
    float x;
    float y;
    float width;
    float height;
    bool ativo;
    TipoInimigo tipo;
    Color cor;
} Inimigo;

void InitInimigos(Inimigo inimigos[]);
void CarregarInimigos(Inimigo inimigos[], const char* nomeArquivo);
void DrawInimigos(Inimigo inimigos[]);

#endif