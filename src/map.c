/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbany <mbany@student.42warsaw.pl>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 18:19:05 by mbany             #+#    #+#             */
/*   Updated: 2025/03/25 19:16:26 by mbany            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void draw_map(t_game *game)
{
    int x, y;
    int tile_size = BLOCK / 8; // Rozmiar kafelka na minimapie (1/8 rozmiaru bloku)
    int offset_x = 10;        // Przesunięcie minimapy od lewej krawędzi
    int offset_y = 10;        // Przesunięcie minimapy od górnej krawędzi

    // Iteracja po mapie
    for (y = 0; game->map[y] != NULL; y++)
    {
        for (x = 0; game->map[y][x] != '\0'; x++)
        {
            int color = CELING; // Domyślny kolor (czarny)

            if (game->map[y][x] == '1') // Ściana
                color = 0xFF0000; // Czerwony
            else if (game->map[y][x] == '0') // Puste miejsce
                color = FLOOR; // Szary

            // Rysowanie kafelka na obrazie
            for (int i = 0; i < tile_size; i++)
            {
                for (int j = 0; j < tile_size; j++)
                {
                    put_pixel(offset_x + x * tile_size + i,
                              offset_y + y * tile_size + j,
                              color, game);
                }
            }
        }
    }

    // Rysowanie gracza na minimapie
    int player_tile_x = offset_x + (game->player.x / BLOCK) * tile_size;
    int player_tile_y = offset_y + (game->player.y / BLOCK) * tile_size;

    for (int i = 0; i < tile_size; i++)
    {
        for (int j = 0; j < tile_size; j++)
        {
            put_pixel(player_tile_x + i,
                      player_tile_y + j,
                      0x00FF00, game); // Zielony kolor dla gracza
        }
    }
}

