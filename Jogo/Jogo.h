#ifndef JOGO_H
#define JOGO_H

#include "../Util/Util.h"

#define ERRO (-32000)

typedef struct game_st JOGO;

JOGO *jogo_criar_vazio();
JOGO *jogo_criar(int chave, const char *nome, int ano, const char *empresa);
JOGO *jogo_ler_std_in();
boolean jogo_apagar(JOGO **jogo);
void jogo_imprimir(const JOGO *jogo);
int jogo_get_chave(const JOGO *jogo);
boolean jogo_set_chave(JOGO *jogo, int chave);

#endif //JOGO_H
