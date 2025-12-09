#include "definicoes.h"

void LoadResources(Resources *res) {
    // Carrega todas as imagens UMA VEZ aqui
    res->player  = LoadTexture("Sprites/Player.png");
    res->playerE = LoadTexture("Sprites/PlayerE.png");
    res->playerD = LoadTexture("Sprites/PlayerD.png");
    
    // Mapa
    res->terra = LoadTexture("Sprites/T.png");
    res->navio = LoadTexture("Sprites/N.png");
    res->heli  = LoadTexture("Sprites/x.png");
    res->ponte = LoadTexture("Sprites/P.png");
    
    // Combustíveis
    res->fuelF = LoadTexture("Sprites/F.png");
    res->fuelU = LoadTexture("Sprites/U.png");
    res->fuelE = LoadTexture("Sprites/E.png");
    res->fuelL = LoadTexture("Sprites/L.png");
}

void UnloadResources(Resources *res) {
    // Limpa da memória VRAM
    UnloadTexture(res->player);
    UnloadTexture(res->playerE);
    UnloadTexture(res->playerD);
    UnloadTexture(res->terra);
    UnloadTexture(res->navio);
    UnloadTexture(res->heli);
    UnloadTexture(res->ponte);
    UnloadTexture(res->fuelF);
    UnloadTexture(res->fuelU);
    UnloadTexture(res->fuelE);
    UnloadTexture(res->fuelL);
}