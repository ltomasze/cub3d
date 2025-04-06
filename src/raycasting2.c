/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbany <mbany@student.42warsaw.pl>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 12:40:28 by mbany             #+#    #+#             */
/*   Updated: 2025/04/06 15:46:33 by mbany            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	calc_delta_dist(t_ray *ray)
{
	if (ray->raydirx == 0)
		ray->deltadistx = 1e10f;
	else
		ray->deltadistx = fabsf(1.0f / ray->raydirx);
	if (ray->raydiry == 0)
		ray->deltadisty = 1e10f;
	else
		ray->deltadisty = fabsf(1.0f / ray->raydiry);
}

void	perform_dda(t_ray *ray, t_game *game)
{
	ray->hit = 0;
	while (!ray->hit)
	{
		if (ray->sidedistx < ray->sidedisty)
		{
			ray->sidedistx += ray->deltadistx;
			ray->mapx += ray->stepx;
			ray->side = 0;
		}
		else
		{
			ray->sidedisty += ray->deltadisty;
			ray->mapy += ray->stepy;
			ray->side = 1;
		}
		if (game->map[ray->mapy][ray->mapx] == '1')
			ray->hit = 1;
	}
}
