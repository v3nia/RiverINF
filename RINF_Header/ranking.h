#include "definicoes.h"

static Registro lista[MAX_SCORES];

void CarregarRanking();

void SalvarRanking();

bool VerificarRecorde(int score);

void AdicionarScore(const char *nome, int score);

void DesenharTelaRanking();
