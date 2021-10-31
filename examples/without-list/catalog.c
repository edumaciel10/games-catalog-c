#include "game.h"
#include "utils.h"
#include "catalog.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct catalog_
{
  GAME *gamesOfCatalog;
  int gamesLength;
} CATALOG;

CATALOG *createEmptyCatalog(CATALOG* catalog)
{
  catalog = (CATALOG *)malloc(1 * sizeof(CATALOG));
  return catalog;
}
CATALOG *getCatalogWithFilters(CATALOG *catalog, GAME *games, int sizeOfGames)
{
  char input[10];
  char inputFilter[50];
  int inputIsF, sizeOfGamesCatalog = 0;
  do
  {
    if (!(fgets(input, sizeof input, stdin) != NULL)) {
        exit(1);
    }
    
    input[strcspn(input, "\r\n")] = 0;

    inputIsF = strcmp(input, "F");
    if (inputIsF == 0)
    {
      break;
    }

    if (!(fgets(inputFilter, sizeof inputFilter, stdin) != NULL)) {
        exit(1);
    }
    
    inputFilter[strcspn(inputFilter, "\r\n")] = 0;

    if (input[0] == 'A')
    {
      catalog->gamesOfCatalog = getGamesByYear(games,catalog->gamesOfCatalog, atoi(inputFilter), sizeOfGames, &sizeOfGamesCatalog);
    }
    if (input[0] == 'E')
    {
      catalog->gamesOfCatalog = getGamesByEnterprise(games, catalog->gamesOfCatalog, inputFilter, sizeOfGames, &sizeOfGamesCatalog);
    }
    catalog->gamesLength = sizeOfGamesCatalog;
  } while (inputIsF != 0);

  return catalog;
}
void printCatalog(CATALOG *catalog){
  printGameNameOfCatalog(catalog->gamesOfCatalog, catalog->gamesLength);
}
void freeCatalog(CATALOG **catalog) {
  if (*catalog != NULL)
  {
      free (*catalog);
      *catalog = NULL;
  }
}
