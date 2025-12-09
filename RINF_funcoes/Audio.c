#include "Audio.h"
#include <stdio.h>


Sound sndTiro;
Sound sndExplosao;
Sound sndGameOver;

void InitAudio(void)
{
    InitAudioDevice();
}

void CarregarSons(void)
{

    sndTiro = LoadSound("Sons/tiro.wav");
    sndExplosao = LoadSound("Sons/explosao.wav");
    sndGameOver = LoadSound("Sons/gameover.wav");


    SetSoundVolume(sndTiro, 0.5f);
    SetSoundVolume(sndExplosao, 0.8f);
}

void TocarSom(TipoSom som)
{
    switch (som)
    {
    case SOM_TIRO:
        PlaySound(sndTiro);
        break;
    case SOM_EXPLOSAO:
        PlaySound(sndExplosao);
        break;
    case SOM_GAMEOVER:
        PlaySound(sndGameOver);
        break;
    }
}

void DescarregarSons(void)
{
    UnloadSound(sndTiro);
    UnloadSound(sndExplosao);
    UnloadSound(sndGameOver);

    CloseAudioDevice();
}
