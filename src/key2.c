/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbany <mbany@student.42warsaw.pl>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 18:21:28 by mbany             #+#    #+#             */
/*   Updated: 2025/04/06 15:34:16 by mbany            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	mouse_move(int x, int y, t_game *game)
{
	int	center_x;

	center_x = WIDTH / 2;
	(void)y;
	if (x < center_x)
		game->player.angle -= 0.002 * (center_x - x);
	else if (x > center_x)
		game->player.angle += 0.002 * (x - center_x);
	if (game->player.angle < 0)
		game->player.angle += 2 * PI;
	if (game->player.angle >= 2 * PI)
		game->player.angle -= 2 * PI;
	mlx_mouse_move(game->mlx, game->win, center_x, HEIGHT / 2);
	return (0);
}
