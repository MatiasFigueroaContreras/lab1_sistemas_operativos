#ifndef YEARDATA_H
#define YEARDATA_H
#include "linkedList.h"

typedef struct
{
    int year;
    char expensive_game[25];
    float price_expensive_game;
    char cheap_game[25];
    float price_cheap_game;
    int total_games;
    float sum_prices;
    int windows_games;
    int mac_games;
    int linux_games;
    LinkedList *free_games;
} YearData;

YearData *createYearData();

char *toString(YearData *data);

float meanPrices(YearData *data);

float getPercentage(int total_games, int plataform_games);
#endif