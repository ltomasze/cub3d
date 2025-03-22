/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_characters.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltomasze <ltomasze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:31:40 by ltomasze          #+#    #+#             */
/*   Updated: 2025/03/20 11:45:11 by ltomasze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	ft_check_map_line_chars(const char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '1' && line[i] != '0'
			&& line[i] != 'N' && line[i] != 'S'
			&& line[i] != 'W' && line[i] != 'E'
			&& line[i] != ' ' && line[i] != '\t'
			&& line[i] != '\n' && line[i] != '\v'
			&& line[i] != '\f' && line[i] != '\r')
			return (1);
		i++;
	}
	return (0);
}

int	ft_process2_map_lines(int fd)
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
		if (ft_is_map_line(trimmed) && ft_check_map_line_chars(trimmed))
		{
			free(line);
			return (1);
		}
		free(line);
		line = get_next_line(fd);
	}
	return (0);
}

int	ft_check_map_characters(const char *filename)
{
	int		fd;
	int		error;

	fd = ft_open_file(filename);
	if (fd == -1)
		return (1);
	error = ft_process2_map_lines(fd);
	close(fd);
	if (error)
	{
		printf("Error: Map line have forbidden characters.\n");
		return (1);
	}
	return (0);
}

/*
int	ft_check_map_characters(const char *filename)
{
	int		fd;
	char	*line;
	int		error;
	char	*trimmed;

	fd = ft_open_file(filename);
	if (fd == -1)
		return (1);
	error = 0;
	line = get_next_line(fd);
	while (line != NULL)
    {
        trimmed = ft_skip_whitespaces(line);
        if (*trimmed == '\0')
        {
            free(line);
			line = get_next_line(fd);
            continue;
        }
        if (ft_is_map_line(trimmed))
        {
            if (ft_check_map_line_chars(trimmed))
            {
                error = 1;
                free(line);
                break;
            }
        }
        free(line);
		line = get_next_line(fd);
    }
    close(fd);
    if (error)
    {
        printf("Error: Map line have forbidden characters.\n");
        return 1;
    }
    return 0;
}*/
