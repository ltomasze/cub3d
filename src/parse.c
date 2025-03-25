#include "cub3d.h"

int ft_get_texture_index(char *line)
{
    if (ft_strncmp(line, "NO", 2) == 0)
        return (0);
    if (ft_strncmp(line, "SO", 2) == 0)
        return (1);
    if (ft_strncmp(line, "WE", 2) == 0)
        return (2);
    if (ft_strncmp(line, "EA", 2) == 0)
        return (3);
    return (-1);
}

void ft_parse_texture(char *line, t_config *config)
{
    char *path;
    int index;

    while (*line == ' ' || *line == '\t') // Pomijanie początkowych białych znaków
        line++;

    index = ft_get_texture_index(line);
    if (index == -1)
        return;

    line += 2; // Przechodzimy za "NO", "SO", "WE", "EA"
    while (*line == ' ' || *line == '\t') // Pomijanie kolejnych białych znaków przed ścieżką
        line++;

    path = ft_strdup(line); // Kopiujemy ścieżkę do tekstury
    if (path)
        config->textures[index] = path;
}

int ft_extract_rgb(char *line, int *r, int *g, int *b)
{
    int values[3];
    int i;

    i = 0;
    while (i < 3)
    {
        while (*line == ' ' || *line == '\t') // Pomijanie białych znaków przed liczbą
            line++;

        if (!ft_isdigit(*line)) // Sprawdzenie, czy znak jest cyfrą
            return (0);
        
        values[i] = ft_atoi(line); // Konwersja liczby
        
        while (*line && *line != ',' && *line != ' ' && *line != '\t') // Przejście przez liczbę
            line++;

        if (i < 2) // Po pierwszych dwóch liczbach sprawdzamy przecinek
        {
            while (*line == ' ' || *line == '\t') // Pomijanie białych znaków przed przecinkiem
                line++;
            if (*line != ',') // Brak przecinka między wartościami
                return (0);
            line++; // Przesuwamy wskaźnik za przecinek
        }
        i++;
    }

    *r = values[0];
    *g = values[1];
    *b = values[2];

    return (1);
}

void ft_parse_color(char *line, t_config *config)
{
    int r, g, b;
    int *color_ptr;

    while (*line == ' ' || *line == '\t') // Pomijanie początkowych białych znaków
        line++;

    if (ft_strncmp(line, "F", 1) == 0 && (line[1] == ' ' || line[1] == '\t'))
        color_ptr = &config->floor_color;
    else if (ft_strncmp(line, "C", 1) == 0 && (line[1] == ' ' || line[1] == '\t'))
        color_ptr = &config->ceiling_color;
    else
        return;

    line += 2; // Przesuwamy wskaźnik za "F " lub "C "
    while (*line == ' ' || *line == '\t') // Pomijanie kolejnych białych znaków
        line++;

    if (!ft_extract_rgb(line, &r, &g, &b))
        return;

    *color_ptr = (r << 16) | (g << 8) | b;
}

int ft_count_map_lines(const char *filename)
{
    int fd;
    char *line;
    int row_count = 0;

    fd = ft_open_file(filename);
    if (fd == -1)
        return (-1);  // Błąd otwarcia pliku

    line = get_next_line(fd);
    while (line != NULL)
    {
        if (ft_is_map_line(line))  // Sprawdzamy, czy to linia mapy
            row_count++;
        free(line);  // Zwalniamy pamięć
        line = get_next_line(fd);  // Wczytujemy kolejną linię
    }

    close(fd);  // Zamykamy plik
    return (row_count);  // Zwracamy liczbę linii mapy
}

void ft_parse_map(const char *filename, t_config *config)
{
    int fd;
    char *line;
    int row = 0;
    int map_lines;
	int i;

	if (config->map != NULL)
    {
        i = 0;
        while (config->map[i] != NULL)
        {
            free(config->map[i]);
            i++;
        }
        free(config->map);
        config->map = NULL;
    }
    // Liczymy liczbę linii mapy
    map_lines = ft_count_map_lines(filename);
    if (map_lines == -1)
    {
        printf("Error: Could not count map rows\n");
        return;
    }

    // Alokujemy pamięć na mapę w zależności od liczby linii
    config->map = malloc(sizeof(char *) * (map_lines + 1));  // +1 na NULL na końcu

    if (config->map == NULL)
    {
        printf("Error: Memory allocation failed for map\n");
        return;
    }

    // Otwieramy plik .cub
    fd = ft_open_file(filename);
    if (fd == -1)
        return;

    line = get_next_line(fd);
    while (line != NULL)
    {
        if (ft_is_map_line(line))  // Sprawdzamy, czy to linia mapy
        {
            config->map[row] = ft_strdup(line);  // Kopiujemy linię mapy
            row++;
        }
        free(line);  // Zwalniamy pamięć
        line = get_next_line(fd);  // Wczytujemy kolejną linię
    }

    // Zakończenie mapy, dodajemy NULL na końcu
    config->map[row] = NULL;
    close(fd);  // Zamykanie pliku
}

int ft_parse_cub(const char *filename, t_config *config)
{
    int     fd;
    char    *line;

    fd = ft_open_file(filename);
    if (fd == -1)
        return (1);

    while ((line = get_next_line(fd)) != NULL)
    {
        if (ft_is_texture_line(line))
            ft_parse_texture(line, config);
        else if (ft_is_color_line(line))
            ft_parse_color(line, config);
        else if (ft_is_map_line(line))
            ft_parse_map(filename, config);
        free(line);
    }
    close(fd);
    return (0);
}
