#ifndef ITEM_H
#define ITEM_H

#include "../Util/Util.h"

#define ERRO (-32000)

typedef struct item_st JOGO;

JOGO *item_criar_vazio();
JOGO *item_criar (int chave, const char *nome, const char *descricao, int ataque, int defesa);
JOGO *item_ler_std_in();
boolean item_apagar(JOGO **item);
void item_imprimir(const JOGO *item);
int item_get_chave(const JOGO *item);
boolean item_set_chave(JOGO *item, int chave);

#endif //ITEM_H
