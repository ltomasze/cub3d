/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_is_last.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltomasze <ltomasze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 18:15:46 by ltomasze          #+#    #+#             */
/*   Updated: 2025/03/20 12:34:16 by ltomasze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	ft_check_line_type(char *line, int *has_texture, int *has_color)
{
	char	*trimmed;

	trimmed = ft_skip_whitespaces(line);
	if (*trimmed == '\0')
		return (0);
	if (ft_is_map_line(trimmed))
	{
		if (!*has_texture || !*has_color)
		{
			printf("Error: Map found before texture or color.\n");
			return (1);
		}
	}
	else if (ft_is_texture_line(trimmed))
		*has_texture = 1;
	else if (ft_is_color_line(trimmed))
		*has_color = 1;
	return (0);
}

int	ft_check_tc_line_order(int fd, int *has_texture, int *has_color)
{
	char	*line;

	line = get_next_line(fd);
	while (line != NULL)
	{
		if (ft_check_line_type(line, has_texture, has_color))
		{
			free(line);
			return (1);
		}
		free(line);
		line = get_next_line(fd);
	}
	return (0);
}

int	ft_check_map_is_last(const char *filename)
{
	int	fd;
	int	has_texture;
	int	has_color;

	fd = ft_open_file(filename);
	if (fd == -1)
		return (1);
	has_texture = 0;
	has_color = 0;
	if (ft_check_tc_line_order(fd, &has_texture, &has_color))
	{
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}
/*
int	ft_check_map_is_last(const char *filename)
{
    int 	fd;
	char	*line;
	int		has_texture;
	int		has_color;

	fd = ft_open_file(filename);
	if (fd == -1)
		return (1);
	has_texture = 0;
	has_color = 0;
    while ((line = get_next_line(fd)) != NULL)
    {
        if (line == NULL)
        {
            free(line);
            continue;
        }
        char *trimmed = ft_skip_whitespaces(line);
        if (*trimmed == '\0') 
        {
            free(line);
            continue;
        }
        if (ft_is_map_line(trimmed))
        {
            if (!has_texture || !has_color)
            {
                printf("Error: Map found before texture or color.\n");
                free(line);
                close(fd);
                return 1;
            }
		}
		else if (ft_is_texture_line(trimmed))
			has_texture = 1;
		else if (ft_is_color_line(trimmed))
			has_color = 1;
		free(line);
	}
	close(fd);
	return (0);
}*/
