/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_border.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltomasze <ltomasze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 18:19:41 by ltomasze          #+#    #+#             */
/*   Updated: 2025/03/20 11:11:40 by ltomasze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	**ft_get_map_lines(const char *filename, int *height, int *width)
{
	int		fd;
	char	**map;

	fd = ft_open_file(filename);
	if (fd == -1)
		return (NULL);
	map = ft_process_map_lines(fd, height, width);
	close(fd);
	return (map);
}

int	ft_check_floor_border(char **map, int height, int max_width)
{
	int	y;
	int	row_len;
	int	x;

	y = 0;
	(void)max_width;
	while (y < height)
	{
		row_len = ft_strlen(map[y]);
		x = 0;
		while (x < row_len)
		{
			if (map[y][x] == '0' && ft_check_nghs_floor(map, height, y, x))
				return (1);
			x++;
		}
		y++;
	}
	return (0);
}

int	ft_check_player_border(char **map, int height)
{
	int	y;
	int	row_len;
	int	x;

	y = 0;
	while (y < height)
	{
		x = 0;
		row_len = ft_strlen(map[y]);
		while (x < row_len)
		{
			if (map[y][x] == 'N' || map[y][x] == 'W' ||
			map[y][x] == 'E' || map[y][x] == 'S')
			{
				if (ft_check_nghs_player(map, height, y, x))
					return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

void	ft_free_map(char **map, int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

int	ft_check_map_border(const char *filename)
{
	int		height;
	int		width;
	char	**map;

	map = ft_get_map_lines(filename, &height, &width);
	if (!map)
		return (1);
	if (ft_check_floor_border(map, height, width)
		|| ft_check_player_border(map, height))
	{
		ft_free_map(map, height);
		return (1);
	}
	ft_free_map(map, height);
	return (0);
}
