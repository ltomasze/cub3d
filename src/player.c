/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbany <mbany@student.42warsaw.pl>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 15:10:10 by mbany             #+#    #+#             */
/*   Updated: 2025/03/16 15:38:35 by mbany            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void move_forward(t_game *game)
{
    double new_x = game->player_x + game->player_dir_x * game->move_speed;
    double new_y = game->player_y + game->player_dir_y * game->move_speed;

    // Sprawdź kolizję z mapą
    if (game->map[(int)new_y][(int)game->player_x] != '1')
        game->player_y = new_y;
    if (game->map[(int)game->player_y][(int)new_x] != '1')
        game->player_x = new_x;
}

void move_backward(t_game *game)
{
    double new_x = game->player_x - game->player_dir_x * game->move_speed;
    double new_y = game->player_y - game->player_dir_y * game->move_speed;

    // Sprawdź kolizję z mapą
    if (game->map[(int)new_y][(int)game->player_x] != '1')
        game->player_y = new_y;
    if (game->map[(int)game->player_y][(int)new_x] != '1')
        game->player_x = new_x;
}
void strafe_left(t_game *game)
{
    double new_x = game->player_x - game->plane_x * game->move_speed;
    double new_y = game->player_y - game->plane_y * game->move_speed;

    // Sprawdź kolizję z mapą
    if (game->map[(int)new_y][(int)game->player_x] != '1')
        game->player_y = new_y;
    if (game->map[(int)game->player_y][(int)new_x] != '1')
        game->player_x = new_x;
}

void strafe_right(t_game *game)
{
    double new_x = game->player_x + game->plane_x * game->move_speed;
    double new_y = game->player_y + game->plane_y * game->move_speed;

    // Sprawdź kolizję z mapą
    if (game->map[(int)new_y][(int)game->player_x] != '1')
        game->player_y = new_y;
    if (game->map[(int)game->player_y][(int)new_x] != '1')
        game->player_x = new_x;
}


void rotate_left(t_game *game)
{
    double old_dir_x = game->player_dir_x;
    game->player_dir_x = game->player_dir_x * cos(-game->rot_speed) - game->player_dir_y * sin(-game->rot_speed);
    game->player_dir_y = old_dir_x * sin(-game->rot_speed) + game->player_dir_y * cos(-game->rot_speed);

    double old_plane_x = game->plane_x;
    game->plane_x = game->plane_x * cos(-game->rot_speed) - game->plane_y * sin(-game->rot_speed);
    game->plane_y = old_plane_x * sin(-game->rot_speed) + game->plane_y * cos(-game->rot_speed);
}

void rotate_right(t_game *game)
{
    double old_dir_x = game->player_dir_x;
    game->player_dir_x = game->player_dir_x * cos(game->rot_speed) - game->player_dir_y * sin(game->rot_speed);
    game->player_dir_y = old_dir_x * sin(game->rot_speed) + game->player_dir_y * cos(game->rot_speed);

    double old_plane_x = game->plane_x;
    game->plane_x = game->plane_x * cos(game->rot_speed) - game->plane_y * sin(game->rot_speed);
    game->plane_y = old_plane_x * sin(game->rot_speed) + game->plane_y * cos(game->rot_speed);
}