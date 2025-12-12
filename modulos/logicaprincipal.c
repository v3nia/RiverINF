#include "definicoes.h"
#include "logica.h"

// --- MAPA ---

int CarregarMapa(MapData *mapa, int nivel) {
    char caminho[50];
    sprintf(caminho, "Fases/fase %d.txt", nivel);

    FILE *f = fopen(caminho, "r");
    
    if (!f) {
        printf("ERRO: Nao abriu %s. Criando mapa vazio.\n", caminho);
        for(int i=0; i<MAP_ROWS; i++) 
            for(int j=0; j<MAP_COLS; j++) mapa->grid[i][j] = ' '; // Preenche com água para não morrer
        return 0; //deu pau
    }

    // Limpa
    for(int i=0; i<MAP_ROWS; i++) 
        for(int j=0; j<MAP_COLS; j++) mapa->grid[i][j] = ' ';

    char ch;
    for (int row = 0; row < MAP_ROWS; row++) {
        for (int col = 0; col < MAP_COLS; col++) {
            ch = fgetc(f);
            while (ch == '\n' || ch == '\r') ch = fgetc(f);
            if (ch == EOF) break;
            mapa->grid[row][col] = ch;
        }
    }
    fclose(f); 
    return 1; //deu certo
}

// parâmetro "playerY" para fazer a câmera seguir o jogador
void DesenharMapa(MapData *mapa, Resources *res, float playerY) {
    
    // Calcula a câmera
    int cameraY = (int)playerY - 600; 

    for (int row = 0; row < MAP_ROWS; row++) {
        for (int col = 0; col < MAP_COLS; col++) {
            
            char tile = mapa->grid[row][col];

            int screenX = col * TILE_SIZE;
            int screenY = (row * TILE_SIZE) - cameraY;

            // Só desenha o que está na tela
            if (screenY < -TILE_SIZE || screenY > SCREEN_H) continue;

            // --- LÓGICA DE ESCALA ---
            
            // 1. Destino: Onde vai aparecer na tela e qual tamanho (40x40)
            // Para a TERRA, +1 pixel no tamanho para garantir que não haja linhas pretas entre os blocos
            Rectangle destRectTerra = {screenX, screenY, TILE_SIZE + 1, TILE_SIZE + 1};
            
            // Para os OBJETOS, 40x40 normal
            Rectangle destRectObj = {screenX, screenY, TILE_SIZE, TILE_SIZE};
            
            Vector2 origin = {0, 0}; // Ponto pivô (canto superior esquerdo)

            switch (tile) {
                // --- ÁGUA ---
                case ' ': 
                {
                    Rectangle source = {0, 0, res->agua.width, res->agua.height};
                    DrawTexturePro(res->agua, source, destRectTerra, origin, 0.0f, WHITE);
                } break;
                // --- TERRA (Estica para preencher lacunas) ---
                case 'T': 
                {
                    Rectangle source = {0, 0, res->terra.width, res->terra.height};
                    DrawTexturePro(res->terra, source, destRectTerra, origin, 0.0f, WHITE);
                } break;

                // --- NAVIO (Ajusta para caber no quadrado) ---
                case 'N': 
                {
                    Rectangle source = {0, 0, res->navio.width, res->navio.height};
                    DrawTexturePro(res->agua, source, destRectTerra, origin, 0.0f, WHITE);
                    DrawTexturePro(res->navio, source, destRectObj, origin, 0.0f, WHITE);
                } break;

                // --- HELICÓPTERO (Já ajustado) ---
                case 'X': 
                {
                    Rectangle source = {0, 0, res->heli.width, res->heli.height};
                    DrawTexturePro(res->agua, source, destRectTerra, origin, 0.0f, WHITE);
                    DrawTexturePro(res->heli, source, destRectObj, origin, 0.0f, WHITE);
                } break;
                
                // --- PONTE ---
                case 'P': 
                {
                    Rectangle source = {0, 0, res->ponte.width, res->ponte.height};
                    DrawTexturePro(res->agua, source, destRectTerra, origin, 0.0f, WHITE);
                    DrawTexturePro(res->ponte, source, destRectObj, origin, 0.0f, WHITE);
                } break;

                // --- COMBUSTÍVEIS ---
                case 'F': DrawTexturePro(res->fuelF, (Rectangle){0,0,res->fuelF.width,res->fuelF.height}, destRectObj, origin, 0, WHITE); break;
                case 'U': DrawTexturePro(res->fuelU, (Rectangle){0,0,res->fuelU.width,res->fuelU.height}, destRectObj, origin, 0, WHITE); break;
                case 'E': DrawTexturePro(res->fuelE, (Rectangle){0,0,res->fuelE.width,res->fuelE.height}, destRectObj, origin, 0, WHITE); break;
                case 'L': DrawTexturePro(res->fuelL, (Rectangle){0,0,res->fuelL.width,res->fuelL.height}, destRectObj, origin, 0, WHITE); break;
            }
        }
    }
}

