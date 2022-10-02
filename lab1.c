#include "padre.h"

int main()
{
    int *positions;
    positions = generateIntermediateFile("datos_juegos_1000.csv", 2010);
    for(int i = 1; i <= positions[0]; i++)
    {
        printf("Position: %d\n", positions[i]);
    }
    return 0;
}