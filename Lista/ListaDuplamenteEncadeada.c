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

boolean deleteNodeIfPossible(LISTA *lista, NODE *noAtual);

LISTA *lista_criar()
{
    /*pré-condição: existir espaço na memória.*/
    LISTA *lista = (LISTA *)malloc(sizeof(LISTA));
    if (lista != NULL)
    {
        NODE *sentinela = (NODE *)malloc(sizeof(NODE));
        jogo_set_chave(sentinela->jogo, 0);
        NODE *fim = NULL;
        lista->sentinela = sentinela;
        lista->fim = fim;
        lista->tamanho = 0;
    }
    return lista;
}

/*recebe o inicio da lista como argumento e esvazia a mesma*/
void lista_esvazia(NODE *noAtual)
{
    if (noAtual != NULL)
    {
        if (noAtual->proximo != NULL)
        {
            lista_esvazia(noAtual->proximo);
        }
        jogo_apagar(&noAtual->jogo);
        noAtual->anterior = NULL;
        free(noAtual); /* apaga o nó*/
        noAtual = NULL;
    }
}

boolean lista_apagar(LISTA **lista)
{
    if (*lista == NULL)
        return FALSE;
    lista_esvazia((*lista)->sentinela->proximo);
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
                pnovo->proximo = NULL;
                lista->sentinela->proximo = pnovo;
            }
            else
            {
                lista->fim->proximo = pnovo;
                pnovo->anterior = lista->fim;
                pnovo->proximo = lista->sentinela;
                if (lista->fim->anterior == NULL)
                {
                    lista->fim->anterior = lista->sentinela;
                }
            }
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
    // implementação se não fosse circular
    // se fosse circular seria noAtual != NULL 
    // && jogo_get_chave(p->jogo) != 0 -> 
    // nesse caso 0 seria o nosso sentinela, que significa dar a volta na lista :)
    while (jogo_get_chave(noAtual->jogo) != 0)
    {
        NODE *noAtual2 = noAtual->proximo;
        while (noAtual2 != NULL 
                && jogo_get_chave(noAtual2->jogo) != 0
                && jogo_get_chave(noAtual->jogo) != 0)
        {
            if (jogos_iguais(noAtual->jogo, noAtual2->jogo))
            {
                deleteNodeIfPossible(lista, noAtual2);
            }
            noAtual2 = noAtual2->proximo;
        }
        noAtual = noAtual->proximo;
    }
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

boolean deleteNodeIfPossible(LISTA *lista, NODE *noAtual)
{
    boolean result;
    if (noAtual != NULL)
    {
        result = deleteNode(lista, noAtual);
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
