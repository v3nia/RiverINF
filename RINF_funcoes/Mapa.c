#include "Mapa.h"

void DesenhaMapa(FILE *arquivo, TexturasMapa Temas) {

void CarregarTexturasMapa(void)
{
    texTerra  = LoadTexture("Sprites/T.png");
    texNavio  = LoadTexture("Sprites/N.png");
    texHeli   = LoadTexture("Sprites/x.png");
    texFuelF  = LoadTexture("Sprites/F.png");
    texFuelU  = LoadTexture("Sprites/U.png");
    texFuelE  = LoadTexture("Sprites/E.png");
    texFuelL  = LoadTexture("Sprites/L.png");
    texPonte  = LoadTexture("Sprites/P.png");
}

void DescarregarTexturasMapa(void)
{
    UnloadTexture(texTerra);
    UnloadTexture(texNavio);
    UnloadTexture(texHeli);
    UnloadTexture(texFuelF);
    UnloadTexture(texFuelU);
    UnloadTexture(texFuelE);
    UnloadTexture(texFuelL);
    UnloadTexture(texPonte);
}

void InitObstaculos(Obstaculo obstaculos[])
{
    for(int i = 0; i < MAX_OBSTACULOS; i++)
    {
        obstaculos[i].ativo = false;
    }
}

void CarregarObstaculos(Obstaculo obstaculos[], const char* nomeArquivo)
{
    InitObstaculos(obstaculos);

    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL)
    {
        printf("ERRO: Nao abriu mapa %s\n", nomeArquivo);
        return;
    }

    int count = 0;
    char ch;

    
    for (int linha = 0; linha < 80; linha++) {
        for (int coluna = 0; coluna < 24; coluna++) {
            
           
            ch = fgetc(arquivo);


    for (int linha = 0; linha < 20; linha++)
    {
        for (int coluna = 0; coluna < 24; coluna++)
        {

            ch = fgetc(arquivo);
            while (ch == '\n' || ch == '\r')
            {
                ch = fgetc(arquivo);
            }
            if (ch == EOF) break;

            if (ch == ' ') continue;

                
                switch(ch) {
                    case 'T': DrawTexture (Temas.Terra, coluna, linha, WHITE); break; // Terra
                    case 'N': DrawTexture (Temas.Navio, coluna, linha, WHITE); break; // Navio
                    case 'X': DrawTexture (Temas.Helicoptero, coluna, linha, WHITE); break; // Helicóptero
                    case 'F': DrawTexture (Temas.CombustivelF, coluna, linha, WHITE); break; // Combustível
                    case 'U': DrawTexture (Temas.CombustivelU, coluna, linha, WHITE); break; // Combustível
                    case 'E': DrawTexture (Temas.CombustivelE, coluna, linha, WHITE); break; // Combustível
                    case 'L': DrawTexture (Temas.CombustivelL, coluna, linha, WHITE); break; // Combustível
                    case 'P': DrawTexture (Temas.Ponte, coluna, linha, WHITE); break; // Ponte
                    case ' ': DrawRectangle(coluna, linha, 40, 40, BLUE); break; // mar
                }
                
            }
        }
    }
    fclose(arquivo);
}

void DrawMapa(Obstaculo obstaculos[])
{
    for(int i = 0; i < MAX_OBSTACULOS; i++)
    {
        if (!obstaculos[i].ativo) continue;

        int x = (int)obstaculos[i].x;
        int y = (int)obstaculos[i].y;

        switch(obstaculos[i].tipo)
        {
        case TERRA:
            DrawTexture(texTerra, x, y, WHITE);
            break;
        case NAVIO:
            DrawTexture(texNavio, x, y, WHITE);
            break;
        case HELICOPTERO:
            DrawTexture(texHeli, x, y, WHITE);
            break;
        case PONTE:
            DrawTexture(texPonte, x, y, WHITE);
            break;

        case FUEL_F:
            DrawTexture(texFuelF, x, y, WHITE);
            break;
        case FUEL_U:
            DrawTexture(texFuelU, x, y, WHITE);
            break;
        case FUEL_E:
            DrawTexture(texFuelE, x, y, WHITE);
            break;
        case FUEL_L:
            DrawTexture(texFuelL, x, y, WHITE);
            break;

        default:
            break;
        }
    }
}
