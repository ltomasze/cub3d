/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbany <mbany@student.42warsaw.pl>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 14:29:35 by mbany             #+#    #+#             */
/*   Updated: 2025/03/22 14:39:38 by mbany            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	error_clean_up(t_game *game)
{
	free_map(game->map);
	free_map(game->copy_map);
	free_texture_paths(game);
}

int	error(t_error code, t_game *game)
{
	if (code == NO_FILE)
		printf("please provide a file you pookie\n");
	else
	{
		if (game && game->mlx)
			close_game(game);
		if (code == INVALID_FILE)
			printf("invalid file\n");
		if (code == INVALID_INPUT)
		{
			error_clean_up(game);
			printf("invalid input - check the parameters!!");
		}
		else if (code == INVALID_SPAWN)
		{
			printf("invalid spawn point\n");
		}
		else if (code == INVALID_MAP)
		{
			error_clean_up(game);
			printf("invalid map - make sure that it's enclosed in walls\n");
		}
	}
	return (0);
}