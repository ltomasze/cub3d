/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tcm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltomasze <ltomasze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 12:22:40 by ltomasze          #+#    #+#             */
/*   Updated: 2025/03/22 15:25:13 by ltomasze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	*ft_skip_whitespaces(char *line)
{
	while (*line && (*line == ' ' || *line == '\t'))
		line++;
	return (line);
}

int	ft_process_tcm_lines(int fd, int *has_texture, int *has_color,
	int *has_map)
{
	char	*line;
	char	*trimmed;

	line = get_next_line(fd);
	while (line != NULL)
	{
		trimmed = ft_skip_whitespaces(line);
		if (*trimmed == '\0')
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		if (ft_is_texture_line(trimmed))
			*has_texture = 1;
		else if (ft_is_color_line(trimmed))
			*has_color = 1;
		else if (ft_is_map_line(trimmed))
			*has_map = 1;
		free(line);
		line = get_next_line(fd);
	}
	return (0);
}

int	ft_check_tcm(const char *filename)
{
	int	fd;
	int	has_texture;
	int	has_color;
	int	has_map;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		printf("Error: Cannot open file.\n");
		return (1);
	}
	has_texture = 0;
	has_color = 0;
	has_map = 0;
	ft_process_tcm_lines(fd, &has_texture, &has_color, &has_map);
	close(fd);
	if (!has_texture || !has_color || !has_map)
	{
		printf("Error: Missing textures, colors, or map in .cub file.\n");
		return (1);
	}
	return (0);
}
