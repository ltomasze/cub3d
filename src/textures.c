/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbany <mbany@student.42warsaw.pl>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 18:42:26 by mbany             #+#    #+#             */
/*   Updated: 2025/03/23 14:49:26 by mbany            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
void load_textures(t_game *game)
{
    game->textures[0] = mlx_xpm_file_to_image(game->mlx, "textures/mossy.xpm", &game->tex_width, &game->tex_height);
	if (!game->textures[0])
        exit(printf("Error: failed to load texture1\n"));
    game->textures[1] = mlx_xpm_file_to_image(game->mlx, "textures/color_stone.xpm", &game->tex_width, &game->tex_height);
	if (!game->textures[1])
        exit(printf("Error: failed to load texture2\n"));
    game->textures[2] = mlx_xpm_file_to_image(game->mlx, "textures/red_brick.xpm", &game->tex_width, &game->tex_height);
	if (!game->textures[2])
        exit(printf("Error: failed to load texture3\n"));
    game->textures[3] = mlx_xpm_file_to_image(game->mlx, "textures/purple_stone.xpm", &game->tex_width, &game->tex_height);
	if (!game->textures[3])
        printf("Error: failed to load texture4\n"), exit(1);
}
*/

int	load_texture(t_game *game, t_tex *tex, char *path)
{
	tex->img = mlx_xpm_file_to_image(game->mlx, path,
			&tex->w, &tex->h);
	if (!tex->img)
		return (0);
	tex->data = mlx_get_data_addr(tex->img, &tex->bpp,
			&tex->line_size, &tex->endian);
	return (1);
}

int	load_all_textures(t_game *game)
{
	if (!load_texture(game, &game->n_tex, game->n_tex_path))
		return (error(INVALID_FILE, game));
	if (!load_texture(game, &game->s_tex, game->s_tex_path))
		return (error(INVALID_FILE, game));
	if (!load_texture(game, &game->w_tex, game->w_tex_path))
		return (error(INVALID_FILE, game));
	if (!load_texture(game, &game->e_tex, game->e_tex_path))
		return (error(INVALID_FILE, game));
	return (1);
}

t_tex	*choose_texture(t_ray *ray, t_game *game)
{
	if (ray->side == 0)
	{
		if (ray->raydirx < 0)
			return (&game->w_tex);
		else
			return (&game->e_tex);
	}
	else
	{
		if (ray->raydiry < 0)
			return (&game->n_tex);
		else
			return (&game->s_tex);
	}
}

