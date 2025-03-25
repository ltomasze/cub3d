/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltomasze <ltomasze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 16:56:59 by ltomasze          #+#    #+#             */
/*   Updated: 2025/03/25 17:30:34 by ltomasze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	ft_count_map_lines(const char *filename)
{
	int		fd;
	char	*line;
	int		row_count;

	row_count = 0;
	fd = ft_open_file(filename);
	if (fd == -1)
		return (-1);
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (ft_is_map_line(line))
			row_count++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (row_count);
}

void	ft_free_map_for_parse(t_config *config)
{
	int	i;

	i = 0;
	while (config->map[i] != NULL)
	{
		free(config->map[i]);
		i++;
	}
	free(config->map);
	config->map = NULL;
}

int	ft_init_map(t_config *config, int map_lines)
{
	config->map = malloc(sizeof(char *) * (map_lines + 1));
	if (config->map == NULL)
	{
		printf("Error: Memory allocation failed for map\n");
		return (1);
	}
	ft_memset(config->map, 0, sizeof(char *) * (map_lines + 1));
	return (0);
}

void	ft_load_map(const char *filename, t_config *config)
{
	int		fd;
	char	*line;
	int		row;

	fd = ft_open_file(filename);
	if (fd == -1)
		return ;
	line = get_next_line(fd);
	row = 0;
	while (line != NULL)
	{
		if (ft_is_map_line(line))
		{
			config->map[row] = ft_strdup(line);
			row++;
		}
		free(line);
		line = get_next_line(fd);
	}
	config->map[row] = NULL;
	close(fd);
}

void	ft_parse_map(const char *filename, t_config *config)
{
	int	row;
	int	map_lines;

	row = 0;
	if (config->map != NULL)
		ft_free_map_for_parse(config);
	map_lines = ft_count_map_lines(filename);
	if (map_lines == -1)
	{
		printf("Error: Could not count map rows\n");
		return ;
	}
	if (ft_init_map(config, map_lines))
		return ;
	ft_load_map(filename, config);
}
