#include <stdio.h>
#include <getopt.h>
#include <string.h>

//menu de opciones
void usage (FILE *fp, const char *path)
{
    const char *basename = path+2;

    fprintf (fp, "usage: %s [OPTION]\n", basename);
    fprintf (fp, "  -h, --help\t\t"
                 "Print this help and exit.\n");
    fprintf (fp, "  -f, --file[=FILENAME]\t"
                 "Write all output to a file (defaults to out.txt).\n");
    fprintf (fp, "  -m, --msg=STRING\t"
                 "Output a particular message rather than 'Hello world'.\n");
}

int main(int argc, char *argv[])
{
    FILE *fp; //no se como declarar el archivo
    int help_flag = 0;//no se si realizar un help
    int opt, anio,minprice;
    char *inputFile=NULL, *outputFile=NULL;
    //necesito terminar los longopts
    struct option longopts[] = {
        { "help", no_argument, &help_flag, 1 },
        { "input", required_argument, NULL, 'i' },
        { "output", required_argument, NULL, 'o' },
        { "anio", required_argument, NULL, 'a' },
        { "minprice", required_argument, NULL, 'm' },
        { 0 }};

    while (1) {
        opt = getopt_long (argc, argv, "i:o:d:p:b::h", longopts, 0);
        if (opt == -1) {
            break;
        }
        switch (opt) {
        case 'i': //Archivo de entrada
            strcpy(inputFile, optarg);
            break;
        case 'o': //Archivo de salida
            strcpy(outputFile, optarg);
            break;
        case 'd': //Año de inicio juego
            sscanf(optarg, "%d", &anio);
        case 'h':  //Ayuda
            help_flag = 1;
            break;
        case 'p': //Precio minimo
            sscanf(optarg, "%d", &minprice);
            break; 

        case '?': //flag que no existe
            usage (stderr, argv[0]);
            return 1;
        case ':': // cuando se usa mal una flag
            usage (stderr, argv[0]);
            return 1;
        default: // se aborta cuando falta flag o argumento obligatorio
            break;
        }
    }

//necesito hacer las verificaciones de los archivos
    if (help_flag) {
        usage (stdout, argv[0]);
        return 0;
    }

    if (filename[0]) {
        fp = fopen (filename, "w");
    } else {
        fp = stdout;
    }
    
    if (!fp) {
        fprintf(stderr, "Failed to open file.\n");
        return 1;
    }

    //detecta todo lo que sobra del get opt, archivos basura
    if (optind < argc) 
    {
        printf("Non-option args: ");
        while (optind < argc)
            printf("%s ", argv[optind++]);
        printf("\n");
    }
    fprintf (fp, "%s\n", message);

    fclose (fp);
    return 0;
}