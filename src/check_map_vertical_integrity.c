/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_vertical_integrity.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltomasze <ltomasze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 14:02:26 by ltomasze          #+#    #+#             */
/*   Updated: 2025/03/20 14:05:17 by ltomasze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	ft_find_start_map(int fd, char **line, int *map_started)
{
	char	*trimmed;

	trimmed = ft_skip_whitespaces(*line);
	if (*trimmed == '\0')
	{
		free(*line);
		*line = get_next_line(fd);
		return (0);
	}
	if (ft_is_map_line(trimmed))
		*map_started = 1;
	else if (*map_started)
	{
		free(*line);
		printf("Error: Invalid map(wrong char before 1, or new line).\n");
		return (1);
	}
	free(*line);
	*line = get_next_line(fd);
	return (0);
}

int	ft_process4_map_lines(int fd)
{
	int		map_started;
	char	*line;

	map_started = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (ft_find_start_map(fd, &line, &map_started))
			return (1);
	}
	return (0);
}

int	ft_check_map_vertical_integrity(const char *filename)
{
	int	fd;
	int	result;

	fd = ft_open_file(filename);
	if (fd == -1)
		return (1);
	result = ft_process4_map_lines(fd);
	close(fd);
	return (result);
}

/*int ft_check_map_vertical_integrity(const char *filename)
{
    int fd;
	char *line;
	int map_started;
	char *trimmed;
	
	fd = ft_open_file(filename);
	if (fd == -1)
		return (1);
    map_started = 0;
	line = get_next_line(fd);
	while(line != NULL)
    {
        trimmed = ft_skip_whitespaces(line);
        if (*trimmed == '\0')
        {
            free(line);
            continue;
        }
        if (ft_is_map_line(trimmed))
            map_started = 1;
        else if (map_started)
        {
            free(line);
            close(fd);
            printf("Error: Invalid map(wrong char before 1, or new line).\n");
            return 1;
        }
        free(line);
    }
    close(fd);
    return 0;
}*/
