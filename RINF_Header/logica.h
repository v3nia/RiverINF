#ifndef LOGICA_H
#define LOGICA_H

int CarregarMapa(MapData *mapa, int nivel);

void DesenharMapa(MapData *mapa, Resources *res, float playerY);

void InicializarPlayer(Player *p);

bool UpdatePlayer(Player *p);

void VerificarColisoes(Player *p, MapData *mapa, Sound somExplosao);

void InicializarProjeteis(Projectile tiros[]);

void Atirar(Projectile tiros[], Player p, Sound somTiro);

void UpdateProjeteis(Projectile tiros[]);

void DrawProjeteis(Projectile tiros[], float cameraY);

void VerificarColisaoTiros(Projectile tiros[], MapData *mapa, Player *p, Sound somExplosao, Effect boom[]);

void InicializarExplosoes(Effect boom[]);

void UpdateExplosoes(Effect boom[]);
    
#endif