#include <stdlib.h>
#include <stdbool.h>
#include "../Lista/Lista.h"

typedef struct node_st NODE;

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

boolean is_list_start(const LISTA *lista, const NODE *noAtual);

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
    lista->sentinela->jogo = jogo_criar_vazio();

    jogo_set_chave(lista->sentinela->jogo, chave);
    NODE *p = lista->sentinela;
    do
    {
        p = p->proximo;
    } while (jogo_get_chave(p->jogo) != chave);
    jogo_apagar(&lista->sentinela->jogo);
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
    NODE *noAtual = lista->sentinela->proximo;
    // implementação se não fosse circular
    // se fosse circular seria noAtual != NULL && jogo_get_chave(p->jogo) != 0 -> nesse caso 0 seria o nosso sentinela, que significa dar a volta na lista :)
    while (noAtual != NULL)
    {
        NODE *noAtual2 = noAtual->proximo;
        while (noAtual2 != NULL)
        {
            if (jogo_iguais(noAtual->jogo, noAtual2->jogo))
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

boolean deleteNode(LISTA *lista, NODE *noAtual)
{ 
    // esse método deve ser um dos mais complicados
    // pq tem que tratar alguns casos diferentes
    // se for o nó anteiror ao sentinela
    // se for o nó posterior ao sentinela
    // se a lista sem aquele nó não vai ficar vazia
    // se o nó estiver em qualquer lugar da lista entre o posterior e anterior do sentinela, vulgo meio
    if (is_list_start(lista, noAtual))
    {
        // tem que validar se é o último, pq a gente iria fazer o sentinela apontar para ele mesmo
        // tem que validar se na lista existe mais de um elemento
        lista->sentinela = noAtual->proximo;
    }
    /*Se não é o 1º da lista, há alguém antes dele para acertar o ptr*/
    else
    {
        noAtual->anterior->proximo = noAtual->proximo;
        noAtual->proximo->anterior = noAtual->anterior;
    }
    /* Ideia do if/else anterior para o fim da lista */
    if (noAtual == lista->fim)
    {
        lista->fim = noAtual->anterior;
    }
    else
    {
        noAtual->proximo->anterior = noAtual->anterior;
    }
    noAtual->proximo = NULL;
    noAtual->anterior = NULL;
    free(noAtual);
    lista->tamanho--;
    return TRUE;
}

// boolean is_list_start(const LISTA *lista, const NODE *noAtual)
// {
//     return noAtual == lista->sentinela->proximo;
// }

boolean lista_vazia(const LISTA *lista)
{
    return lista->tamanho == 0;
}