#include <stdio.h>
#include <stdlib.h>

#include "Lista/Lista.h"

void testeInserir();
void testeInserirRemover();

int main()
{
    testeEmpilhaStdin();
    testeInserirRemover();
}

void testeEmpilhaStdin()
{
    LISTA *lista;
    lista = lista_criar();
    JOGO *jogo = jogo_ler_std_in(1);
    lista_inserir_fim(lista, jogo);
    jogo = jogo_ler_std_in(2);
    lista_inserir_fim(lista, jogo);
    jogo = jogo_ler_std_in(3);
    lista_inserir_fim(lista, jogo);
    jogo_imprimir(lista_busca(lista, 1));
    jogo_imprimir(lista_busca(lista, 2));
    jogo_imprimir(lista_busca(lista, 3));
    boolean_print(lista_vazia(lista));
    // should print passed in green
    printf("\033[32m PASSED");
    // should print 3 items
    // lista_apagar(&lista);
}
void testeInserirRemover()
{
    LISTA *lista;
    lista = lista_criar();
    JOGO *jogo = NULL;
    for (int i = 1; i <= 6; i++)
    {
        jogo = jogo_ler_std_in(i);
        lista_inserir_fim(lista, jogo);
    }
    lista_remove_jogos_duplicados(lista);
    printf("\n\n\n");
    for (int i = 1; i <= 6; i++)
    {
        jogo = lista_busca(lista,i);
        jogo_imprimir(jogo);
    }
    boolean_print(lista_vazia(lista));
    // should print passed in green
    printf("\033[32m PASSED");
    // should print 3 items
    // lista_apagar(&lista);
}
