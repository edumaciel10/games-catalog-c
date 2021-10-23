#ifndef GAME_H
#define GAME_H

typedef struct game_ GAME;

GAME *createEmptyGames(GAME * games);
GAME createGame(char name[], char enterprise[], int year);
GAME * getGames(GAME *game, int * sizeOfGames);
GAME * getGamesByYear(GAME * games,GAME * gamesOfCatalog, int year, int sizeOfGames, int *sizeOfDestiny);
GAME * getGamesByEnterprise(GAME * games,GAME * gamesOfCatalog,  char enterprise[50], int sizeOfGames, int *sizeOfDestiny);
void printGameNameOfCatalog(GAME *game, int size);
void freeGames(GAME **game, int size);
#endif //GAME_H
