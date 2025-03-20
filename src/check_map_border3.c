/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_border3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltomasze <ltomasze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 11:03:15 by ltomasze          #+#    #+#             */
/*   Updated: 2025/03/20 11:11:33 by ltomasze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	ft_check_ngh_floor(t_pos_in_map pos)
{
	int		ny;
	int		nx;
	char	neighbor;
	int		neighbor_len;

	ny = pos.y + pos.dy;
	nx = pos.x + pos.dx;
	neighbor = ' ';
	if (ny >= 0 && ny < pos.height)
	{
		neighbor_len = ft_strlen(pos.map[ny]);
		if (nx >= 0 && nx < neighbor_len)
			neighbor = pos.map[ny][nx];
	}
	return (neighbor);
}

int	ft_check_dx(t_pos_in_map pos)
{
	char	neighbor;
	int		dx;

	dx = -1;
	while (dx <= 1)
	{
		if (!(pos.dy == 0 && dx == 0))
		{
			pos.dx = dx;
			neighbor = ft_check_ngh_floor(pos);
			if (neighbor != '1' && neighbor != '0' && neighbor != 'N'
				&& neighbor != 'S' && neighbor != 'W' && neighbor != 'E')
			{
				printf("Error: Missing border for floor\n");
				return (1);
			}
		}
		dx++;
	}
	return (0);
}

int	ft_check_nghs_floor(char **map, int height, int y, int x)
{
	int				dy;
	t_pos_in_map	pos;

	dy = -1;
	while (dy <= 1)
	{
		pos.y = y;
		pos.x = x;
		pos.dy = dy;
		pos.height = height;
		pos.map = map;
		if (ft_check_dx(pos))
			return (1);
		dy++;
	}
	return (0);
}

char	ft_get_ngh_player(char **map, int height, int ny, int nx)
{
	int	neighbor_len;

	if (ny < 0 || ny >= height)
		return (' ');
	neighbor_len = ft_strlen(map[ny]);
	if (nx < 0 || nx >= neighbor_len)
		return (' ');
	return (map[ny][nx]);
}

int	ft_check_nghs_player(char **map, int height, int y, int x)
{
	int		dy;
	int		dx;
	char	neighbor;

	dy = -1;
	while (dy <= 1)
	{
		dx = -1;
		while (dx <= 1)
		{
			if (!(dy == 0 && dx == 0))
			{
				neighbor = ft_get_ngh_player(map, height, y + dy, x + dx);
				if (neighbor != '0' && neighbor != '1')
				{
					printf("Error: Player is not closed at (%d, %d)\n", y, x);
					return (1);
				}
			}
			dx++;
		}
		dy++;
	}
	return (0);
}
