/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbany <mbany@student.42warsaw.pl>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 12:40:28 by mbany             #+#    #+#             */
/*   Updated: 2025/03/25 19:27:06 by mbany            ###   ########.fr       */
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

float	compute_corrected_dist(t_ray *ray, t_player *player, float ray_angle)
{
	float	perpwalldist;
	float	distance_in_pixels;
	float	angle_diff;

	if (ray->side == 0)
	{
		perpwalldist = (ray->mapx - (player->x / BLOCK)
				+ (1 - ray->stepx) / 2.0f) / ray->raydirx;
	}
	else
	{
		perpwalldist = (ray->mapy - (player->y / BLOCK)
				+ (1 - ray->stepy) / 2.0f) / ray->raydiry;
	}
	distance_in_pixels = perpwalldist * BLOCK;
	angle_diff = ray_angle - player->angle;
	distance_in_pixels *= cosf(angle_diff);
	return (distance_in_pixels);
}

void	draw_column(t_game *game, t_tex *texture, int column, t_line *line)
{
	float	step;
	float	tex_pos;
	int		y;
	int		tex_y;
	int		color;

	step = (float)texture->h / (float)line->wall_h;
	tex_pos = (line->start_y - HEIGHT / 2 + line->wall_h / 2) * step;
	y = line->start_y;
	while (y < line->end_y)
	{
		tex_y = (int)tex_pos & (texture->h - 1);
		color = *(int *)(texture->data + (tex_y * texture->line_size
					+ line->tex_x * (texture->bpp / 8)));
		put_pixel(column, y, color, game);
		tex_pos += step;
		y++;
	}
}

void	calc_line(t_player *player, t_ray *ray, t_tex *tex, t_line *line)
{
	float	wall_x;

	line->wall_h = (int)(BLOCK * HEIGHT / line->dist);
	line->start_y = (HEIGHT - line->wall_h) / 2;
	line->end_y = line->start_y + line->wall_h;
	if (line->start_y < 0)
		line->start_y = 0;
	if (line->end_y >= HEIGHT)
		line->end_y = HEIGHT - 1;
	if (ray->side == 0)
		wall_x = (player->y / BLOCK) + ((line->dist / BLOCK)
				* ray->raydiry);
	else
		wall_x = (player->x / BLOCK) + ((line->dist / BLOCK)
				* ray->raydirx);
	wall_x = wall_x - floor(wall_x);
	line->tex_x = (int)(wall_x * tex->w);
	if (line->tex_x < 0)
		line->tex_x = 0;
	if (line->tex_x >= tex->w)
		line->tex_x = tex->w - 1;
}

void	init_sidedist_step(t_ray *ray, t_player *player)
{
	if (ray->raydirx < 0)
	{
		ray->stepx = -1;
		ray->sidedistx = ((player->x / BLOCK) - ray->mapx)
			* ray->deltadistx;
	}
	else
	{
		ray->stepx = 1;
		ray->sidedistx = ((ray->mapx + 1) - (player->x / BLOCK))
			* ray->deltadistx;
	}
	if (ray->raydiry < 0)
	{
		ray->stepy = -1;
		ray->sidedisty = ((player->y / BLOCK) - ray->mapy)
			* ray->deltadisty;
	}
	else
	{
		ray->stepy = 1;
		ray->sidedisty = ((ray->mapy + 1) - (player->y / BLOCK))
			* ray->deltadisty;
	}
}

void	draw_line(t_player *player, t_game *game, float ray_angle, int column)
{
	t_ray		ray;
	t_line		line;
	t_tex		*texture;

	init_ray(&ray, player, ray_angle);
	calc_delta_dist(&ray);
	init_sidedist_step(&ray, player);
	perform_dda(&ray, game);
	texture = choose_texture(&ray, game);
	if (!texture || !texture->data)
		return ;
	line.dist = compute_corrected_dist(&ray, player, ray_angle);
	calc_line(player, &ray, texture, &line);
	draw_column(game, texture, column, &line);
}