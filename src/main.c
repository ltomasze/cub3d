/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltomasze <ltomasze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 15:45:26 by ltomasze          #+#    #+#             */
/*   Updated: 2025/03/13 14:07:42 by ltomasze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int ft_check_args(int argc, char **argv)
{
    if (argc != 2)
        return (printf("Error: wrong number of arguments.\n"), 1);
    int len;
    len = ft_strlen(argv[1]);
    if (len < 4 || ft_strncmp(argv[1] + len - 4, ".cub", len) != 0)
        return (printf("Error: wrong file extension, expected '.cub'.\n"), 1);
    int fd = open(argv[1], O_RDONLY);
    if (fd == -1)
        return (printf("Error: file does not exist.\n"), 1);
    close(fd);
    return 0;
}
/*
int handle_key(int key, t_game *game)
{
    if (key == ESC_KEY)
    {
        mlx_destroy_window(game->mlx, game->win);
        exit(0);
    }
    return (0);
}

char **ft_load_map(const char *filename)
{
    int fd = open(filename, O_RDONLY);
    if (fd == -1)
        return (printf("Error: Cannot open file\n"), NULL);

    char **map = NULL;
    char *line;
    int lines = 0;

    while ((line = get_next_line(fd)) != NULL)
    {
        char *trimmed = line;
        if (ft_is_map_line(trimmed))
        {
            map = realloc(map, sizeof(char *) * (lines + 2));
            map[lines] = ft_strdup(trimmed);
            lines++;
        }
        free(line);
    }
    close(fd);

    if (!map)
        return (printf("Error: No map found in file\n"), NULL);

    map[lines] = NULL;

    // Debugowanie: wypisz mapę, aby sprawdzić, co wczytujemy
    // for (int i = 0; map[i] != NULL; i++)
    // {
    //     printf("Line %d: %s\n", i, map[i]);
    // }

    return map;
}

void draw_map(t_game *game)
{
    int x, y;
    int tile_size = 32;

    for (y = 0; game->map[y] != NULL; y++) // Iteracja po liniach mapy
    {
        int x_offset = 0;

        // Obliczamy przesunięcie w poziomie na podstawie liczby spacji na początku wiersza
        while (game->map[y][x_offset] == ' ') {

            x_offset++;  // Liczymy, ile spacji jest na początku
        }

        for (x = 0; game->map[y][x] != '\0'; x++) // Iteracja po znakach w linii
        {
            if (game->map[y][x] == '1') // Ściana
            {
                // Rysowanie całego kwadratu 32x32 piksele w kolorze czerwonym
                for (int i = 0; i < tile_size; i++)
                {
                    for (int j = 0; j < tile_size; j++)
                    {
                        mlx_pixel_put(game->mlx, game->win, (x) * tile_size + i, y * tile_size + j, 0xFF0000); // Czerwony kolor
                    }
                }
            }
            else if (game->map[y][x] == '0' || game->map[y][x] == ' ') // Puste miejsce
            {
                // Rysowanie całego kwadratu 32x32 piksele w kolorze czarnym
                for (int i = 0; i < tile_size; i++)
                {
                    for (int j = 0; j < tile_size; j++)
                    {
                        mlx_pixel_put(game->mlx, game->win, (x) * tile_size + i, y * tile_size + j, 0x000000); // Czarny kolor
                    }
                }
            }
        }
    }
}

void new_window(t_game *game, const char *map_file)
{
    game->mlx = mlx_init();
    if (!game->mlx)
        exit(printf("Error: mlx init failed\n"));

    game->win = mlx_new_window(game->mlx, 1440, 720, "Cub3D");
    if (!game->win)
        exit(printf("Error: window creation failed\n"));

    game->map = ft_load_map(map_file);
    if (!game->map)
        exit(printf("Error: failed to load map\n"));

    draw_map(game);
    mlx_key_hook(game->win, handle_key, game);
    mlx_loop(game->mlx);
}*/

