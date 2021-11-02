#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Jogo.h"

struct game_st
{
    int chave;
    char nome[50];
    int ano;
    char empresa[50];
};

JOGO *jogo_criar_vazio()
{
    JOGO *jogo;

    jogo = (JOGO *)calloc(sizeof(JOGO), 1);
    return jogo;
}

JOGO *jogo_criar(int chave, const char *nome, int ano, const char *empresa)
{
    JOGO *jogo;

    jogo = (JOGO *)malloc(sizeof(JOGO));

    if (jogo != NULL)
    {
        jogo->chave = chave;
        strcpy(jogo->nome, nome);
        jogo->ano = ano;
        strcpy(jogo->empresa, empresa);
        return jogo;
    }
    return NULL;
}

JOGO *jogo_ler_std_in()
{
    JOGO jogo;
    scanf("%d", &(jogo.chave));
    scanf(" %[^(\r|\n)]*c", jogo.nome);
    scanf("%d", &(jogo.ano));
    scanf(" %[^(\r|\n)]*c", jogo.empresa);
    return jogo_criar(jogo.chave, jogo.nome, jogo.ano, jogo.empresa);
}

boolean jogo_apagar(JOGO **jogo)
{
    if (*jogo != NULL)
    {
        (*jogo)->chave = ERRO; /*apaga o jogo simbolicamente*/
        free(*jogo);
        *jogo = NULL;
        return TRUE;
    }
    return FALSE;
}

int jogo_get_chave(const JOGO *jogo)
{
    if (jogo != NULL)
    {
        return jogo->chave;
    }
    return ERRO;
}

boolean jogo_set_chave(JOGO *jogo, int chave)
{
    if (jogo != NULL)
    {
        jogo->chave = chave;
        return TRUE;
    }
    return FALSE;
}

void jogo_imprimir(const JOGO *jogo)
{
    if (jogo != NULL)
    {
        printf("\n-->chave: %d", jogo->chave);
        printf("\n-->nome: %s", jogo->nome);
        printf("\n-->ano: %d", jogo->ano);
        printf("\n-->empresa: %s", jogo->empresa);
    }
}
