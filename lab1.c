#include "padre.h"
#include "hijo.h"
#include <sys/types.h>
#include <unistd.h>

int main()
{
    int *positions, pid;
    positions = generateIntermediateFile("datos_juegos_1000.csv", 2000, 0);
    YearData *year_data;
    for (int i = 1; i < positions[0]; i++)
    {
        int fd1[2], fd2[2];
        pipe(fd1);
        pipe(fd2);
        pid = fork();
        if (pid == -1)
        {
            printf("Error\n");
        }
        else if (pid == 0)
        {
            int initial_final_positions[2];
            close(fd1[1]);
            close(fd2[0]);
            read(fd1[0], initial_final_positions, sizeof(int[2]));
            printf("Inicial: %d, Final: %d\n", initial_final_positions[0], initial_final_positions[1]);
            year_data = getYearData(initial_final_positions[0], initial_final_positions[1]);
            write(fd2[1], year_data, sizeof(YearData));
            close(fd1[0]);
            close(fd2[1]);
            exit(0);
            break;
        }
        else
        {
            int initial_final_positions[2] = {positions[i], positions[i + 1]};
            close(fd1[0]);
            close(fd2[1]);
            write(fd1[1], initial_final_positions, sizeof(int[2]));
            year_data = createYearData();
            read(fd2[0], year_data, sizeof(YearData));
            writeOutputFile("output.txt", year_data);
            showData(year_data);
            close(fd1[1]);
            close(fd2[0]);
        }
    }
    return 0;
}