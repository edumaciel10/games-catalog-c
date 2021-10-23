#include "game.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "utils.h"

struct game_
{
  char name[50];
  char enterprise[50];
  int year;
};
GAME * createEmptyGames(GAME * games) {
  games = (GAME *)malloc(1 * sizeof(GAME));
  return games;
}

GAME createGame(char name[],char enterprise[], int year){
  GAME *game = (GAME*) malloc(sizeof(GAME));

  strcpy(game->name,name);
  strcpy(game->enterprise,enterprise);
  game->year = year;
  return *game;
}
GAME * getGames(GAME * games, int *sizeOfGames) { 
  char input[50];
  char enterprise[50];
  char year[10];

  int inputIsF = 0;
  do{

    if (!(fgets(input, sizeof input, stdin) != NULL)) {
        exit(1);
    }
    input[strcspn(input, "\r\n")] = 0;

    inputIsF = strcmp(input, "F");
    if(inputIsF == 0){
      break;
    }
    if (!(fgets(enterprise, sizeof enterprise, stdin) != NULL)) {
        exit(1);
    }
    enterprise[strcspn(enterprise, "\r\n")] = 0;

    if (!(fgets(year, sizeof year, stdin) != NULL)) {
        exit(1);
    }
    
    year[strcspn(year, "\r\n")] = 0;

    games = (GAME *)realloc(games, ((*sizeOfGames + 1) * sizeof(GAME)));

    games[*sizeOfGames] = createGame(input, enterprise, atoi(year));
    (*sizeOfGames)++;

    strcpy(input, "");
  } while (inputIsF != 0);

  return games;
}
GAME * getGamesByYear(GAME * games,GAME * gamesOfCatalog, int year, int sizeOfGames, int *sizeGamesOfCatalog) {
  int indexOfFilteredGames = 0;
  for (int i = 0; i < sizeOfGames; i++)
  {
    if(games[i].year == year) {
      gamesOfCatalog = (GAME *)realloc(gamesOfCatalog, (*sizeGamesOfCatalog + 1) * sizeof(GAME));
      gamesOfCatalog[*sizeGamesOfCatalog] = games[i];
      (*sizeGamesOfCatalog)++;
      indexOfFilteredGames++;
    }
  }
  if (indexOfFilteredGames == 0)
  {
    gamesOfCatalog = (GAME *)realloc(gamesOfCatalog, (*sizeGamesOfCatalog + 1) * sizeof(GAME));
    gamesOfCatalog[*sizeGamesOfCatalog] = createGame("Nada encontrado", " ", 0);
    (*sizeGamesOfCatalog)++;
  }
  return gamesOfCatalog;
}
GAME * getGamesByEnterprise(GAME * games,GAME * gamesOfCatalog, char enterprise[50], int sizeOfGames, int *sizeGamesOfCatalog) {
  int indexOfFilteredGames = 0;
  for (int i = 0; i < sizeOfGames; i++)
  {
    if (strcmp(games[i].enterprise, enterprise) == 0)
    {
      gamesOfCatalog = (GAME *)realloc(gamesOfCatalog, (*sizeGamesOfCatalog + 1) * sizeof(GAME));
      gamesOfCatalog[*sizeGamesOfCatalog] = games[i];
      (*sizeGamesOfCatalog)++;
      indexOfFilteredGames++;
    }
  }
  if (indexOfFilteredGames == 0)
  {
    gamesOfCatalog = (GAME *)realloc(gamesOfCatalog, (*sizeGamesOfCatalog + 1) * sizeof(GAME));
    gamesOfCatalog[*sizeGamesOfCatalog] = createGame("Nada encontrado", " ", 0);
    (*sizeGamesOfCatalog)++;
  }
  return gamesOfCatalog;
}

void printGameNameOfCatalog(GAME *game,int size){
  for (int i = 0; i < size; i++)
  {
    printf("%s", game[i].name);
    if(i+1 != size) {
      printf("\n");
    }
  }
}

void freeGames(GAME **game, int size) {
  free(*game);
}