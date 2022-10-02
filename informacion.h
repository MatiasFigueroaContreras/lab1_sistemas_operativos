#include "linkedList.h"

typedef struct 
{
    int year;
    char *expensive_game;
    float price_expensive_game;
    char *cheap_game;
    float price_cheap_game;
    int total_games;
    float sum_prices;
    int windows_games;
    int mac_games;
    int linux_games;
    LinkedList *free_games;
} YearData;

char *toString(YearData data);

int meanPrices(YearData data);

float getPercentage(int total_games, int plataform_games);
