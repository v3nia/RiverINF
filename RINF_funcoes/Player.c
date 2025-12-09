#include "Player.h"



void Reinicia_player(Player *p) {
    p->x = 480.0f;
    p->y = 700.0f;
    p->speed = 5.0f;
    p->lifes = 3;
    p->score = 0;
    // tamanho do retângulo
    p->width = 50; 
    p->height = 50;
}

void UpdatePlayer(Player *p) {
    if (IsKeyDown(KEY_RIGHT)) p->x += p->speed;
    if (IsKeyDown(KEY_LEFT)) p->x -= p->speed;
    if (IsKeyDown(KEY_UP)) p->y -= p->speed;
    if (IsKeyDown(KEY_DOWN)) p->y += p->speed;

    // Limites da tela
    if (p->x < 0) p->x = 0;
    if (p->x > 960 - p->width) p->x = 960 - p->width;
    if (p->y < 0) p->y = 0;
    if (p->y > 800 - p->height) p->y = 800 - p->height;
}

void DrawPlayer(Player *p) {
    // printf("Desenhando Player...\n"); // <-- Se quiser testar se chega aqui
    DrawRectangle((int)p->x, (int)p->y, p->width, p->height, BLUE);
}