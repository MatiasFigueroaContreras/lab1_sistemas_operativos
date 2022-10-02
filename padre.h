#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "informacion.h"

int *generateIntermediateFile(char *input_file, int initial_year, float min_price);

void writeOutputFile(char *file_name, YearData *data);

void showData(YearData *data);
