#include "padre.h"
#include "hijo.h"
#include <sys/types.h>
#include <unistd.h>
#include <getopt.h>

int main(int argc, char *argv[])
{
    int print_flag = 0;
    int opt, year = -1;
    float min_price = -1;
    char input_file[100], output_file[100];

    while ((opt = getopt(argc, argv, ":i:o:d:p:b::h")) != -1)
    {
        switch (opt)
        {
        case 'i': // Archivo de entrada
            strcpy(input_file, optarg);
            break;
        case 'o': // Archivo de salida
            strcpy(output_file, optarg);
            break;
        case 'd': // Año de inicio juego
            year = atoi(optarg);
        case 'p': // Precio minimo
            min_price = atof(optarg);
            break;
        case 'b':
            print_flag = 1;
            break;
        case '?': // flag que no existe
            printf("Error, Flag doesn't exist\n");
            return 1;
        case ':': // cuando se usa mal una flag
            printf("Error, Flag require argument\n");
            return 1;
        default: // se aborta cuando falta flag o argumento obligatorio
            abort();
            break;
        }
    }

    if(input_file == NULL || output_file == NULL || year < 0 || min_price < 0)
    {
        printf("Error, flags required.\n");
        return 0;
    }

    int *positions, pid, total_years;
    positions = generateIntermediateFile(input_file, year, min_price);
    total_years = positions[0];

    for (int i = 1; i < total_years; i++)
    {
        int fd[2];
        pipe(fd);
        pid = fork();
        if (pid == -1)
        {
            printf("Error, child creation.\n");
            return 0;
        }
        else if (pid == 0)
        {
            close(fd[0]);
            YearData *year_data = getYearData(positions[i], positions[i + 1]);
            write(fd[1], toString(year_data), sizeof(char) * 1000);
            close(fd[1]);
            exit(0);
            return 0;
        }
        else
        {
            char string_year_data[1000];
            read(fd[0], string_year_data, sizeof(char) * 1000);
            if (print_flag)
            {
                showData(string_year_data);
            }
            writeOutputFile(output_file, string_year_data);
            close(fd[0]);
        }
    }

    return 0;
}