// --- JOGADOR ---

void InicializarPlayer(Player *p) {
    p->x = 400; // Posição segura X (meio)
    p->y = 2800; // Começa lá embaixo no mapa (Linha 70 * 40 = 2800)
    p->width = 40;
    p->height = 40;
    p->speed = SPEED_MIN; // Começa devagar
    p->vidas = 3;
    p->combustivel = 100.0f;
    p->score = 0;
    p->ativo = true;
    p->cooldown = 0;
    p->proximaVida = 1000; // Próxima vida extra aos 1000 pontos
}

bool UpdatePlayer(Player *p) {
    float lateralSpeed = 3.0f;
    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) p->x -= lateralSpeed;
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) p->x += lateralSpeed;
    
    // Aceleração / Desaceleração (W e S)
    if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) {
        p->speed += ACCEL; // Acelera
    }
    if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) {
        p->speed -= ACCEL; // Freia
    }

    // Limites de Velocidade
    if (p->speed > SPEED_MAX) p->speed = SPEED_MAX;
    if (p->speed < SPEED_MIN) p->speed = SPEED_MIN;


    // O avião sempre anda pra cima (Y diminui) baseado na velocidade
    p->y -= p->speed;

    // Consumo de Combustível 
    p->combustivel -= 0.2f * (p->speed / SPEED_MAX); 
    if (p->combustivel <= 0) p->vidas = 0; 

    if (p->cooldown > 0) {
        p->cooldown--; 
    }

    // Limites da tela (Lateral)
    if (p->x < 0) p->x = 0;
    if (p->x > SCREEN_W - p->width) p->x = SCREEN_W - p->width;
    
    // Limite Final do Mapa (Opcional: Ganha a fase se Y < 0)
    if (p->y < 0) {
        // Chegou no fim da fase
        return true;
    }
    return false;
}

// --- COLISÕES ---

void VerificarColisoes(Player *p, MapData *mapa, Sound somExplosao) {
    float margem = 10.0f; 

    Rectangle rectPlayer = {
        p->x + margem,              // Empurra X para dentro
        p->y + margem,              // Empurra Y para dentro
        p->width - (margem * 2),    // Diminui a largura total
        p->height - (margem * 2)    // Diminui a altura total
    };

    // Otimização: Calcula quais linhas da matriz o jogador está perto
    // Ao invés de checar o mapa todo (80 linhas), checa só onde o player está
    int linhaPlayer = (int)(p->y / TILE_SIZE);
    
    // Checa 2 linhas pra cima e 2 pra baixo pra garantir
    int startRow = linhaPlayer - 2;
    int endRow = linhaPlayer + 2;
    if (startRow < 0) startRow = 0;
    if (endRow >= MAP_ROWS) endRow = MAP_ROWS - 1;

    for (int row = startRow; row <= endRow; row++) {
        for (int col = 0; col < MAP_COLS; col++) {
            char tile = mapa->grid[row][col];
            if (tile == ' ') continue;

            Rectangle rectTile = {col * TILE_SIZE, row * TILE_SIZE, TILE_SIZE, TILE_SIZE};

            if (CheckCollisionRecs(rectPlayer, rectTile)) {
                // Obstáculos
                if (tile == 'T' || tile == 'N' || tile == 'X' || tile == 'P') {
                    PlaySound(somExplosao);
                    p->vidas--;
                    // Respawn recuando um pouco
                    p->x = 400; 
                    p->y += 200; // Volta 200 pixels pra trás
                    p->speed = SPEED_MIN;
                    p->combustivel = 100.0f;
                }
                // Combustível
                else if (tile == 'F' || tile == 'U' || tile == 'E' || tile == 'L') {
                    p->combustivel += 0.3f; 
                    if (p->combustivel > 100) p->combustivel = 100;
                }
            }
        }
    }
}

