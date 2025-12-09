#include "Mapa.h"
#include "raylib.h"

void DesenhaMapa(FILE *arquivo) {

    Texture2D Terra = LoadTexture("Sprites/T.png");
    Texture2D Navio = LoadTexture("Sprites/N.png");
    Texture2D Helicoptero = LoadTexture("Sprites/x.png");
    Texture2D CombustivelF = LoadTexture("Sprites/F.png");
    Texture2D CombustivelU = LoadTexture("Sprites/U.png");
    Texture2D CombustivelE = LoadTexture("Sprites/E.png");
    Texture2D CombustivelL = LoadTexture("Sprites/L.png");
    Texture2D Ponte = LoadTexture("Sprites/P.png");

    char ch;
    int linha = 0;
    int coluna = 0;
    

    
    for (int linha = 0; linha < 80; linha++) {
        for (int coluna = 0; coluna < 24; coluna++) {
            
           
            ch = fgetc(arquivo);

            
            while (ch == '\n' || ch == '\r') {
                ch = fgetc(arquivo);
            }
            if (ch == EOF) break; 
            
            if (ch == ' ') continue;

                
                switch(ch) {
                    case 'T': DrawTexture(Terra, coluna, linha, WHITE); break; // Terra
                    case 'N': DrawTexture(Navio, coluna, linha, WHITE); break; // Navio
                    case 'X': DrawTexture(Helicoptero, coluna, linha, WHITE); break; // Helicóptero
                    case 'F': DrawTexture(CombustivelF, coluna, linha, WHITE); break; // Combustível
                    case 'U': DrawTexture(CombustivelU, coluna, linha, WHITE); break; // Combustível
                    case 'E': DrawTexture(CombustivelE, coluna, linha, WHITE); break; // Combustível
                    case 'L': DrawTexture(CombustivelL, coluna, linha, WHITE); break; // Combustível
                    case 'P': DrawTexture(Ponte, coluna, linha, WHITE); break; // Ponte
                    case ' ': DrawRectangle(coluna, linha, 40, 40, BLUE); break; // mar
                }
                
            }
        }
}

void CarregaMapa(FILE *arquivo, Rectangle* Combustivel[], Rectangle* Obstaculo[]) {

    char ch;
    int linha, coluna; 
    int x, y;

    for (int linha = 0; linha < 80; linha++) {
        for (int coluna = 0; coluna < 24; coluna++) {
            
           
            ch = fgetc(arquivo);

            
            while (ch == '\n' || ch == '\r') {
                ch = fgetc(arquivo);
            }
            if (ch == EOF) break; 
            
            if (ch == ' ') continue;
                x = coluna * 40;
                y = linha * 40;
                
                switch(ch) {
                    case 'T': Obstaculo[linha][coluna] = (Rectangle){x, y, 40, 40}; break; // Terra
                    case 'N': Obstaculo[linha][coluna] = (Rectangle){x, y, 40, 40}; break; // Navio
                    case 'X': Obstaculo[linha][coluna] = (Rectangle){x, y, 40, 40}; break; // Helicóptero
                    case 'F': Combustivel[linha][coluna] = (Rectangle){x, y, 40, 40}; break; // Combustível
                    case 'U': Combustivel[linha][coluna] = (Rectangle){x, y, 40, 40}; break; // Combustível
                    case 'E': Combustivel[linha][coluna] = (Rectangle){x, y, 40, 40}; break; // Combustível
                    case 'L': Combustivel[linha][coluna] = (Rectangle){x, y, 40, 40}; break; // Combustível
                    case 'P': Obstaculo[linha][coluna] = (Rectangle){x, y, 40, 40}; break; // Ponte
                    case ' ': Obstaculo[linha][coluna] = (Rectangle){x, y, 40, 40}; break; // mar
                }
                
            }
        }
    return;
}   
