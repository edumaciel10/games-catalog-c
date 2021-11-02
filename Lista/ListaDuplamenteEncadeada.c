#include <stdlib.h>
#include <stdbool.h>
#include "../Lista/Lista.h"

typedef struct node_st NODE;

struct node_st
{
    ITEM *item;
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
        item_apagar(&noAtual->item);
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
boolean lista_inserir_fim(LISTA *lista, ITEM *item)
{
    if ((lista != NULL))
    {
        NODE *pnovo = (NODE *)malloc(sizeof(NODE));
        if (pnovo != NULL)
        {
            pnovo->item = item;
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
ITEM *lista_busca(const LISTA *lista, int chave)
{
    lista->sentinela->item = item_criar_vazio();

    item_set_chave(lista->sentinela->item, chave);
    NODE *p = lista->sentinela;
    do
    {
        p = p->proximo;
    } while (item_get_chave(p->item) != chave);
    item_apagar(&lista->sentinela->item);
    return ((p != lista->sentinela) ? p->item : NULL);
}

NODE *getNodeWithKey(int chave, NODE *noAtual)
{

    while (noAtual != NULL && (item_get_chave(noAtual->item) != chave))
    {
        noAtual = noAtual->proximo;
    }
    return noAtual;
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

// boolean deleteNodeIfPossible(LISTA *lista, NODE *noAtual)
// {
//     boolean result;
//     if (noAtual != NULL)
//     {
//         result = deleteNode(lista, noAtual);
//     }
//     else
//     {
//         result = FALSE;
//     }
//     return result;
// }

// boolean lista_contem_algo(const LISTA *lista)
// {
//     return (lista != NULL) && (!lista_vazia(lista));
// }

// boolean deleteNode(LISTA *lista, NODE *noAtual)
// { /*Se é o 1º da lista basta acertar o ptr inicio*/
//     if (is_list_start(lista, noAtual))
//     {
//         lista->sentinela = noAtual->proximo;
//     }
//     /*Se não é o 1º da lista, há alguém antes dele para acertar o ptr*/
//     else
//     {
//         noAtual->anterior->proximo = noAtual->proximo;
//     }
//     /* Ideia do if/else anterior para o fim da lista */
//     if (noAtual == lista->fim)
//     {
//         lista->fim = noAtual->anterior;
//     }
//     else
//     {
//         noAtual->proximo->anterior = noAtual->anterior;
//     }
//     noAtual->proximo = NULL;
//     noAtual->anterior = NULL;
//     free(noAtual);
//     lista->tamanho--;
//     return TRUE;
// }

// boolean is_list_start(const LISTA *lista, const NODE *noAtual)
// {
//     return noAtual == lista->sentinela->proximo;
// }

boolean lista_vazia(const LISTA *lista)
{
    return lista->tamanho == 0;
}