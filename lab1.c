#include "padre.h"
#include "hijo.h"
#include <sys/types.h>
#include <unistd.h>
#include <getopt.h>

/*
    Descripcion: Imprime la informacion de uso referente al formato
        correcto para la ejecucion del programa.
    Parametros:
        -fp: salida por consola.
        -path: direccion donde se encuentra el nombre del programa.
    Retorno:
        no tiene.
*/
void usage(FILE *fp, const char *path)
{
    const char *basename = path + 2;
    fprintf(fp, "usage: %s [OPTION]\n", basename);
    fprintf(fp, "The following is the correct format for using the program:\t\t"
                "\n'./lab1 -i input_file -o output_file -d year -p min_price -b'\n");
    fprintf(fp, "  -h, --help\t\t"
                "Print this help and exit.\n");
    fprintf(fp, "  -i, --input[=INPUTFILENAME]\t"
                "File to read games data.\n");
    fprintf(fp, "  -o, --output[=OUTPUTFILENAME]\t"
                "File to write the output data generated.\n");
    fprintf(fp, "  -d, --year[=YEAR]\t"
                "year required to start the search.\n");
    fprintf(fp, "  -p, --min[=MINPRICE]\t"
                "Minimum price required to start the search.\n");
    fprintf(fp, "  -b, --print[=PRINTFLAG]\t"
                "print the data in the console.\n");
}

int main(int argc, char *argv[])
{
    int print_flag = 0;
    int help_flag = 0;
    int opt, year = -1;
    float min_price = -1;
    char input_file[100], output_file[100];

    struct option longopts[] =
        {{"help", no_argument, &help_flag, 1},
         {"input", required_argument, NULL, 'i'},
         {"output", required_argument, NULL, 'o'},
         {"year", required_argument, NULL, 'd'},
         {"min", required_argument, NULL, 'p'},
         {"print", optional_argument, NULL, 'b'}};

    while ((opt = getopt_long(argc, argv, ":i:o:d:p:b::h", longopts, 0)) != -1)
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
            break;
        case 'p': // Precio minimo
            min_price = atof(optarg);
            break;
        case 'b':
            print_flag = 1;
            break;
        case 'h':
            usage(stdout, argv[0]);
            return 0;
        case '?': // flag que no existe
            usage(stderr, argv[0]);
            return 1;
        case ':': // cuando se usa mal una flag
            usage(stderr, argv[0]);
            return 1;
        default: // se aborta cuando falta flag o argumento obligatorio
            abort();
            break;
        }
    }

    if (input_file == NULL || output_file == NULL || year < 0 || min_price < 0 || help_flag)
    {
        //Entra si no se ingreso alguna opcion o valor necesario para
        //  el funcionamiento del programa, ademas si se ingresa
        //  la flag de ayuda.
        usage(stderr, argv[0]);
        return 1;
    }

    int *positions, pid, total_years;
    positions = generateIntermediateFile(input_file, year, min_price);

    if (positions == NULL)
    {
        // Entra si el archivo de entrada no se encuentra.
        return 1;
    }

    total_years = positions[0];

    for (int i = 1; i < total_years; i++)
    {
        int fd[2];
        pipe(fd);
        pid = fork();
        if (pid == -1)
        {
            printf("Error: child creation.\n");
            return 1;
        }
        else if (pid == 0)
        {
            // Proceso hijo
            close(fd[0]);
            YearData *year_data = getYearData(positions[i], positions[i + 1]);
            write(fd[1], toString(year_data), sizeof(char) * 1000); // Se pasa la informacion por el pipe hacia el padre.
            close(fd[1]);
            exit(0);
            return 0;
        }
        else
        {
            // Proceso padre
            char string_year_data[1000];
            read(fd[0], string_year_data, sizeof(char) * 1000); // Lee la informacion del hijo a traves del pipe.
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
