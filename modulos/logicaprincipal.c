#include "definicoes.h"
#include "logica.h"

// --- MAPA ---

void CarregarMapa(MapData *mapa, int nivel) {
    char caminho[50];
    sprintf(caminho, "Fases/fase %d.txt", nivel);

    FILE *f = fopen(caminho, "r");
    
    // Segurança contra falha de arquivo
    if (!f) {
        printf("ERRO: Nao abriu %s. Criando mapa vazio.\n", caminho);
        for(int i=0; i<MAP_ROWS; i++) 
            for(int j=0; j<MAP_COLS; j++) mapa->grid[i][j] = ' '; // Preenche com água para não morrer
        return;
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
}

// ATENÇÃO: Adicionei o parâmetro "playerY" para fazer a câmera seguir o jogador
void DesenharMapa(MapData *mapa, Resources *res, float playerY) {
    
    // Calcula o "Scroll": Mantém o jogador na parte de baixo da tela (pixel 600)
    // Se o jogador sobe (Y diminui), o scroll diminui junto.
    int cameraY = (int)playerY - 600; 

    for (int row = 0; row < MAP_ROWS; row++) {
        for (int col = 0; col < MAP_COLS; col++) {
            
            char tile = mapa->grid[row][col];
            if (tile == ' ') continue; // Otimização

            // Posição no Mundo
            int worldX = col * TILE_SIZE;
            int worldY = row * TILE_SIZE;

            // Posição na Tela (Mundo - Câmera)
            int screenX = worldX;
            int screenY = worldY - cameraY;

            // Otimização: Só desenha se estiver dentro da tela
            if (screenY < -TILE_SIZE || screenY > SCREEN_H) continue;

            // Retângulos para desenho ajustado (Resolve o HELICÓPTERO CORTADO)
            Rectangle destRect = {screenX, screenY, TILE_SIZE, TILE_SIZE};
            Vector2 origin = {0, 0};

            switch (tile) {
                // Para os objetos normais, desenha direto
                case 'T': DrawTexture(res->terra, screenX, screenY, WHITE); break;
                
                // HELICOPTERO CORRIGIDO: Usa DrawTexturePro
                case 'X': 
                {
                    // Pega a imagem inteira (source)
                    Rectangle sourceRect = {0, 0, res->heli.width, res->heli.height};
                    // Desenha espremida no quadrado 40x40 (destRect)
                    DrawTexturePro(res->heli, sourceRect, destRect, origin, 0.0f, WHITE);
                } break;

                case 'N': DrawTexture(res->navio, screenX, screenY, WHITE); break;
                case 'P': DrawTexture(res->ponte, screenX, screenY, WHITE); break;
                
                case 'F': DrawTexture(res->fuelF, screenX, screenY, WHITE); break;
                case 'U': DrawTexture(res->fuelU, screenX, screenY, WHITE); break;
                case 'E': DrawTexture(res->fuelE, screenX, screenY, WHITE); break;
                case 'L': DrawTexture(res->fuelL, screenX, screenY, WHITE); break;
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
}

void UpdatePlayer(Player *p) {
    // 1. Movimento Lateral (Esquerda/Direita) - Velocidade Fixa lateral
    float lateralSpeed = 5.0f;
    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) p->x -= lateralSpeed;
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) p->x += lateralSpeed;
    
    // 2. Aceleração / Desaceleração (W e S)
    if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) {
        p->speed += ACCEL; // Acelera
    }
    if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) {
        p->speed -= ACCEL; // Freia
    }

    // 3. Limites de Velocidade (Clamp)
    if (p->speed > SPEED_MAX) p->speed = SPEED_MAX;
    if (p->speed < SPEED_MIN) p->speed = SPEED_MIN;

    // 4. Aplica o movimento vertical AUTOMÁTICO
    // O avião sempre anda pra cima (Y diminui) baseado na velocidade
    p->y -= p->speed;

    // 5. Consumo de Combustível (Baseado na velocidade?)
    p->combustivel -= 0.05f;
    if (p->combustivel <= 0) p->vidas = 0; 

    // 6. Limites da tela (Lateral)
    if (p->x < 0) p->x = 0;
    if (p->x > SCREEN_W - p->width) p->x = SCREEN_W - p->width;
    
    // Limite Final do Mapa (Opcional: Ganha a fase se Y < 0)
    if (p->y < 0) {
        // Chegou no fim da fase
    }
}

// --- COLISÕES ---

void VerificarColisoes(Player *p, MapData *mapa) {
    Rectangle rectPlayer = {p->x, p->y, p->width, p->height};

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
                    p->vidas--;
                    // Respawn recuando um pouco
                    p->x = 400; 
                    p->y += 200; // Volta 200 pixels pra trás
                    p->speed = SPEED_MIN;
                    p->combustivel = 100.0f;
                }
                // Combustível
                else if (tile == 'F' || tile == 'U' || tile == 'E' || tile == 'L') {
                    p->combustivel += 1.0f; 
                    if (p->combustivel > 100) p->combustivel = 100;
                    // mapa->grid[row][col] = ' '; // Consumir gasolina?
                }
            }
        }
    }
}

// --- PROJÉTEIS E TIRO ---

void InicializarProjeteis(Projectile tiros[]) {
    for(int i = 0; i < MAX_PROJETEIS; i++) {
        tiros[i].ativo = false;
        tiros[i].speed = 10.0f;
        tiros[i].width = 4;   // Tamanho do tiro
        tiros[i].height = 10;
    }
}

void Atirar(Projectile tiros[], Player p) {
    for(int i = 0; i < MAX_PROJETEIS; i++) {
        if (!tiros[i].ativo) {
            tiros[i].ativo = true;
            // Centraliza o tiro no jogador
            tiros[i].x = p.x + (p.width / 2) - 2; 
            // O tiro sai da ponta do avião (ajuste visual - cameraY)
            // Nota: Como estamos desenhando relativo à tela no main, aqui salvamos posição absoluta
            tiros[i].y = p.y; 
            break; 
        }
    }
}

void UpdateProjeteis(Projectile tiros[]) {
    for(int i = 0; i < MAX_PROJETEIS; i++) {
        if (tiros[i].ativo) {
            tiros[i].y -= tiros[i].speed; 
            
            // Se sair muito da tela (ou do mapa), desativa
            // Valor negativo alto para garantir que saiu do mapa
            if (tiros[i].y < 0) {
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

// Verifica se acertou algo 
void VerificarColisaoTiros(Projectile tiros[], MapData *mapa, Player *p) {
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
                tiros[i].ativo = false; // Destroi o tiro
                mapa->grid[row][col] = ' '; // Destroi o inimigo (vira água)
                p->score += 100; // Dá pontos
            }
            // Se acertou combustível
            else if (tile == 'F' || tile == 'U' || tile == 'E' || tile == 'L') {
                tiros[i].ativo = false;
                mapa->grid[row][col] = ' '; 
                p->score += 50; 
                p->combustivel += 5.0f; // Explodir combustível dá pouco gasosa? (Regra do jogo original)
            }
            // Se acertou a terra
            else if (tile == 'T') {
                tiros[i].ativo = false;
            }
        }
    }
}