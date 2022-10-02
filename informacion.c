#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "informacion.h"

YearData *createYearData()
{
    YearData *new_year_data = malloc(sizeof(YearData));
    new_year_data->total_games = 0;
    new_year_data->sum_prices = 0;
    new_year_data->windows_games = 0;
    new_year_data->mac_games = 0;
    new_year_data->linux_games = 0;
    new_year_data->free_games = createList();
    return new_year_data;
}

// total del archivo a recabar informacion
char *toString(YearData *info)
{
    // asignacion de memoria
    char *string = malloc(sizeof(char) * 1000);
    char *anio = malloc(sizeof(char) * 50);
    char *precioJuegoCaro = malloc(sizeof(char) * 50);
    char *precioJuegoBarato = malloc(sizeof(char) * 50);
    char *totalJuegos = malloc(sizeof(char) * 50);
    char *mean = malloc(sizeof(char) * 50);
    char *totalWindows = malloc(sizeof(char) * 50);
    char *totalMac = malloc(sizeof(char) * 50);
    char *totalLinux = malloc(sizeof(char) * 50);

    // conversion de datos a string
    sprintf(anio, "%d", info->year);
    sprintf(precioJuegoCaro, "%f", info->price_expensive_game);
    sprintf(precioJuegoBarato, "%f", info->price_cheap_game);
    sprintf(totalJuegos, "%d", info->total_games);
    sprintf(mean, "%f", meanPrices(info));
    sprintf(totalWindows, "%f", getPercentage(info->total_games, info->windows_games));
    sprintf(totalMac, "%f", getPercentage(info->total_games, info->mac_games));
    sprintf(totalLinux, "%f", getPercentage(info->total_games, info->linux_games));
    // concatenacion de datos
    strcpy(string, "");
    strcat(string, "Year: ");
    strcat(string, "2000");
    strcat(string, "\nJuego mas caro: ");
    strcat(string, precioJuegoCaro);
    strcat(string, "\nJuego mas barato: ");
    strcat(string, precioJuegoBarato);
    strcat(string, "\nTotal de juegos: ");
    strcat(string, totalJuegos);
    strcat(string, "\nPromedio de precios: ");
    strcat(string, mean);
    strcat(string, "\nWindows: ");
    strcat(string, totalWindows);
    strcat(string, "%");
    strcat(string, "  Mac: ");
    strcat(string, totalMac);
    strcat(string, "%");
    strcat(string, "  Linux: ");
    strcat(string, totalLinux);
    strcat(string, "%\n");
    for (Node *current = info->free_games->head; current != NULL; current = current->next)
    {
        strcat(string, current->data);
    }

    return string;
}

float meanPrices(YearData *info)
{
    float total = info->total_games;
    float sumPrices = info->sum_prices;
    float mean = sumPrices / total;
    return mean;
}

float getPercentage(int total_games, int plataform_games)
{
    return (plataform_games / (float)total_games )* 100;
}
