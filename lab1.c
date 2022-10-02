#include "padre.h"
#include "hijo.h"

int main()
{
    int *positions;
    positions = generateIntermediateFile("datos_juegos_1000.csv", 2000, 0);
    YearData *year_data = getYearData(positions[1], positions[2]);
    printf("%d\n", year_data->windows_games);
    showData(year_data);
    return 0;
}