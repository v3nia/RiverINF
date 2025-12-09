#ifndef DEFS_H
#define DEFS_H

#include "raylib.h"
#include <stdio.h>
#include <string.h>

// --- CONFIGURAÇÕES ---
#define SCREEN_W 960
#define SCREEN_H 800
#define MAP_ROWS 80
#define MAP_COLS 24
#define TILE_SIZE 40
#define MAX_PROJETEIS 10

// --- VELOCIDADE ---
#define SPEED_MIN 1.0f
#define SPEED_MAX 3.0f
#define ACCEL 0.2f  // O quanto acelera por frame

// --- RANKING CONFIG ---
#define MAX_SCORES 5
#define ARQUIVO_RANKING "ranking.bin"

// --- ESTADOS DO JOGO ---
// Adicionei NEW_RECORD para quando o jogador estiver digitando o nome
typedef enum { SPLASH, MENU, GAMEPLAY, GAMEOVER, NEW_RECORD, RANKING, END } GameScreen;

// --- ESTRUTURAS ---
typedef struct {
    float x, y;
    float width, height;
    float speed;
    bool ativo;
} Projectile;

typedef struct {
    char nome[20];
    int pontos;
} Registro;

typedef struct {
    Texture2D player, playerE, playerD;
    Texture2D terra, navio, heli, ponte;
    Texture2D fuelF, fuelU, fuelE, fuelL;
    Font fonte; 
} Resources;

typedef struct {
    float x, y;
    float width, height;
    float speed;
    int vidas;
    float combustivel;
    int score;
    bool ativo;
    int cooldown;
} Player;

typedef struct {
    char grid[MAP_ROWS][MAP_COLS]; 
    int nivelAtual;
} MapData;

#endif