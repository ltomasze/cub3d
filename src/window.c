/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbany <mbany@student.42warsaw.pl>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 18:19:57 by mbany             #+#    #+#             */
/*   Updated: 2025/03/23 14:24:39 by mbany            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

bool	touch(float px, float py, t_game *game)
{
	int	x1;
	int	y1;
	int	mapx;
	int	mapy;

	x1 = (int)((px + COLLISION_RADIUS) / BLOCK);
	y1 = (int)((py + COLLISION_RADIUS) / BLOCK);
	mapy = (int)((py - COLLISION_RADIUS) / BLOCK);
	while (mapy <= y1)
	{
		mapx = (int)((px - COLLISION_RADIUS) / BLOCK);
		while (mapx <= x1)
		{
			if (mapy < 0 || game->map[mapy] == NULL || mapx < 0
				|| game->map[mapy][mapx] == '\0'
				|| game->map[mapy][mapx] == '1')
				return (true);
			mapx++;
		}
		mapy++;
	}
	return (false);
}

void	put_pixel(int x, int y, int color, t_game *game)
{
	int	index;

	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	index = y * game->line_size + x * game->bpp / 8;
	game->data[index] = color & 0xFF;
	game->data[index + 1] = (color >> 8) & 0xFF;
	game->data[index + 2] = (color >> 16) & 0xFF;
}

void	clear_image(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			put_pixel(x, y, 0, game);
			x++;
		}
		y++;
	}
}
void	draw_floor_ceiling(t_game *game)
{
	int	x;
	int	y;	

	y = 0;
	while (y < HEIGHT / 2)
	{
		x = 0;
		while (x < WIDTH)
		{
			put_pixel(x, y, CELING, game);
			x++;
		}
		y++;
	}
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			put_pixel(x, y, FLOOR, game);
			x++;
		}
		y++;
	}
}



