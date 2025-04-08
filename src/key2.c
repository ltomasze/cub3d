/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbany <mbany@student.42warsaw.pl>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 18:21:28 by mbany             #+#    #+#             */
/*   Updated: 2025/04/08 18:38:01 by mbany            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	mouse_move(int x, int y, t_game *game)
{
	int	delta_x;

	delta_x = x - game->prev_mouse_x;
	game->player.angle += 0.02 * delta_x;
	if (game->player.angle < 0)
		game->player.angle += 2 * PI;
	if (game->player.angle >= 2 * PI)
		game->player.angle -= 2 * PI;
	game->prev_mouse_x = x;
	game->prev_mouse_y = y;
	return (0);
}
