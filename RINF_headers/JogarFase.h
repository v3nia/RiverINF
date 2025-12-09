#ifndef JogarFase_h
#define JogarFase_h

#include "raylib.h"
#include "Player.h"

void CarregaMapa(int fase);
int JogarFase(int nivel, Player *jogador);

#endif
void CarregaMapa(FILE*); // Protótipo da função para carregar o mapa do nível

#endif 
