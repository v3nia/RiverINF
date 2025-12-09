#include "Inimigo.h"

void InitInimigos(Inimigo inimigos[]) {
    for(int i = 0; i < MAX_INIMIGOS; i++) {
        inimigos[i].ativo = false;
    }
}

void CarregarInimigos(Inimigo inimigos[], const char* nomeArquivo) {
    
    InitInimigos(inimigos);

    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("ERRO: Nao foi possivel abrir o mapa: %s\n", nomeArquivo);
        return;
    }

    int count = 0;
    char ch;
    

    
    for (int linha = 0; linha < 20; linha++) {
        for (int coluna = 0; coluna < 24; coluna++) {
            
           
            ch = fgetc(arquivo);

            
            while (ch == '\n' || ch == '\r') {
                ch = fgetc(arquivo);
            }
            if (ch == EOF) break; 
            
            if (ch == ' ') continue;

            
            if (count < MAX_INIMIGOS) {
                inimigos[count].ativo = true;
                inimigos[count].tipo = (TipoInimigo)ch;
                
          
                inimigos[count].x = coluna * 40.0f; 
                inimigos[count].y = linha * 40.0f;
                inimigos[count].width = 40.0f;
                inimigos[count].height = 40.0f;

                
                switch(ch) {
                    case 'T': inimigos[count].cor = DARKGREEN; break; // Terra
                    case 'N': inimigos[count].cor = RED;       break; // Navio
                    case 'X': inimigos[count].cor = ORANGE;    break; // Helicóptero
                    case 'G': inimigos[count].cor = MAGENTA;   break; // Combustível
                    case 'P': inimigos[count].cor = BLACK;     break; // Ponte
                    default:  inimigos[count].cor = WHITE;     break;
                }
                
                count++;
            }
        }
    }

    fclose(arquivo);
    printf("Mapa carregado! Total de objetos: %d\n", count);
}

void DrawInimigos(Inimigo inimigos[]) {
    for(int i = 0; i < MAX_INIMIGOS; i++) {
        if (inimigos[i].ativo) {
            DrawRectangle(
                (int)inimigos[i].x, 
                (int)inimigos[i].y, 
                (int)inimigos[i].width, 
                (int)inimigos[i].height, 
                inimigos[i].cor
            );
            
            
        }
    }
}