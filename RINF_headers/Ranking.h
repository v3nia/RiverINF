#ifndef RANKING_H
#define RANKING_H

#include "raylib.h"
#include <stdio.h>
#include <string.h>

#define MAX_SCORES 5
#define ARQUIVO_RANKING "ranking.bin"


typedef struct {
    char nome[20];
    int pontos;
} Registro;


void CarregarRanking();
void SalvarRanking();
int  VerificarRecorde(int score); 
void AdicionarScore(const char *nome, int score);
void DesenharTelaRanking();

#endif