/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kay.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbany <mbany@student.42warsaw.pl>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 18:21:28 by mbany             #+#    #+#             */
/*   Updated: 2025/03/09 15:49:27 by mbany            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int handle_key(int key, t_game *game)
{
    int new_x = game->player_x;
    int new_y = game->player_y;

    if (key == ESC_KEY)
        clean_exit(game);
    else if (key == W_KEY)
        new_y -= game->move_speed;
    else if (key == S_KEY)
        new_y += game->move_speed;
    else if (key == A_KEY)
        new_x -= game->move_speed;
    else if (key == D_KEY)
        new_x += game->move_speed;

    // Check for collision with walls
    if (game->map[new_y][new_x] != '1')
    {
        game->player_x = new_x;
        game->player_y = new_y;
    }

    draw_3d_view(game);
    // draw_map(game);
    return (0);
}