// --- PROJÉTEIS E TIRO ---

void InicializarProjeteis(Projectile tiros[]) {
    for(int i = 0; i < MAX_PROJETEIS; i++) {
        tiros[i].ativo = false;
        tiros[i].speed = 15.0f;
        tiros[i].width = 4;   // Tamanho do tiro
        tiros[i].height = 16;
        tiros[i].continuidade = 0;
    }
}

void Atirar(Projectile tiros[], Player p, Sound somTiro) {
    for(int i = 0; i < MAX_PROJETEIS; i++) {
        if (!tiros[i].ativo) {
            PlaySound(somTiro);
            tiros[i].ativo = true;
            // Centraliza o tiro no jogador
            tiros[i].x = p.x + (p.width / 2) - 2; 
            // O tiro sai da ponta do avião (ajuste visual - cameraY)
            // Nota: Como estamos desenhando relativo à tela no main, aqui salvamos posição absoluta
            tiros[i].y = p.y; 
            tiros[i].continuidade = 45;
            break; 
        }
    }
}

void UpdateProjeteis(Projectile tiros[]) {
    for(int i = 0; i < MAX_PROJETEIS; i++) {
        if (tiros[i].ativo) {
            tiros[i].y -= tiros[i].speed; 
            tiros[i].continuidade--;
            
            // Se sair muito da tela (ou do mapa), desativa
            if (tiros[i].continuidade <= 0) {
                tiros[i].ativo = false; 
            }
        }
    }
}

void DrawProjeteis(Projectile tiros[], float cameraY) {
    for(int i = 0; i < MAX_PROJETEIS; i++) {
        if (tiros[i].ativo) {
            // Ajuste da Câmera para desenhar
            DrawRectangle(tiros[i].x, tiros[i].y - cameraY, tiros[i].width, tiros[i].height, YELLOW);
        }
    }
}

void InicializarExplosoes(Effect boom[]) {
    for(int i=0; i<MAX_EXPLOSOES; i++) {
        boom[i].ativa = false;
        boom[i].tempoVida = 0;
    }
}

void UpdateExplosoes(Effect boom[]) {
    for(int i=0; i<MAX_EXPLOSOES; i++) {
        if (boom[i].ativa) {
            boom[i].tempoVida--;
            if (boom[i].tempoVida <= 0) {
                boom[i].ativa = false;
            }
        }
    }
}

// Verifica se acertou algo 
void VerificarColisaoTiros(Projectile tiros[], MapData *mapa, Player *p, Sound somExplosao, Effect boom[]) {
    for(int i = 0; i < MAX_PROJETEIS; i++) {
        if (!tiros[i].ativo) continue;

        // Pega a posição do tiro no Grid do Mapa
        int col = (int)(tiros[i].x / TILE_SIZE);
        int row = (int)(tiros[i].y / TILE_SIZE);

        // Verifica limites
        if (row >= 0 && row < MAP_ROWS && col >= 0 && col < MAP_COLS) {
            char tile = mapa->grid[row][col];

            // Se acertou algo destrutível
            if (tile == 'N' || tile == 'X' || tile == 'P') {
                PlaySound(somExplosao);
                tiros[i].ativo = false; // Destroi o tiro
                mapa->grid[row][col] = ' '; // Destroi o inimigo (vira água)
                switch (tile){
                    case 'N': p->score += 30; break;
                    case 'X': p->score += 60; break;
                    case 'P': p->score += 200; break;
                }; // Dá pontos baseado no inimigo
            // --- SPAWN DA EXPLOSÃO ---
                for(int k=0; k<MAX_EXPLOSOES; k++) {
                    if (!boom[k].ativa) {
                        boom[k].ativa = true;
                        boom[k].x = col * TILE_SIZE;
                        boom[k].y = row * TILE_SIZE;
                        boom[k].tempoVida = 20; // Dura 20 frames (aprox 0.3 segundos)
                        break;
                    }
                }
            }
            // Se acertou a terra
            else if (tile == 'T') {
                tiros[i].ativo = false;
            }
        }
    }
}