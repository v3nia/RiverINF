#ifndef Player_H
#define Player_H

#include "raylib.h"
#include <stdbool.h> 

typedef struct Player {

    float x;
    float y;
    float deslocamento;
    float speed;
    int lifes;
    int score;
    float fuel;
    int width;
    int height;
    bool superAviao;    
    bool nitrado;

    Texture2D textura; 
    Texture2D texturaD; 
    Texture2D texturaE; 

    double ultimoDisparo; // Guarda o momento exato do ultimo tiro
    float cadencia;       // Tempo de espera entre tiros 

} Player;


void Reinicia_player(Player *p);
void UpdatePlayer(Player *p);
void DrawPlayer(Player *p);
bool PodeAtirar(Player *p); 



#endif