/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting copy.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbany <mbany@student.42warsaw.pl>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 12:40:28 by mbany             #+#    #+#             */
/*   Updated: 2025/03/22 13:52:49 by mbany            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// Oblicza wektor promienia dla danego piksela
static  void    calculate_ray(int x, int w, double dirX, double dirY,double planeX, double planeY,double *cameraX, double *rayDirX, double *rayDirY)
{
    *cameraX = 2 * x / (double)w - 1;
    *rayDirX = dirX + planeX * *cameraX;
    *rayDirY = dirY + planeY * *cameraX;
}

// Oblicza odległości delta dla osi X i Y
static void compute_delta_distances(double rayDirX, double rayDirY, double *deltaDistX, double *deltaDistY)
{
    *deltaDistX = fabs(1 / rayDirX);
    *deltaDistY = fabs(1 / rayDirY);
}

// Ustawia kierunek kroku i początkową odległość boczną
static void compute_step_sideDist(double pos, int map,
                                  double rayDir, double deltaDist,
                                  int *step, double *sideDist)
{
if (rayDir < 0)
{
    *step = -1;
    *sideDist = (pos - map) * deltaDist;
}
else
{
    *step = 1;
    *sideDist = (map + 1.0 - pos) * deltaDist;
}
}

// Przeprowadza algorytm DDA, aż do trafienia w ścianę
static void perform_dda(t_game *game, int *mapX, int *mapY,
                        double *sideDistX, double *sideDistY,
                        double deltaDistX, double deltaDistY,
                        int stepX, int stepY, int *side)
{
    int hit = 0;
    while (hit == 0)
    {
        if (*sideDistX < *sideDistY)
        {
            *sideDistX += deltaDistX;
            *mapX += stepX;
            *side = 0;
        }
        else
        {
            *sideDistY += deltaDistY;
            *mapY += stepY;
            *side = 1;
        }
        if (game->map[*mapY][*mapX] == '1')
            hit = 1;
    }
}

// Oblicza odległość od ściany
static double compute_perp_wall_dist(double posX, double posY,
                                       int mapX, int mapY,
                                       int stepX, int stepY,
                                       double rayDirX, double rayDirY,
                                       int side)
{
    if (side == 0)
        return (mapX - posX + (1 - stepX) / 2.0) / rayDirX;
    else
        return (mapY - posY + (1 - stepY) / 2.0) / rayDirY;
}

// Wybiera numer tekstury w zależności od trafionej ściany
static int get_texture_number(int side, double rayDirX, double rayDirY)
{
    int texNum;
    if (side == 1)
    {
        if (rayDirY > 0)
            texNum = 0; // prawa ściana - red_stone
        else
            texNum = 1; // lewa ściana - blue_stone
    }
    else
    {
        if (rayDirX > 0)
            texNum = 2; // przednia ściana - grey_stone
        else
            texNum = 3; // tylna ściana - color_stone
    }
    return texNum;
}

// Oblicza współrzędną X tekstury
static void compute_texture_coordinates(double posX, double posY,
                                        double perpWallDist,
                                        double rayDirX, double rayDirY,
                                        int side, int texWidth,
                                        int *texX)
{
    double wallX;
    if (side == 0)
        wallX = posY + perpWallDist * rayDirY;
    else
        wallX = posX + perpWallDist * rayDirX;
    wallX -= floor(wallX);
    *texX = (int)(wallX * (double)texWidth);
    if (side == 0 && rayDirX > 0)
        *texX = texWidth - *texX - 1;
    if (side == 1 && rayDirY < 0)
        *texX = texWidth - *texX - 1;
}

// Rysuje pionowy pasek z odpowiednią teksturą
static void draw_vertical_stripe(t_game *game, int x,
                                 int drawStart, int drawEnd,
                                 int lineHeight, int texX,
                                 int texNum, int h)
{
    char *texture_data = mlx_get_data_addr(game->textures[texNum],
                                             &game->bpp,
                                             &game->size_line,
                                             &game->endian);
    for (int y = drawStart; y < drawEnd; y++)
    {
        int d = y * 256 - h * 128 + lineHeight * 128;
        int texY = ((d * game->tex_height) / lineHeight) / 256;
        if (texY < 0 || texY >= game->tex_height)
            continue;
        int color = *(int *)(texture_data +
                             (texY * game->size_line +
                              texX * (game->bpp / 8)));
        mlx_pixel_put(game->mlx, game->win, x, y, color);
    }
}
static void	prepare_ray(t_game *game, int x, double posX, double posY,
		double dirX, double dirY, double planeX, double planeY, int w,
		double *rayDirX, double *rayDirY, int *mapX, int *mapY,
		double *deltaDistX, double *deltaDistY, int *stepX, int *stepY,
		double *sideDistX, double *sideDistY, int *side)
{
	double	cameraX;

	calculate_ray(x, w, dirX, dirY, planeX, planeY, &cameraX,
		rayDirX, rayDirY);
	*mapX = (int)posX;
	*mapY = (int)posY;
	compute_delta_distances(*rayDirX, *rayDirY, deltaDistX, deltaDistY);
	compute_step_sideDist(posX, *mapX, *rayDirX, *deltaDistX, stepX,
		sideDistX);
	compute_step_sideDist(posY, *mapY, *rayDirY, *deltaDistY, stepY,
		sideDistY);
	perform_dda(game, mapX, mapY, sideDistX, sideDistY, *deltaDistX,
		*deltaDistY, *stepX, *stepY, side);
}

static void	render_ray(t_game *game, int x, double posX, double posY,
		double rayDirX, double rayDirY, int mapX, int mapY, int stepX,
		int stepY, int side, int h)
{
	double	perpWallDist;
	int		lineHeight;
	int		drawStart;
	int		drawEnd;
	int		texNum;
	int		texX;

	perpWallDist = compute_perp_wall_dist(posX, posY, mapX, mapY, stepX,
			stepY, rayDirX, rayDirY, side);
	lineHeight = (int)(h / perpWallDist);
	drawStart = -lineHeight / 2 + h / 2;
	if (drawStart < 0)
		drawStart = 0;
	drawEnd = lineHeight / 2 + h / 2;
	if (drawEnd >= h)
		drawEnd = h - 1;
	texNum = get_texture_number(side, rayDirX, rayDirY);
	compute_texture_coordinates(posX, posY, perpWallDist, rayDirX,
		rayDirY, side, game->tex_width, &texX);
	draw_vertical_stripe(game, x, drawStart, drawEnd, lineHeight, texX,
		texNum, h);
}

void	process_ray(t_game *game, int x, double posX, double posY,
		double dirX, double dirY, double planeX, double planeY, int w, int h)
{
	double	rayDirX;
	double	rayDirY;
	int		mapX;
	int		mapY;
	double	deltaDistX;
	double	deltaDistY;
	double	sideDistX;
	double	sideDistY;
	int		stepX;
	int		stepY;
	int		side;

	prepare_ray(game, x, posX, posY, dirX, dirY, planeX, planeY, w,
		&rayDirX, &rayDirY, &mapX, &mapY, &deltaDistX, &deltaDistY,
		&stepX, &stepY, &sideDistX, &sideDistY, &side);
	render_ray(game, x, posX, posY, rayDirX, rayDirY, mapX, mapY, stepX,
		stepY, side, h);
}
void render_floor(t_game *game, int w, int h)
{
    int floor_color = 0x2F2F2F; // Ciemnoszary kolor (hex: #2F2F2F)
    for (int y = h / 2; y < h; y++) // Podłoga
    {
        for (int x = 0; x < w; x++)
        {
            mlx_pixel_put(game->mlx, game->win, x, y, floor_color);
        }
    }
}
void render_ceiling(t_game *game, int w, int h)
{
    int ceiling_color = 0x87CEEB; // Błękitny kolor (hex: #87CEEB)
    for (int y = 0; y < h / 2; y++) // Sufit
    {
        for (int x = 0; x < w; x++)
        {
            mlx_pixel_put(game->mlx, game->win, x, y, ceiling_color);
        }
    }
}

void	draw_3d_view(t_game *game)
{
    int w = 1440;
    int h = 720;
    double posX = game->player_x;
    double posY = game->player_y;
    double dirX = game->dirX;
    double dirY = game->dirY;
    double planeX = game->planeX;
    double planeY = game->planeY;
    int x = 0;
    render_ceiling(game, w, h);
    render_floor(game, w, h);
    while (x < w)
        {
        process_ray(game, x, posX, posY, dirX, dirY, planeX, planeY, w, h);
        x++;
        }
}
