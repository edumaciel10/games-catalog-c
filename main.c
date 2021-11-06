#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Lista/Lista.h"

void testeEmpilhaStdin();
void testeInserir();
void testeInserirRemover();
void testePesquisas();
LISTA *lerJogosDoCSV();

int main()
{
    LISTA *catalogo;
    catalogo = lerJogosDoCSV();

    char input[2];
    scanf("%s",input);
    getchar();
    char *aux;
    char *aux2;
    while(strcmp(input,"f") != 0) {
        if(strcmp(input,"r") ==0) {
            lista_remove_jogos_duplicados(catalogo);
        }
        if(strcmp(input,"p")==0) {
            aux = readLine();
            lista_imprimir_jogos_from_produtora(catalogo,aux);
        }
        if(strcmp(input,"a")==0) {
            aux2 = readLine();
            lista_imprimir_jogos_from_ano(catalogo,atoi(aux2));
        }
        if(strcmp(input,"i")==0) {
            lista_imprimir_todos_jogos(catalogo);
        }
        if(strcmp(input,"u")==0) {
            aux = readLine();
            // lista_imprimir_jogo_from_index(catalogo,atoi(aux));
        }
        if(strcmp(input,"mr")==0) {
            aux = readLine();
            aux2 = readLine();
        //     lista_mover_direita(catalogo,atoi(aux2),atoi(aux));
        }
        if(strcmp(input,"ml")==0) {
            aux = readLine();
            aux2 = readLine();
        //     lista_mover_esquerda(catalogo,atoi(aux2),atoi(aux));
        }
        if(strcmp(input,"f")==0) {
            break;
        }
        scanf("%s",input);
        getchar();
    }
    return 0;

    //testeEmpilhaStdin();
    //testeInserirRemover();
    //testePesquisas();
}

LISTA *lerJogosDoCSV(){
    FILE *arquivo;
    arquivo = fopen("CSV.csv", "r");
    fseek(arquivo, 3, SEEK_SET);
    JOGO *jogo;
    int key = 1;
    LISTA *lista = lista_criar();
    while( !feof(arquivo) ){
        jogo = jogo_ler_linha_csv(arquivo, key);
        if(jogo != NULL){
            lista_inserir_fim(lista, jogo);
            key++;
        }
    }
    fclose(arquivo);
    return lista;
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
void testePesquisas()
{
    LISTA *lista;
    lista = lista_criar();
    JOGO *jogo = NULL;
    for (int i = 1; i <= 6; i++)
    {
        jogo = jogo_ler_std_in(i);
        lista_inserir_fim(lista, jogo);
    }
    printf("\n\n\n");
    printf("Produtora:\n");
    lista_imprimir_jogos_from_produtora(lista, "Ubisoft");
    printf("\nAno:\n");
    lista_imprimir_jogos_from_ano(lista, 2013);
    printf("\nTodos jogos:\n");
    lista_imprimir_todos_jogos(lista);
    boolean_print(lista_vazia(lista));
    // should print passed in green
    printf("\033[32m PASSED");
    // should print 3 items
    // lista_apagar(&lista);
}
