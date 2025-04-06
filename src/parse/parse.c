/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltomasze <ltomasze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 16:29:53 by ltomasze          #+#    #+#             */
/*   Updated: 2025/04/06 17:59:27 by ltomasze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	ft_get_texture_index(char *line)
{
	if (ft_strncmp(line, "NO", 2) == 0)
		return (0);
	if (ft_strncmp(line, "SO", 2) == 0)
		return (1);
	if (ft_strncmp(line, "WE", 2) == 0)
		return (2);
	if (ft_strncmp(line, "EA", 2) == 0)
		return (3);
	return (-1);
}

void	ft_parse_texture(char *line, t_config *config)
{
	char	*path;
	int		index;
	int		len;

	while (*line == ' ' || *line == '\t')
		line++;
	index = ft_get_texture_index(line);
	if (index == -1)
		return ;
	line += 2;
	while (*line == ' ' || *line == '\t')
		line++;
	path = ft_strdup(line);
	if (path)
	{
		len = ft_strlen(path);
		while (len > 0 && (path[len - 1] == ' ' || path[len - 1] == '\t'
				|| path[len - 1] == '\n'))
		{
			path[len - 1] = '\0';
			len--;
		}
		config->textures[index] = path;
	}
}

int	ft_extract_rgb(char *line, int *r, int *g, int *b)
{
	int	values[3];
	int	i;

	i = 0;
	while (i < 3)
	{
		line = ft_skip_whitespaces(line);
		if (!ft_isdigit(*line))
			return (1);
		values[i] = ft_atoi(line);
		while (*line && *line != ',' && *line != ' ' && *line != '\t')
			line++;
		if (i < 2)
		{
			line = ft_skip_whitespaces(line);
			if (*line != ',')
				return (1);
			line++;
		}
		i++;
	}
	*r = values[0];
	*g = values[1];
	*b = values[2];
	return (0);
}

void	ft_parse_color(char *line, t_config *config)
{
	int	r;
	int	g;
	int	b;
	int	*color_ptr;

	while (*line == ' ' || *line == '\t')
		line++;
	if (ft_strncmp(line, "F", 1) == 0 && (line[1] == ' ' || line[1] == '\t'))
		color_ptr = &config->floor_color;
	else if (ft_strncmp(line, "C", 1) == 0
		&& (line[1] == ' ' || line[1] == '\t'))
		color_ptr = &config->ceiling_color;
	else
		return ;
	line += 2;
	while (*line == ' ' || *line == '\t')
		line++;
	if (ft_extract_rgb(line, &r, &g, &b))
		return ;
	*color_ptr = (r << 16) | (g << 8) | b;
}

int	ft_parse(const char *filename, t_config *config)
{
	int		fd;
	char	*line;

	fd = ft_open_file(filename);
	if (fd == -1)
		return (1);
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (ft_is_texture_line(line))
			ft_parse_texture(line, config);
		else if (ft_is_color_line(line))
			ft_parse_color(line, config);
		else if (ft_is_map_line(line))
			ft_parse_map(filename, config);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}
