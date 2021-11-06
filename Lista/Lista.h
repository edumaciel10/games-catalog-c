#ifndef LISTA_H
#define LISTA_H

#include "../Util/Util.h"
#include "../Jogo/Jogo.h"

#define TAM_MAX 100 /*estimativa do tamanho máximo da valores*/
#define INICIO 0
#define ERRO (-32000)

typedef struct lista LISTA;
typedef struct node_st NODE;

LISTA *lista_criar();
boolean lista_inserir_inicio(LISTA *lista, JOGO *i);
boolean lista_inserir_fim(LISTA *lista, JOGO *jogo);
boolean lista_inserir_posicao(LISTA *lista, int posicao, JOGO *jogo);
boolean lista_apagar(LISTA **lista);
boolean lista_remover(LISTA *lista);
boolean lista_remover_jogo(LISTA *lista, int chave);
int lista_tamanho(const LISTA *lista);
boolean lista_vazia(const LISTA *lista);
boolean lista_cheia(const LISTA *lista);
boolean lista_fim(const LISTA *lista, const NODE *noAtual);
boolean lista_comeco(const LISTA *lista, const NODE *noAtual);
void lista_imprimir(const LISTA *lista);
JOGO *lista_busca(const LISTA *lista, int chave);
int lista_inserir_ordenado(LISTA *lista, JOGO *i);
boolean lista_contem_algo(const LISTA *lista);
boolean lista_remove_jogos_duplicados(LISTA *lista);
void lista_imprimir_jogos_from_produtora(LISTA *lista, char *produtora);
void lista_imprimir_jogos_from_ano(LISTA *lista, int ano);
void lista_imprimir_todos_jogos(LISTA *lista);
void lista_imprimir_jogo_from_index(LISTA *lista, int index);
void lista_mover_direita(LISTA *lista, int index, int steps);
#endif //LISTA_H
