/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltomasze <ltomasze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 15:45:26 by ltomasze          #+#    #+#             */
/*   Updated: 2025/03/08 18:14:47 by ltomasze         ###   ########.fr       */
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

int ft_get_map_height(char **map) 
{
    int count = 0;
    while (map[count] != NULL)
        count++;
    return count;
}

int ft_get_map_width(char **map)
{
    int max_width = 0;
    int i = 0;
    while (map[i] != NULL)
    {
        int len = ft_strlen(map[i]);
        if (len > max_width)
            max_width = len;
        i++;
    }
    return max_width;
}

char **ft_get_map_lines(const char *filename, int *height, int *width) 
{
    int fd = open(filename, O_RDONLY);
    if (fd == -1) 
    {
        printf("Error: Cannot open file %s\n", filename);
        return NULL;
    }
    
    char **map = NULL;
    int count = 0;
    int max_width = 0;
    int map_started = 0;
    char *line = NULL;
    
    while ((line = get_next_line(fd)) != NULL) 
    {
        if (!map_started && ft_is_map_line(line)) 
        {
            map_started = 1;
        }
        if (map_started) 
        {
            if (line[0] == '\n' || line[0] == '\0')
            {
                free(line);
                break;
            }
            char **tmp = malloc(sizeof(char *) * (count + 1));
            if (!tmp) 
            {
                printf("Error: Memory allocation failed\n");
                close(fd);
                return NULL;
            }
            int i = 0;
            while (i < count) 
            {
                tmp[i] = map[i];
                i++;
            }
            // Zwalniamy starą tablicę (same wskaźniki nie są zwalniane, bo nadal wskazują na zaalokowane linie)
            free(map);
            map = tmp;
            map[count] = line;
            int len = ft_strlen(line);
            if (len > max_width)
                max_width = len;
            count++;
        } 
        else 
        {
            free(line);
        }
    }
    close(fd);
    char **tmp = malloc(sizeof(char *) * (count + 1));
    if (!tmp) 
    {
        printf("Error: Memory allocation failed\n");
        return NULL;
    }
     int i = 0;
    while (i < count) 
    {
        tmp[i] = map[i];
        i++;
    }
    free(map);
    map = tmp;
    map[count] = NULL;
    
    *height = count;
    *width = max_width;
    return map;
    
}

int ft_check_floor_border(char **map, int height, int max_width)
{
    (void)max_width;
    int y = 0;
    while (y < height)
    {
        int row_len = ft_strlen(map[y]);
        int x = 0;
        while (x < row_len)
        {
            if (map[y][x] == '0')
            {
                int dy = -1;
                while (dy <= 1)
                {
                    int dx = -1;
                    while (dx <= 1)
                    {
                        if (!(dy == 0 && dx == 0))
                        {
                            int ny = y + dy;
                            int nx = x + dx;
                            char neighbor;
                            if (ny < 0 || ny >= height)
                                neighbor = ' ';
                            else
                            {
                                int neighbor_len = ft_strlen(map[ny]);
                                if (nx < 0 || nx >= neighbor_len)
                                    neighbor = ' ';
                                else
                                    neighbor = map[ny][nx];
                            }
                            if (neighbor != '1' && neighbor != '0' &&
                                neighbor != 'N' && neighbor != 'S' &&
                                neighbor != 'W' && neighbor != 'E')
                            {
                                printf("Error: Missing boundary\n");
                                return 1;
                            }
                        }
                        dx++;
                    }
                    dy++;
                }
            }
            x++;
        }
        y++;
    }
    return 0;
}

void ft_free_map(char **map, int height)
{
    int i = 0;
    while (i < height)
    {
        free(map[i]);
        i++;
    }
    free(map);
}

int ft_check_map_border(const char *filename)
{
    int height, width;
    char **map = ft_get_map_lines(filename, &height, &width);
    if (!map)
        return 1;
    if (ft_check_floor_border(map, height, width))
    {
        ft_free_map(map, height);
        return 1;
    }
    ft_free_map(map, height);
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
        ft_check_map_player_count(argv[1]) ||
        ft_check_map_border(argv[1]))
        return 1;
    //new_window(&game, argv[1]);
    return 0;
}