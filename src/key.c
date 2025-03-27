/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbany <mbany@student.42warsaw.pl>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 18:21:28 by mbany             #+#    #+#             */
/*   Updated: 2025/03/23 16:06:57 by mbany            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
int mouse_move(int x, int y, t_game *game)
{
	printf("Mouse moved: x = %d, y = %d\n", x, y);
    static int prev_x = WIDTH / 2; // Środek okna
    float angle_speed = 0.005;

    (void)y; // Ignorujemy ruch w osi Y

    // Oblicz różnicę pozycji kursora w osi X
    int delta_x = x - prev_x;

    // Zaktualizuj kąt gracza
    game->player.angle += delta_x * angle_speed;

    // Normalizacja kąta
    if (game->player.angle < 0)
        game->player.angle += 2 * PI;
    if (game->player.angle >= 2 * PI)
        game->player.angle -= 2 * PI;

    // Ustaw kursor na środku okna
    mlx_mouse_move(game->mlx, game->win, WIDTH / 2, HEIGHT / 2);
	prev_x = WIDTH / 2; // Zresetuj poprzednią pozycję kursora

    return (0);
}
*/

void	rotate_player(t_player *player)
{
	float	angle_speed;	

	angle_speed = 0.015;
	if (player->angle < 0)
		player->angle += 2 * PI;
	if (player->angle >= 2 * PI)
		player->angle -= 2 * PI;
		
	if (player->rotate_right)
		player->angle += angle_speed;
	if (player->rotate_left)
		player->angle -= angle_speed;
}
int	key_down(int key, t_game *game)
{
	if (key == ESC_KEY)
	{
		close_game(game);
		exit(0);
	}
	if (key == S_KEY)
		game->player.key_down = true;
	if (key == W_KEY)
		game->player.key_up = true;
	if (key == LEFT_ARROW_KEY)
		game->player.rotate_left = true;
	if (key == D_KEY)
		game->player.key_right = true;
	if (key == RIGHT_ARROW_KEY)
		game->player.rotate_right = true;
	if (key == A_KEY)
		game->player.key_left = true;
	return (0);
}

int	key_up(int key, t_player *player)
{
	if (key == LEFT_ARROW_KEY)
		player->rotate_left = false;
	if (key == RIGHT_ARROW_KEY)
		player->rotate_right = false;
	if (key == A_KEY)
		player->key_left = false;
	if (key == D_KEY)
		player->key_right = false;
	if (key == W_KEY)
		player->key_up = false;
	if (key == S_KEY)
		player->key_down = false;
	return (0);
}


void	calc_new_pos(t_player *player, int *new_x, int *new_y, int speed)
{
	float	cos_angle;
	float	sin_angle;

	cos_angle = cos(player->angle);
	sin_angle = sin(player->angle);
	if (player->key_up)
	{
		*new_x += cos_angle * speed;
		*new_y += sin_angle * speed;
	}
	if (player->key_down)
	{
		*new_x -= cos_angle * speed;
		*new_y -= sin_angle * speed;
	}
	if (player->key_left)
	{
		*new_x += sin_angle * speed;
		*new_y -= cos_angle * speed;
	}
	if (player->key_right)
	{
		*new_x -= sin_angle * speed;
		*new_y += cos_angle * speed;
	}
}

void	move_player(t_player *player, t_game *game)
{
	float	speed;
	int	new_x;
	int	new_y;

	new_x = player->x;
	new_y = player->y;
	speed = 2.1;
	calc_new_pos(player, &new_x, &new_y, speed);
	if (!touch(new_x, player->y, game))
		player->x = new_x;
	if (!touch(player->x, new_y, game))
		player->y = new_y;
}