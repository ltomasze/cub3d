/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltomasze <ltomasze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 15:11:49 by mbany             #+#    #+#             */
/*   Updated: 2025/04/06 14:17:37 by ltomasze         ###   ########.fr       */
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

int ft_map_max_height(const char **map) 
{
    int max_height = 0;
    while (map[max_height] != NULL) 
        max_height++;
    return max_height;
}

int	ft_map_max_width(const char **map, int max_height, int *max_width)
{
	*max_width = 0;
    int i = 0;
    while (i < max_height)
	{
        int current_width = strlen(map[i]);
        if (current_width > *max_width)
            *max_width = current_width;
        i++;
    }
	return *max_width;
}

void	init_player(t_player *player)
{
	player->x = 587;
	player->y = 166;
	player->angle = PI / 1.8;
	player->key_up = false;
	player->key_down = false;
	player->key_left = false;
	player->key_right = false;
	player->rotate_left = false;
	player->rotate_right = false;
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
	/////////////////////////////////////////
	// if (!parsing(game))
	// 	return (error(INVALID_MAP, game));
	int map_height = ft_map_max_height((const char **)game->map);
    int map_width = ft_map_max_width((const char **)game->map, map_height, &map_width);
    printf("Map height: %d, Map width: %d\n", map_height, map_width);
	
	/////////////////////////////////////////
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "cub3d");
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->data = mlx_get_data_addr(game->img, &game->bpp,
			&game->line_size, &game->endian);
	if (!load_all_textures(game))
		return (error(INVALID_FILE, game));
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (1);
}
