#ifndef AUDIO_H
#define AUDIO_H

#include "raylib.h"


typedef enum TipoSom {
    SOM_TIRO,
    SOM_EXPLOSAO,
    SOM_GAMEOVER
} TipoSom;


void InitAudio(void);      
void CarregarSons(void);    
void TocarSom(TipoSom som); 
void DescarregarSons(void);

#endif