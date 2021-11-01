#ifndef LISTA_H
#define LISTA_H

#include "../Util/Util.h"
#include "../Item/Item.h"

#define TAM_MAX 100 /*estimativa do tamanho máximo da valores*/
#define INICIO 0
#define ERRO (-32000)

typedef struct lista LISTA;

LISTA *lista_criar();
boolean lista_inserir_inicio(LISTA *lista, ITEM *i);
boolean lista_inserir_fim(LISTA *lista, ITEM *item);
boolean lista_inserir_posicao(LISTA *lista, int posicao, ITEM *item);
boolean lista_apagar(LISTA **lista);
boolean lista_remover(LISTA *lista);
boolean lista_remover_item(LISTA *lista, int chave);
int lista_tamanho(const LISTA *lista);
boolean lista_vazia(const LISTA *lista);
boolean lista_cheia(const LISTA *lista);
void lista_imprimir(const LISTA *lista);
ITEM *busca(const LISTA *lista, int chave);
int lista_inserir_ordenado(LISTA *lista, ITEM *i);
boolean lista_contem_algo(const LISTA *lista);
#endif //LISTA_H
