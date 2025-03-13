/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltomasze <ltomasze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 15:45:26 by ltomasze          #+#    #+#             */
/*   Updated: 2025/03/13 12:41:40 by ltomasze         ###   ########.fr       */
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

int check_path_exists(const char *path)
{
    if (ft_strlen(path) >= 1023)
    {
        printf("Error: Path too long\n");
        return 1;
    }
    char trimmed[1024];
    int i = 0;
    // Skopiuj oryginalną ścieżkę do bufora 'trimmed'
    while (path[i] && i < 1023)
    {
         trimmed[i] = path[i];
         i++;
    }
    trimmed[i] = '\0';

    // Usuń białe znaki (spacje, tabulatory, nowe linie) z końca bufora
    int len = ft_strlen(trimmed);
    while (len > 0 && (trimmed[len - 1] == ' ' ||
                       trimmed[len - 1] == '\t' ||
                       trimmed[len - 1] == '\n'))
    {
         trimmed[len - 1] = '\0';
         len--;
    }

    if (len == 0)
    {
         printf("Error: Empty path\n");
         return 1;  // błąd
    }
    
    int fd;
    // Jeśli ścieżka kończy się na '/', traktujemy ją jako katalog
    if (trimmed[len - 1] == '/')
    {
        fd = open(trimmed, O_RDONLY);
        if (fd == -1)
        {
            printf("Error: Directory not found: %s\n", trimmed);
            return 1;
        }
        close(fd);
        return 0;  // katalog istnieje – sukces
    }
    // Jeśli ścieżka kończy się na ".xpm", traktujemy ją jako plik
    else if (len >= 4 && ft_strncmp(trimmed + len - 4, ".xpm", 4) == 0)
    {
        fd = open(trimmed, O_RDONLY);
        if (fd == -1)
        {
            printf("Error: File not found: %s\n", trimmed);
            return 1;
        }
        close(fd);
        return 0;  // plik istnieje – sukces
    }
    else
    {
        printf("Error: Path '%s' does not end with '/' or '.xpm'\n", trimmed);
        return 1;
    }
}

int ft_check_textures(const char *filename)
{
    int fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        printf("Error: Cannot open file %s\n", filename);
        return 1;
    }

    char *line;
    int error_found = 0;

    while ((line = get_next_line(fd)) != NULL)
    {
        // Sprawdzamy, czy linia zawiera teksturę
        if (ft_is_texture_line(line))
        {
            // Usuwamy białe znaki i przechodzimy do nazwy pliku
            char *path = ft_skip_whitespaces(line);
            
            // Pomijamy "NO", "SO", "WE", "EA"
            while (*path && *path != ' ' && *path != '\t')
                path++;

            // Usuwamy kolejne białe znaki
            path = ft_skip_whitespaces(path);

            // Sprawdzamy poprawność ścieżki
            if (check_path_exists(path) == 1)
                error_found = 1;  // Znaleziono błąd
        }

        free(line);
    }
    
    close(fd);
    return error_found;
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
        ft_check_map_is_last(argv[1]) ||
        ft_check_map_vertical_integrity(argv[1]) ||
        ft_check_map_characters(argv[1]) ||
        ft_check_map_player_count(argv[1]) ||
        ft_check_map_border(argv[1]))
        return 1;
    // new_window(&game, argv[1]);
    return 0;
}
