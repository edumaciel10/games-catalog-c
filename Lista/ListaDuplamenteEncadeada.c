#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../Lista/Lista.h"


struct node_st
{
    JOGO *jogo;
    NODE *anterior;
    NODE *proximo;
};

struct lista
{
    NODE *sentinela;
    NODE *fim;
    int tamanho;
};

boolean lista_comeco(const LISTA *lista, const NODE *noAtual);

NODE *getNodeWithKey(int chave, NODE *noAtual);

boolean deleteNode(LISTA *lista, NODE *noAtual);

boolean lista_contem_algo(const LISTA *lista);

boolean deleteNodeIfPossible(LISTA *lista, NODE **noAtual);

LISTA *lista_criar()
{
    /*pré-condição: existir espaço na memória.*/
    LISTA *lista = (LISTA *)malloc(sizeof(LISTA));
    if (lista != NULL)
    {
        NODE *sentinela = (NODE *)malloc(sizeof(NODE));
        sentinela->proximo = NULL;
        NODE *fim = NULL;
        lista->sentinela = sentinela;
        lista->fim = fim;
        lista->tamanho = 0;
    }
    return lista;
}

/*recebe o inicio da lista como argumento e esvazia a mesma*/
void lista_esvazia(LISTA *lista)
{
    NODE *noAtual = lista->sentinela->proximo;
    NODE *proximoReserva;
    while(noAtual != lista->sentinela){
        jogo_apagar( &(noAtual->jogo) );
        proximoReserva = noAtual->proximo;
        free(noAtual); /* apaga o nó*/
        noAtual = NULL;

        noAtual = proximoReserva;
    }

    free(lista->sentinela);
    lista->sentinela = NULL;
    lista->fim = NULL;
}

boolean lista_apagar(LISTA **lista)
{
    if (*lista == NULL)
        return FALSE;
    lista_esvazia(*lista);
    free(*lista);
    *lista = NULL;
    return TRUE;
}

/*Insere um novo nó no fim da lista. PARA LISTAS NÃO ORDENADAS*/
boolean lista_inserir_fim(LISTA *lista, JOGO *jogo)
{
    if ((lista != NULL))
    {
        NODE *pnovo = (NODE *)malloc(sizeof(NODE));
        if (pnovo != NULL)
        {
            pnovo->jogo = jogo;
            if (lista->sentinela->proximo == NULL)
            {
                pnovo->anterior = lista->sentinela;
                lista->sentinela->proximo = pnovo;
            }
            else
            {
                lista->fim->proximo = pnovo;
                pnovo->anterior = lista->fim;
            }
            pnovo->proximo = lista->sentinela;
            lista->sentinela->anterior = pnovo;
            lista->fim = pnovo;
            lista->tamanho++;
            return TRUE;
        }
    }
    return FALSE;
}

JOGO *lista_busca(const LISTA *lista, int chave)
{
    jogo_set_chave(lista->sentinela->jogo, chave);
    NODE *p = lista->sentinela;
    do
    {
        p = p->proximo;
    } while (jogo_get_chave(p->jogo) != chave);
    jogo_set_chave(lista->sentinela->jogo, 0);
    return ((p != lista->sentinela) ? p->jogo : NULL);
}

NODE *getNodeWithKey(int chave, NODE *noAtual)
{
    while (noAtual != NULL && (jogo_get_chave(noAtual->jogo) != chave))
    {
        noAtual = noAtual->proximo;
    }
    return noAtual;
}
boolean lista_remove_jogos_duplicados(LISTA *lista)
{
    lista->sentinela->jogo = jogo_criar_vazio();
    jogo_set_chave(lista->sentinela->jogo, 0);
    NODE *noAtual = lista->sentinela->proximo;
    while (jogo_get_chave(noAtual->jogo) != 0)
    {
        NODE *noAtual2 = noAtual->proximo;
        NODE *proximoReserva;
        while (noAtual2 != NULL 
                && jogo_get_chave(noAtual2->jogo) != 0
                && jogo_get_chave(noAtual->jogo) != 0)
        {
            proximoReserva = noAtual2->proximo;
            if (jogos_iguais(noAtual->jogo, noAtual2->jogo))
            {
                deleteNodeIfPossible(lista, &noAtual2);
            }
            noAtual2 = proximoReserva;
        }
        noAtual = noAtual->proximo;
    }

    jogo_apagar( &(lista->sentinela->jogo) );
    return TRUE;
}