int ft_is_valid_color_line(char *line)
{
    // Pomijamy początkowe białe znaki
    line = ft_skip_whitespaces(line);

    // Sprawdzamy, czy linia zaczyna się od 'F' lub 'C'
    if (*line != 'F' && *line != 'C')
        return 0; // To nie jest linia koloru, więc nie sprawdzamy dalej

    line++; // Pomijamy literę 'F' lub 'C'

    // Pomijamy kolejne białe znaki po 'F' lub 'C'
    line = ft_skip_whitespaces(line);

    int count_numbers = 0;
    int count_commas = 0;

    while (*line)
    {
        if (*line >= '0' && *line <= '9') // Jeśli cyfra
        {
            count_numbers++;
            // Przechodzimy przez całą liczbę
            while (*line >= '0' && *line <= '9')
                line++;
        }
        else if (*line == ',') // Jeśli przecinek
        {
            count_commas++;
            line++; // Przechodzimy przecinek

            // Pomijamy białe znaki po przecinku
            line = ft_skip_whitespaces(line);

            // Jeśli po przecinku nie ma cyfry lub jest przecinek od razu, błąd
            if (*line < '0' || *line > '9')
            {
                printf("Error: Expected a digit after comma in color line\n");
                return 1;
            }
        }
        else if (*line == ' ' || *line == '\t' || *line == '\n')
        {
            // Jeśli napotkamy białe znaki, pomijamy je
            line++;
        }
        else // Jeśli napotkamy inny znak
        {
            printf("Error: Invalid character '%c' in color line\n", *line);
            return 1;
        }
    }

    // Po przejściu przez całą linię ponownie pomijamy białe znaki (na wszelki wypadek)
    // i sprawdzamy, czy doszliśmy do końca ciągu
    // (w tym momencie białe znaki już nie powinny występować)
    line = ft_skip_whitespaces(line);
    if (*line != '\0')
    {
        printf("Error: Unexpected character '%c' after color components\n", *line);
        return 1;
    }

    // Sprawdzenie formatu: powinna być dokładnie jedna linia z dwoma przecinkami (czyli trzy liczby)
    if (count_commas != 2 || count_numbers != 3)
    {
        printf("Error: Incorrect number format in color line\n");
        return 1;
    }

    return 0; // Linia koloru jest poprawna
}

int ft_check_color_range(char *line)
{
    // Pomijamy początkowe białe znaki
    line = ft_skip_whitespaces(line);

    // Zakładamy, że linia zaczyna się od 'F' lub 'C'
    if (*line != 'F' && *line != 'C')
        return 1; // Nie jest to linia koloru – ale to powinno być obsłużone przez ft_is_valid_color_line

    line++; // Pomijamy literę 'F' lub 'C'
    line = ft_skip_whitespaces(line); // Pomijamy białe znaki po prefiksie

    int i = 0;
    while (i < 3)
    {
        // Pomijamy białe znaki przed liczbą (na wszelki wypadek)
        line = ft_skip_whitespaces(line);

        // Konwertujemy liczbę przy pomocy ft_atoi (zakładamy, że ft_atoi jest poprawnie zaimplementowane)
        int value = ft_atoi(line);
        if (value < 0 || value > 255)
        {
            printf("Error: Color component %d is out of range (0-255)\n", value);
            return 1;
        }

        // Przechodzimy przez cyfry danej liczby
        while (*line >= '0' && *line <= '9')
            line++;

        // Pomijamy białe znaki po liczbie
        line = ft_skip_whitespaces(line);

        // Jeśli to nie była ostatnia liczba, oczekujemy przecinka i pomijamy go
        if (i < 2)
        {
            if (*line == ',')
                line++;
            line = ft_skip_whitespaces(line);
        }
        i++;
    }
    return 0;
}

int ft_check_colours(const char *filename)
{
    int fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        printf("Error: Could not open file %s\n", filename);
        return 1; // Błąd otwarcia pliku
    }

    char *line;
    while ((line = get_next_line(fd)) != NULL) // Odczytujemy plik linia po linii
    {
        char *trimmed = ft_skip_whitespaces(line);

        // Sprawdzamy, czy linia zaczyna się od 'F' lub 'C'
        if (*trimmed == 'F' || *trimmed == 'C')
        {
            if (ft_is_valid_color_line(trimmed) || ft_check_color_range(trimmed)) // Walidacja linii koloru
            {
                free(line);
                close(fd);
                return 1; // Błąd w linii koloru
            }
        }
        free(line);
    }

    close(fd);
    return 0; // Wszystkie linie kolorów są poprawne
}


int main(int argc, char **argv)
{
    // t_game game;

    if (ft_check_args(argc, argv))
    {
        printf("Usage: ./cub3d maps/<map_file.cub>\n");
        return 1;
    }
    if (ft_check_line(argv[1]) ||
        ft_check_tcm(argv[1]) ||
        ft_check_only_one_tc(argv[1]) ||
        ft_check_textures(argv[1]) ||
        ft_check_colours(argv[1]) ||
        ft_check_map_is_last(argv[1]) ||
        ft_check_map_vertical_integrity(argv[1]) ||
        ft_check_map_characters(argv[1]) ||
        ft_check_map_player_count(argv[1]) ||
        ft_check_map_border(argv[1]))
        return 1;
    // new_window(&game, argv[1]);
    return 0;
}
