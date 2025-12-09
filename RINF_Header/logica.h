#ifndef LOGICA_H
#define LOGICA_H

void CarregarMapa(MapData *mapa, int nivel);

void DesenharMapa(MapData *mapa, Resources *res, float playerY);

void InicializarPlayer(Player *p);

bool UpdatePlayer(Player *p);

void VerificarColisoes(Player *p, MapData *mapa);

void InicializarProjeteis(Projectile tiros[]);

void Atirar(Projectile tiros[], Player p);

void UpdateProjeteis(Projectile tiros[]);

void DrawProjeteis(Projectile tiros[], float cameraY);

void VerificarColisaoTiros(Projectile tiros[], MapData *mapa, Player *p);
    
#endif