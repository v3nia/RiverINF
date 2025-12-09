#include "Player.h"

void Reinicia_player(Player *p) {
    p->x = 480.0f;
    p->y = 700.0f;
    p->deslocamento = 5.0f;
    p->speed = 1.0f;    
    p->lifes = 3;
    p->score = 0;
    p->fuel = 100.0f;
    // tamanho do retângulo
    p->width = 40; 
    p->height = 40;

    p->textura = LoadTexture("Sprites/Player.png");
    p->texturaD = LoadTexture("Sprites/PlayerD.png");
    p->texturaE = LoadTexture("Sprites/PlayerE.png");

    p->ultimoDisparo = 0.0;
    p->cadencia = 0.3f; 
}

void UpdatePlayer(Player *p) {
    if (IsKeyDown(KEY_RIGHT)) {p->x += p->deslocamento;}
    if (IsKeyDown(KEY_D)) {p->x += p->deslocamento;}

    
    if (IsKeyDown(KEY_LEFT)) {p->x -= p->deslocamento;}
    if (IsKeyDown(KEY_A)) {p->x -= p->deslocamento;}
    
    if (IsKeyDown(KEY_UP)) p->y -= p->deslocamento;
    if (IsKeyDown(KEY_W)) p->y -= p->deslocamento;
    
    if (IsKeyDown(KEY_DOWN)) p->y += p->deslocamento;
    if (IsKeyDown(KEY_S)) p->y += p->deslocamento;

    p->y -= p->speed; // Movimento automático para a direita
    // Limites da tela e de velocidade
    if (p->x < 0) p->x = 0;
    if (p->x > 960 - p->width) p->x = 960 - p->width;
    if (p->y < 0) p->y = 0;
    if (p->y > 800 - p->height) p->y = 800 - p->height;
}

void DrawPlayer(Player *p) {
    // printf("Desenhando Player...\n"); // <-- Se quiser testar se chega aqui
    DrawRectangle((int)p->x, (int)p->y, p->width, p->height/2, SKYBLUE);
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))
        DrawTexture (p->texturaD, (int)p->x, (int)p->y, WHITE);
    else if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))
        DrawTexture (p->texturaE, (int)p->x, (int)p->y, WHITE);
    else
    DrawTexture (p->textura, (int)p->x, (int)p->y, WHITE);
}

bool PodeAtirar(Player *p) {
    double currentTime = GetTime();
    if (currentTime - p->ultimoDisparo >= p->cadencia) {
        p->ultimoDisparo = currentTime;
        return true;
    }
    return false;
}   