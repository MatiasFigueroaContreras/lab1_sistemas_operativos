#include "padre.h"
#include "hijo.h"

int main()
{
    int *positions;
    positions = generateIntermediateFile("datos_juegos_1000.csv", 2000, 0);
    YearData *year_data = getYearData(positions[2], positions[3]);
    showData(year_data);
    writeOutputFile("output.txt", year_data);
    return 0;
}