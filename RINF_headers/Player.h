#ifndef Player_H
#define Player_H

#include "raylib.h"

typedef struct Player {
    float x;
    float y;
    float speed;
    int lifes;
    int score;
    int width;
    int height;
} Player;

void Reinicia_player(Player *p);
void UpdatePlayer(Player *p);
void DrawPlayer(Player *p);

#endif