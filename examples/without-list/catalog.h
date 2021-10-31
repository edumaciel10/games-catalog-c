#ifndef CATALOG_H
#define CATALOG_H

typedef struct game_ GAME;

typedef struct catalog_ CATALOG;


CATALOG* createEmptyCatalog(CATALOG* catalog); // should return empty CATALOG
CATALOG* getCatalogWithFilters(CATALOG *catalog, GAME *games, int sizeOfGames);
void printCatalog(CATALOG *catalog);
void freeCatalog(CATALOG **catalog);
#endif //CATALOG_H
