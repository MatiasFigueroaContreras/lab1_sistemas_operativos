#include "padre.h"
#include "hijo.h"
#include <sys/types.h>
#include <unistd.h>
#include <getopt.h>

void usage(FILE *fp, const char *path)
{
    const char *basename = path + 2;
    fprintf(fp, "usage: %s [OPTION]\n", basename);
    fprintf(fp, "The following is the correct format for using the program:\t\t"
                "\n'./lab1 -i input_file -o output_file -d year -p price -b'\n");
    fprintf(fp, "  -h, --help\t\t"
                "Print this help and exit.\n");
    fprintf(fp, "  -i, --input[=INPUTFILENAME]\t"
                "Write all output to a file (defaults to out.txt).\n");
    fprintf(fp, "  -o, --output[=OUTPUTFILENAME]\t");
    fprintf(fp,"-d, year required to start the search.\n");
    fprintf(fp, "  -m, --min[=MINPRICE]\t"
                "Minimum price required to start the search.\n");
    fprintf(fp, "-b, print the data in the console.\n");
}


int main(int argc, char *argv[])
{
    int print_flag = 0;
    int help_flag = 0;
    int opt, year = -1;
    float min_price = -1;
    char input_file[100], output_file[100];

    struct option longopts[]=
{   {"help", no_argument, &help_flag, 1},
    {"input", required_argument, NULL, 'i'},
    {"output", optional_argument, NULL, 'o'},
    {"year", required_argument, NULL, 'd'},
    {"min_price", required_argument, NULL, 'p'},
    {"print_flag", no_argument, NULL, 'b'},
    {0, 0, 0, 0}
};

    while ((opt = getopt_long(argc, argv, ":i:o:d:p:b::h",longopts,0)) != -1)
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
        case 'h':
            usage(stdout, argv[0]);
            exit(EXIT_SUCCESS);
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

    if(input_file == NULL || output_file == NULL || year < 0 || min_price < 0)
    {
    usage(stderr, argv[0]);
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
