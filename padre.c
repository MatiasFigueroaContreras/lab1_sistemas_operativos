#include "padre.h"
#define INTERMEDIATE_FILE "intermediate_file.txt"

/*
    Descripcion: crea un archivo intermedio con la informacion de los
        juegos obtenida en el archivo de entrada, esta informacion se
        encuentra separada por año, partiendo de un año inicial dado
        y teniendo en cuenta un precio minimo para los juegos a
        ordenar.
    Parametros:
        -input_file: nombre del archivo de entrada.
        -initial_year: año de partida.
        -min_price: precio minimo de los juegos.
    Retorno:
        -NULL: si no se encontro el archivo de entrada
        -int*: arreglo con las posiciones iniciales y finales de los años,
            ademas guarda en la primera posicion el numero de años encontrados.
*/
int *generateIntermediateFile(char *input_file, int initial_year, float min_price)
{
    int column, year, index, max_years = 2022 - initial_year + 1;
    char read_game_data[400];
    FILE *read_file = fopen(input_file, "r");
    if(read_file == NULL)
    {
        printf("Error, Input file doesn't exist\n");
        return NULL;
    }

    LinkedList *years_data[max_years];
    for(int i = 0; i < max_years; i++)
    {
        years_data[i] = createList();
    }
    float price;
    while (fgets(read_game_data, 400, read_file))
    {
        column = 0;
        char write_game_data[300] = "";
        char *value = strtok(read_game_data, ",");
        while (value)
        {
            if(column != 0 && column != 2 && column != 4)
            {
                //No se agregan los valores que no seran utilizados de
                // la informacion del juego.
                if(column == 3)
                {
                    price = atof(value);
                }

                if(column == 5)
                {
                    year = atoi(value);
                }
                else if(column != 1)
                {
                    strcat(write_game_data, ",");
                    strcat(write_game_data, value);
                }
                else
                {
                    strcat(write_game_data, value);
                }

            }
            value = strtok(NULL, ",");
            column++;
        }

        if(initial_year <= year && min_price <= price)
        {
            index = year % max_years;
            insert(years_data[index], write_game_data);
        }
    }

    fclose(read_file);

    FILE *write_file = fopen(INTERMEDIATE_FILE, "w");
    int num_years = 0, pos[max_years];

    for(int y = initial_year; y <= 2022; y++)
    {
        index = y % max_years;
        if(years_data[index]->length != 0)
        {
            pos[num_years] = ftell(write_file);
            num_years++;
            fprintf(write_file, "%d\n", y);
            for (Node *game_node = years_data[index]->head; game_node != NULL; game_node = game_node->next)
            {
                fputs(game_node->data, write_file);
            }
        }
    }
    pos[num_years] = ftell(write_file);
    fclose(write_file);
    int *file_positions = malloc(sizeof(int)*(num_years+1));
    file_positions[0] = num_years;
    for(int i = 1; i <= num_years; i++)
    {
        file_positions[i] = pos[i-1];
    }
    return file_positions;
}

/*
    Descripcion: escribe en el archivo de salida, la informacion
        obtenida de un año especifico, esto lo hace al final del
        archivo.
    Parametros:
        -file_name: nombre del archivo de salida. 
        -data: informacion del año especifico a ser
            escrita en el archivo.
    Retorno:
        no posee.
*/
void writeOutputFile(char *file_name, char *data)
{
    FILE *file = fopen(file_name, "a");
    fseek(file, 0, SEEK_END);
    fputs(data, file);
    fclose(file);
}

/*
    Descripcion: imprime por consola, la informacion
        obtenida de un año especifico.
    Parametros:
        -data: informacion del año especifico a ser
            imprimida por consola.
    Retorno:
        no posee.
*/
void showData(char *data)
{
    printf("%s", data);
}

