#include "hijo.h"
#define INTERMEDIATE_FILE "intermediate_file.txt"

/*
    Descripcion: obtiene la informacion referente a un año,
        esto leyendo el archivo intermedio desde una posicion
        inicial dada hasta una posicion final.
    Parametros:
        -initial_position: posicion de partida para leer el archivo.
        -final_position: posicion final a leer del archivo.
    Retorno:
        Estructura que contiene toda la informacion referente al año.
*/
YearData *getYearData(int initial_position, int final_position)
{
    int column;
    char read_game_data[100], name[25];
    FILE *file = fopen(INTERMEDIATE_FILE, "r");
    YearData *year_data = createYearData();
    year_data->price_cheap_game = 1000000;
    year_data->price_expensive_game = -1;
    fseek(file, initial_position, SEEK_SET);
    fscanf(file, "%d\n", &year_data->year);
    while (ftell(file) != final_position)
    {
        column = 0;
        fgets(read_game_data, 100, file);
        float price = 0;
        char *value = strtok(read_game_data, ",");

        while (value)
        {
            switch (column)
            {
            case 0:
                strcpy(name, value);
                break;
            case 1:
                price = atof(value);
                year_data->sum_prices += price;
                if (price > year_data->price_expensive_game)
                {
                    year_data->price_expensive_game = price;
                    strcpy(year_data->expensive_game, name);
                }

                if(price < year_data->price_cheap_game)
                {
                    year_data->price_cheap_game = price;
                    strcpy(year_data->cheap_game, name);
                }
                break;
            case 2:
                if(strcmp("True", value) == 0)
                {
                    insert(year_data->free_games, name);
                }
                break;
            case 3:
                if(strcmp("Yes", value) == 0)
                {
                    year_data->windows_games++;
                }
                break;
            case 4:
                if (strcmp("Yes", value) == 0)
                {
                    year_data->mac_games++;
                }   
                break;
            case 5:
                if (value[0] == 'Y')
                {
                    year_data->linux_games++;
                }
                break;
            default:
                break;
            }

            value = strtok(NULL, ",");
            column++;
        }
        year_data->total_games++;
    }

    return year_data;
}