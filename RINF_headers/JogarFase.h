#ifndef JogarFase_h
#define JogarFase_h

#include "raylib.h"
#include "Player.h"
#include <stdio.h>
#include "Projetil.h"

int JogarFase(int nivel, Player *jogador);

void VerificarColisoes(Player *p, Projetil tiros[], Inimigo inimigos[], bool *faseConcluida); 

#endif 