// boolean lista_remover_item(LISTA *lista, int chave)
// {
//     NODE *noAtual = NULL;
//     if (lista_contem_algo(lista))
//     {
//         /*Percorre a lista em busca da chave*/
//         noAtual = lista_busca(chave, chave);
//         /*Se a lista não acabou significa que encontrou a chave*/
//         deleteNodeIfPossible(lista, noAtual);
//     }
//     return FALSE; /*elemento (chave) não está na lista ou lista vazia*/
// }

boolean deleteNodeIfPossible(LISTA *lista, NODE **noAtual)
{
    boolean result;
    if (*noAtual != NULL)
    {
        result = deleteNode(lista, *noAtual);
        *noAtual = NULL;
    }
    else
    {
        result = FALSE;
    }
    return result;
}

// boolean lista_contem_algo(const LISTA *lista)
// {
//     return (lista != NULL) && (!lista_vazia(lista));
// }

boolean lista_remover_meio(NODE *noAnterior, NODE *noVelho, NODE *noProximo) {
    if (noAnterior != NULL && noVelho != NULL && noProximo != NULL) {
        noAnterior->proximo = noVelho->proximo;
        noProximo->anterior = noVelho->anterior;
        noVelho->proximo = noVelho->anterior = NULL;
        jogo_apagar( &(noVelho->jogo) );
        free(noVelho);
        return TRUE;
    }
    
    return FALSE;
}

boolean lista_inserir_meio(NODE *noAnterior, NODE *noNovo, NODE *noProximo) {
    if (noAnterior != NULL && noNovo != NULL && noProximo != NULL) {
        noAnterior->proximo = noProximo->anterior = noNovo;
        noNovo->proximo = noProximo;
        noNovo->anterior = noAnterior;
        return TRUE;
    }
    
    return FALSE;
}

boolean deleteNode(LISTA *lista, NODE *noAtual)
{ 
    // esse método deve ser um dos mais complicados
    // pq tem que tratar alguns casos diferentes
    // se for o nó anteiror ao sentinela
    // se for o nó posterior ao sentinela
    // se a lista sem aquele nó não vai ficar vazia
    // se o nó estiver em qualquer lugar da lista entre o posterior e anterior do sentinela, vulgo meio
    if (noAtual == lista->sentinela
        || noAtual == NULL
        || noAtual->proximo == NULL
        || noAtual->anterior == NULL
        || lista_vazia(lista) == true
    ) {
        return FALSE;
    }
    if ( lista->tamanho == 1 ) { 
        noAtual->proximo = noAtual->anterior = NULL;
        lista->sentinela->proximo = lista->sentinela->anterior = NULL;
        jogo_apagar( &(noAtual->jogo) );
        free(noAtual);
        lista->tamanho--;
        return TRUE;
    }
    if (lista_comeco(lista, noAtual) == TRUE )
    {
        lista_remover_meio(lista->sentinela, noAtual, noAtual->proximo);   
        lista->tamanho--;
        return TRUE;
    }
    if(lista_fim(lista, noAtual) == TRUE)
    {
        lista_remover_meio(noAtual->anterior, noAtual, lista->sentinela);
        lista->tamanho--;
        return TRUE;
    }
    lista_remover_meio(noAtual->anterior, noAtual, noAtual->proximo);
    lista->tamanho--;
    return TRUE;
}

boolean lista_comeco(const LISTA *lista, const NODE *noAtual)
{
    return noAtual == lista->sentinela->proximo;
}
boolean lista_fim(const LISTA *lista, const NODE *noAtual)
{
    return noAtual == lista->sentinela->anterior;
}

boolean lista_vazia(const LISTA *lista)
{
    return lista->tamanho == 0;
}

void lista_imprimir_jogos_from_produtora(LISTA *lista, char *produtora)
{
    if( lista == NULL || strcmp(produtora, "") == 0 ){
        return;
    }
    
    NODE *noAtual = lista->sentinela->proximo;
    char *produtoraAtual;

    do{
        produtoraAtual = jogo_get_empresa(noAtual->jogo);
        if( strcmp(produtoraAtual, produtora) == 0 ){
            printf("%s\n", jogo_get_nome(noAtual->jogo));
        }
        noAtual = noAtual->proximo;
    }while(noAtual != lista->sentinela && noAtual != NULL);
}

