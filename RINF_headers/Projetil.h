#ifndef PROJETIL_H
#define PROJETIL_H

#include "raylib.h"
#include "Player.h" 

#define MAX_TIROS 20 

typedef struct Projetil {
    float x;
    float y;
    float speed;
    bool ativo;  
    int radius;   
} Projetil;


void InitProjeteis(Projetil tiros[]);


void Atirar(Projetil tiros[], Player *jogador);


void UpdateProjeteis(Projetil tiros[]);


void DrawProjeteis(Projetil tiros[]);

#endif