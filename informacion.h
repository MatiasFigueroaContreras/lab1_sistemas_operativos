struct data
{
    int year;
    char *expensive_game;
    char *cheap_game;
    int total_games;
    int sum_prices;
    int windows_games;
    int mac_games;
    int linux_games;
    // Juegos gratis
};

char *toString(struct data);

int meanPrices(struct data);

int getPercentage(int total_games, int plataform_games);