void lista_imprimir_jogos_from_ano(LISTA *lista, int ano)
{
    if( lista == NULL || ano < 0 ){
        return;
    }
    
    NODE *noAtual = lista->sentinela->proximo;
    int anoAtual;

    do{
        anoAtual = jogo_get_ano(noAtual->jogo);
        if( anoAtual == ano ){
            printf("%s\n", jogo_get_nome(noAtual->jogo));
        }
        noAtual = noAtual->proximo;
    }while(noAtual != lista->sentinela && noAtual != NULL);
}

void lista_imprimir_todos_jogos(LISTA *lista)
{
    if( lista == NULL ){
        return;
    }
    
    NODE *noAtual = lista->sentinela->proximo;

    do{
        printf("%s\n", jogo_get_nome(noAtual->jogo));
        noAtual = noAtual->proximo;
    }while(noAtual != lista->sentinela && noAtual != NULL);
}

static NODE *get_node_by_index(LISTA *lista, int index)
{
    if( lista == NULL || index < 0 || index >= lista->tamanho){
        return NULL;
    }


    NODE *noAtual = lista->sentinela;
    int current_pos = -1;
    do{
        noAtual = noAtual->proximo;
        current_pos++;
    }while(current_pos < index);

    return noAtual;
}

void lista_imprimir_jogo_from_index(LISTA *lista, int index)
{
    NODE *noAtual = get_node_by_index(lista, index);
    if(noAtual != NULL){
        char *nome = jogo_get_nome(noAtual->jogo);
        printf("%s\n", nome);
    }
}

void lista_mover_direita(LISTA *lista, int index, int steps)
{
    if( lista == NULL || lista->tamanho < 2 || steps <= 0){
        return;
    }

    NODE *noAtual = get_node_by_index(lista, index);

    int tam = lista->tamanho;
    int destino = ( index + (steps % (tam-1)) ) % tam;

    if(destino == index){
        return;
    }

    NODE *noFuturoAnterior = get_node_by_index(lista, destino);

    // saindo da antiga vizinhança
    noAtual->anterior->proximo = noAtual->proximo;
    noAtual->proximo->anterior = noAtual->anterior;
    if( lista_fim(lista, noAtual) ){
        lista->fim = noAtual->anterior;
    }

    // conhecendo nova vizinhança
    if( lista_fim(lista, noFuturoAnterior) ){
        // vai entrar no lugar do primeiro
        NODE *primeiro = lista->sentinela->proximo;
        noAtual->proximo = primeiro;
        primeiro->anterior = noAtual;

        noAtual->anterior = lista->sentinela;
        lista->sentinela->proximo = noAtual;
    }else{
        // vai entrar no meio da lista
        noFuturoAnterior->proximo->anterior = noAtual;
        noAtual->proximo = noFuturoAnterior->proximo;
        noFuturoAnterior->proximo = noAtual;
        noAtual->anterior = noFuturoAnterior;
    }
}

void lista_mover_esquerda(LISTA *lista, int index, int steps)
{
    if( lista == NULL || lista->tamanho < 2 || steps <= 0){
        return;
    }

    NODE *noAtual = get_node_by_index(lista, index);

    int tam = lista->tamanho;
    int destino = ( index - (steps % (tam-1)) ) % tam;

    if(destino < 0){
        destino += tam;
    }

    if(destino == index){
        return;
    }

    NODE *noFuturoProximo = get_node_by_index(lista, destino);

    // saindo da antiga vizinhança
    noAtual->anterior->proximo = noAtual->proximo;
    noAtual->proximo->anterior = noAtual->anterior;
    if( lista_fim(lista, noAtual) ){
        lista->fim = noAtual->anterior;
    }

    // conhecendo nova vizinhança
    if( lista_comeco(lista, noFuturoProximo) ){
        // vai entrar no lugar do ultimo
        NODE *ultimo = lista->fim;
        noAtual->anterior = ultimo;
        ultimo->proximo = noAtual;

        noAtual->proximo = lista->sentinela;
        lista->sentinela->anterior = noAtual;
        
        lista->fim = noAtual;
    }else{
        // vai entrar no meio da lista
        noFuturoProximo->anterior->proximo = noAtual;
        noAtual->anterior = noFuturoProximo->anterior;
        noFuturoProximo->anterior = noAtual;
        noAtual->proximo = noFuturoProximo;
    }
}
