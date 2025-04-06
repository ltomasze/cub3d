/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltomasze <ltomasze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 17:41:58 by ltomasze          #+#    #+#             */
/*   Updated: 2025/04/06 17:42:27 by ltomasze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	set_player_angle_and_position(t_game *game, int x, int y, char direction)
{
	game->player.x = x * BLOCK + BLOCK / 2;
	game->player.y = y * BLOCK + BLOCK / 2;
	if (direction == 'N')
		game->player.angle = 3 * PI / 2;
	else if (direction == 'S')
		game->player.angle = PI / 2;
	else if (direction == 'E')
		game->player.angle = 0;
	else if (direction == 'W')
		game->player.angle = PI;
	else
		return (0);
	game->map[y][x] = '0';
	return (1);
}

void	set_player_position(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == 'N' || game->map[y][x] == 'S' ||
				game->map[y][x] == 'E' || game->map[y][x] == 'W')
			{
				if (set_player_angle_and_position(game, x, y, game->map[y][x]))
					return ;
			}
			x++;
		}
		y++;
	}
}

void	init_player(t_player *player)
{
	player->angle = PI;
	player->key_up = false;
	player->key_down = false;
	player->key_left = false;
	player->key_right = false;
	player->rotate_left = false;
	player->rotate_right = false;
}
