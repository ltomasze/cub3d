/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltomasze <ltomasze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 15:11:49 by mbany             #+#    #+#             */
/*   Updated: 2025/04/06 17:42:44 by ltomasze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_ray(t_ray *ray, t_player *player, float ray_angle)
{
	ray->raydirx = cosf(ray_angle);
	ray->raydiry = sinf(ray_angle);
	ray->mapx = (int)(player->x / BLOCK);
	ray->mapy = (int)(player->y / BLOCK);
}

void	init_game_struct(t_game *game)
{
	game->mlx = NULL;
	game->win = NULL;
	game->img = NULL;
	game->data = NULL;
	game->map = game->config.map;
	game->copy_map = NULL;
	game->map = game->config.map;
	game->color_floor = game->config.floor_color;
	game->color_ceiling = game->config.ceiling_color;
	game->n_tex_path = game->config.textures[0];
	game->s_tex_path = game->config.textures[1];
	game->w_tex_path = game->config.textures[2];
	game->e_tex_path = game->config.textures[3];
	game->n_path = 0;
	game->s_path = 0;
	game->w_path = 0;
	game->e_path = 0;
}

int	init_game(t_game *game, char *file)
{
	init_game_struct(game);
	init_player(&game->player);
	game->fd = open(file, O_RDONLY);
	set_player_position(game);
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "cub3d");
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->data = mlx_get_data_addr(game->img, &game->bpp,
			&game->line_size, &game->endian);
	if (!load_all_textures(game))
		return (error(INVALID_FILE, game));
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	mlx_mouse_move(game->mlx, game->win, WIDTH / 2, HEIGHT / 2);
	return (1);
}
