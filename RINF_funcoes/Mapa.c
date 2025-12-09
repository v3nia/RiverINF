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
    int linha = 80;
    int coluna = 24;
    int index[linha][coluna];
    

    
    for (int linha = 0; linha < 80; linha++) {
        for (int coluna = 0; coluna < 24; coluna++) {
            
           
            ch = fgetc(arquivo);

            
            while (ch == '\n' || ch == '\r') {
                ch = fgetc(arquivo);
            }
            if (ch == EOF) break; 
            
            if (ch == ' ') continue;

                
                switch(ch) {
                    case 'T': DrawTexture(Terra, index[linha][coluna], index[linha][coluna], WHITE); break; // Terra
                    case 'N': DrawTexture(Navio, index[linha][coluna], index[linha][coluna], WHITE); break; // Navio
                    case 'X': DrawTexture(Helicoptero, index[linha][coluna], index[linha][coluna], WHITE); break; // Helicóptero
                    case 'F': DrawTexture(CombustivelF, index[linha][coluna], index[linha][coluna], WHITE); break; // Combustível
                    case 'U': DrawTexture(CombustivelU, index[linha][coluna], index[linha][coluna], WHITE); break; // Combustível
                    case 'E': DrawTexture(CombustivelE, index[linha][coluna], index[linha][coluna], WHITE); break; // Combustível
                    case 'L': DrawTexture(CombustivelL, index[linha][coluna], index[linha][coluna], WHITE); break; // Combustível
                    case 'P': DrawTexture(Ponte, index[linha][coluna], index[linha][coluna], WHITE); break; // Ponte
                    case ' ': DrawRectangle(index[linha][coluna], index[linha][coluna], 40, 40, BLUE); break; // mar
                }
                
            }
        }
    fclose(arquivo);
}
