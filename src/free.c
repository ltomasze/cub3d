/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbany <mbany@student.42warsaw.pl>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 18:23:41 by mbany             #+#    #+#             */
/*   Updated: 2025/03/30 17:19:02 by mbany            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_texture(t_game *game, t_tex *texture)
{
	if (texture->img)
		mlx_destroy_image(game->mlx, texture->img);
}

// void	free_texture_paths(t_game *game)
// {
// 	if (game->w_tex_path)
// 		free(game->w_tex_path);
// 	if (game->n_tex_path)
// 		free(game->n_tex_path);
// 	if (game->e_tex_path)
// 		free(game->e_tex_path);
// 	if (game->s_tex_path)
// 		free(game->s_tex_path);
// }

void	free_map(char **map)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	free_all_textures(t_game *game)
{
	free_texture(game, &game->n_tex);
	free_texture(game, &game->s_tex);
	free_texture(game, &game->w_tex);
	free_texture(game, &game->e_tex);
}

