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
boolean lista_inserir_fim(LISTA *lista, JOGO *jogo);
boolean lista_apagar(LISTA **lista);
boolean lista_vazia(const LISTA *lista);
boolean lista_fim(const LISTA *lista, const NODE *noAtual);
boolean lista_comeco(const LISTA *lista, const NODE *noAtual);
int lista_inserir_ordenado(LISTA *lista, JOGO *i);
boolean lista_remove_jogos_duplicados(LISTA *lista);
void lista_imprimir_jogos_from_produtora(LISTA *lista, char *produtora);
void lista_imprimir_jogos_from_ano(LISTA *lista, int ano);
void lista_imprimir_todos_jogos(LISTA *lista);
void lista_imprimir_jogo_from_index(LISTA *lista, int index);
void lista_mover_direita(LISTA *lista, int index, int steps);
void lista_mover_esquerda(LISTA *lista, int index, int steps);
boolean lista_comeco(const LISTA *lista, const NODE *noAtual);
boolean deleteNode(LISTA *lista, NODE *noAtual);
boolean deleteNodeIfPossible(LISTA *lista, NODE **noAtual);
#endif //LISTA_H
