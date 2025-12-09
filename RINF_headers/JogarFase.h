#ifndef JogarFase_h
#define JogarFase_h

#include "raylib.h"
#include "Player.h"
#include <stdio.h>

int JogarFase(int nivel, Player *jogador);

void CarregaMapa(FILE *arquivo); 

#endif 
