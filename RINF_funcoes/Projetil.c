#include "Projetil.h"

void InitProjeteis(Projetil tiros[]) {
    for(int i = 0; i < MAX_TIROS; i++) {
        tiros[i].ativo = false;
        tiros[i].speed = 10.0f; 
        tiros[i].radius = 5;   
        tiros[i].x = 0;
        tiros[i].y = 0;
    }
}

void Atirar(Projetil tiros[], Player *jogador) {
   
    for(int i = 0; i < MAX_TIROS; i++) {
        if (!tiros[i].ativo) {
            tiros[i].ativo = true;
            
            tiros[i].x = jogador->x + (jogador->width / 2) - (tiros[i].radius / 2);
            tiros[i].y = jogador->y; 
            break; 
        }
    }
}

void UpdateProjeteis(Projetil tiros[]) {
    for(int i = 0; i < MAX_TIROS; i++) {
        if (tiros[i].ativo) {
            tiros[i].y -= tiros[i].speed; 

            
            if (tiros[i].y < 0) {
                tiros[i].ativo = false;
            }
        }
    }
}

void DrawProjeteis(Projetil tiros[]) {
    for(int i = 0; i < MAX_TIROS; i++) {
        if (tiros[i].ativo) {
            
            DrawRectangle(tiros[i].x, tiros[i].y, tiros[i].radius, tiros[i].radius * 2, YELLOW);
        }
    }
}