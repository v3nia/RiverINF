#ifndef Player_H
#define Player_H

typedef struct Player {
    float x;
    float y;
    float speed;
    int lifes;
    int score;
} Player;

extern Player jogador;

void Reinicia_player();


#endif