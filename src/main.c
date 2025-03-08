/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltomasze <ltomasze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 15:45:26 by ltomasze          #+#    #+#             */
/*   Updated: 2025/03/08 16:00:00 by ltomasze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int ft_check_args(int argc, char **argv)
{
	if(argc != 2)
		return(printf("Error: wrong number of arguments.\n"), 1);
	int len;
	len = ft_strlen(argv[1]);
	if(len < 4 || ft_strncmp(argv[1] + len - 4, ".cub", len) != 0)
		return(printf("Error: wrong file extension, expected '.cub'.\n"), 1);
	int fd = open(argv[1], O_RDONLY);
	if(fd == - 1)
		return(printf("Error: file does not exist.\n"), 1);
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

int ft_get_map_height(char **map) {
    int count = 0;
    while (map[count] != NULL)
        count++;
    return count;
}

// Funkcja zwracająca maksymalną szerokość mapy (najdłuższy wiersz)
int ft_get_map_width(char **map) {
    int max_width = 0;
    for (int i = 0; map[i] != NULL; i++) {
        int len = strlen(map[i]);
        if (len > max_width)
            max_width = len;
    }
    return max_width;
}

// Funkcja, która wczytuje z pliku linie mapy (pomijając linie konfiguracji)
// i zapisuje je do dynamicznej tablicy (kończonej NULL-em).
// Po zakończeniu, w *height zapisuje liczbę linii, a w *width maksymalną szerokość.
char **ft_get_map_lines(const char *filename, int *height, int *width) {
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        printf("Error: Cannot open file %s\n", filename);
        return NULL;
    }
    
    char **map = NULL;
    int count = 0;
    int max_width = 0;
    int map_started = 0;
    char *line = NULL;
    
    while ((line = get_next_line(fd)) != NULL) {
        // Jeśli mapa jeszcze się nie rozpoczęła, sprawdzamy, czy linia wygląda jak linia mapy.
        if (!map_started && ft_is_map_line(line)) {
            map_started = 1;
        }
        if (map_started) {
            // Jeśli natrafimy na pustą linię po rozpoczęciu mapy, kończymy wczytywanie.
            if (line[0] == '\n' || line[0] == '\0') {
                free(line);
                break;
            }
            map = realloc(map, sizeof(char *) * (count + 1));
            if (!map) {
                printf("Error: Memory allocation failed\n");
                close(fd);
                return NULL;
            }
            map[count] = line;  // zapamiętujemy wczytaną linię
            int len = strlen(line);
            if (len > max_width)
                max_width = len;
            count++;
        } else {
            free(line);
        }
    }
    close(fd);
    
    // Dodajemy NULL jako znacznik końca tablicy
    map = realloc(map, sizeof(char *) * (count + 1));
    map[count] = NULL;
    
    *height = count;
    *width = max_width;
    return map;
}

// Funkcja sprawdzająca granice dla każdej komórki '0' w mapie.
// Dla każdej '0' sprawdzamy jej 8 sąsiadów (w tym przekątne).
// Jeśli którykolwiek sąsiad nie należy do zbioru dozwolonych znaków,
// wypisujemy błąd i zwracamy 1.
int ft_check_map_boundaries(char **map, int height, int max_width) {
    (void)max_width;
    for (int y = 0; y < height; y++) {
        int row_len = strlen(map[y]);
        for (int x = 0; x < row_len; x++) {
            if (map[y][x] == '0') {
                // Sprawdzamy wszystkich 8 sąsiadów
                for (int dy = -1; dy <= 1; dy++) {
                    for (int dx = -1; dx <= 1; dx++) {
                        if (dy == 0 && dx == 0)
                            continue; // pomijamy samą komórkę
                        int ny = y + dy;
                        int nx = x + dx;
                        char neighbor;
                        // Jeśli indeksy są poza zakresem mapy, traktujemy to jako spację
                        if (ny < 0 || ny >= height)
                            neighbor = ' ';
                        else {
                            int neighbor_len = strlen(map[ny]);
                            if (nx < 0 || nx >= neighbor_len)
                                neighbor = ' ';
                            else
                                neighbor = map[ny][nx];
                        }
                        // Dozwolone znaki: '1', '0', 'N', 'S', 'W', 'E'
                        if (neighbor != '1' && neighbor != '0' &&
                            neighbor != 'N' && neighbor != 'S' &&
                            neighbor != 'W' && neighbor != 'E')
                        {
                            printf("Error: Missing boundary\n");
                            return 1;
                        }
                    }
                }
            }
        }
    }
    return 0;
}

int	main(int argc, char **argv)
{

    //t_game game;

	if(ft_check_args(argc, argv))
	{
		printf("Usage: ./cub3d maps/<map_file.cub>\n");
		return 1;
	}
	if(ft_check_tcm(argv[1]) ||
        ft_check_map_is_last(argv[1]) ||
        ft_check_map_vertical(argv[1]) ||
        ft_check_map_characters(argv[1]) ||
        ft_check_map_player_count(argv[1]))
        return 1;
    // Wczytujemy linie mapy do tablicy, ustalając jej wysokość i szerokość
    int height, width;
    char **map = ft_get_map_lines(argv[1], &height, &width);
    if (!map)
        return 1;

    // Sprawdzamy, czy mapa jest zamknięta ścianami, tzn. czy każde '0'
    // ma poprawnych 8 sąsiadów (1, 0, N, S, W, E).
    if (ft_check_map_boundaries(map, height, width))
    {
        // Zwolnienie pamięci w przypadku błędu
        for (int i = 0; i < height; i++)
            free(map[i]);
        free(map);
        return 1;
    }

    // Jeśli wszystkie testy przeszły poprawnie, można przejść do dalszego działania,
    // np. otwarcia okna gry
    // new_window(&game, argv[1]);

    // Zwolnienie pamięci po zakończeniu sprawdzania
    for (int i = 0; i < height; i++)
        free(map[i]);
    free(map);
    return 0;
}