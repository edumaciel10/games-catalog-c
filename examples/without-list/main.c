#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "catalog.h"
#include "utils.h"

int main() {
  GAME *games = createEmptyGames(games);
  int sizeOfGames = 0;
  getGames(games, &sizeOfGames);
  CATALOG *catalog = createEmptyCatalog(catalog);
  catalog = getCatalogWithFilters(catalog, games,sizeOfGames);
  printCatalog(catalog);

  freeCatalog(&catalog);
  freeGames(&games,sizeOfGames);
  return 0;
}
