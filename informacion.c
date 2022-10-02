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

/*
    Descripcion: Transforma los datos del año seleccionado en un string
    
    Parametros:
        YearData: Estructura con los datos del año seleccionado
    Retorno:
        char*: String con los datos del año seleccionado
*/

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
    sprintf(precioJuegoCaro, "%.2f", info->price_expensive_game);
    sprintf(precioJuegoBarato, "%.2f", info->price_cheap_game);
    sprintf(totalJuegos, "%d", info->total_games);
    sprintf(mean, "%.3f", meanPrices(info));
    sprintf(totalWindows, "%.2f", getPercentage(info->total_games, info->windows_games));
    sprintf(totalMac, "%.2f", getPercentage(info->total_games, info->mac_games));
    sprintf(totalLinux, "%.2f", getPercentage(info->total_games, info->linux_games));
    // concatenacion de datos
    strcpy(string, "");
    strcat(string, "Año: ");
    strcat(string, "2000");
    strcat(string, "\nJuego mas caro: ");
    strcat(string, info->expensive_game);
    strcat(string, " ");
    strcat(string, precioJuegoCaro);
    strcat(string, "\nJuego mas barato: ");
    strcat(string, info->cheap_game);
    strcat(string, " ");
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

/*
    Descripcion: Calcula el promedio de precios de los juegos del año seleccionado
    
    Parametros:
        YearData: Estructura con los datos del año seleccionado
    Retorno:
        float: Promedio de precios de los juegos del año seleccionado
*/
float meanPrices(YearData *info)
{
    float total = info->total_games;
    float sumPrices = info->sum_prices;
    float mean = sumPrices / total;
    return mean;
}

/*
    Descripcion: Calcula el porcentaje de juegos de una plataforma en especifico
    
    Parametros:
        int total_games: Total de juegos del año seleccionado
        int plataform_games: Total de juegos de una plataforma en especifico
    Retorno:
        float: Porcentaje de juegos de una plataforma en especifico
*/
float getPercentage(int total_games, int plataform_games)
{
    return (plataform_games / (float)total_games )* 100;
}
