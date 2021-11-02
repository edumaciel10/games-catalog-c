#include <stdio.h>
#include <stdlib.h>

#include "Lista/Lista.h"

void testeEmpilhaStdin();

int main()
{
    testeEmpilhaStdin();
}

void testeEmpilhaStdin()
{
    LISTA *lista;
    lista = lista_criar();
    ITEM *item = item_ler_std_in();
    lista_inserir_fim(lista, item); // sentinela
    item = item_ler_std_in();
    lista_inserir_fim(lista, item); // pnovo 1
    item = item_ler_std_in();
    lista_inserir_fim(lista, item); // pnovo 2
    item_imprimir(lista_busca(lista, 1));
    item_imprimir(lista_busca(lista, 6));
    item_imprimir(lista_busca(lista, 11));
    boolean_print(lista_vazia(lista));
    // should print 3 items
    // lista_apagar(&lista);
}
