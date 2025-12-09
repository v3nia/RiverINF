#ifndef Player_H
#define Player_H

#include "raylib.h"

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
    
    
    double lastShotTime; 
    float fireRate;      
} Player;

void Reinicia_player(Player *p);
void UpdatePlayer(Player *p);
void DrawPlayer(Player *p);
bool PodeAtirar(Player *p); 

#endif