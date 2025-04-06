/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbany <mbany@student.42warsaw.pl>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 18:19:05 by mbany             #+#    #+#             */
/*   Updated: 2025/03/29 17:48:49 by mbany            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	draw_tile(int x, int y, t_draw_data *data, t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->tile_size)
	{
		j = 0;
		while (j < data->tile_size)
		{
			put_pixel(x + i, y + j, data->color, game);
			j++;
		}
		i++;
	}
}

static void	draw_map_tiles_helper(t_game *game, t_draw_data *data, int x, int y)
{
	if (game->map[y][x] == '1')
		data->color = 0xff0000;
	else if (game->map[y][x] == '0')
		data->color = game->color_floor;
	else
		data->color = game->color_ceiling;
	draw_tile(data->offset_x + x * data->tile_size,
		data->offset_y + y * data->tile_size, data, game);
}

static void	draw_map_tiles(t_game *game, t_draw_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (game->map[y] != NULL)
	{
		x = 0;
		while (game->map[y][x] != '\0')
		{
			draw_map_tiles_helper(game, data, x, y);
			x++;
		}
		y++;
	}
}

static void	draw_player_on_map(t_game *game, t_draw_data *data)
{
	int	player_tile_x;
	int	player_tile_y;

	player_tile_x = data->offset_x + (game->player.x / BLOCK) * data->tile_size;
	player_tile_y = data->offset_y + (game->player.y / BLOCK) * data->tile_size;
	data->color = 0x000000;
	draw_tile(player_tile_x, player_tile_y, data, game);
}

void	draw_map(t_game *game)
{
	t_draw_data	data;

	data.tile_size = BLOCK / 8;
	data.offset_x = 10;
	data.offset_y = 10;
	draw_map_tiles(game, &data);
	draw_player_on_map(game, &data);
}
