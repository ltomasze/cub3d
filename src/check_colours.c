/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_colours.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltomasze <ltomasze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 14:49:36 by ltomasze          #+#    #+#             */
/*   Updated: 2025/03/15 15:06:57 by ltomasze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	ft_is_valid_color_line(char *line)
{
	int	count_numbers;
	int	count_commas;

	count_numbers = 0;
	count_commas = 0;
	line = ft_skip_whitespaces(line);
	if (*line != 'F' && *line != 'C')
		return (0);
	line++;
	line = ft_skip_whitespaces(line);
	while (*line)
	{
		if (*line >= '0' && *line <= '9')
		{
			count_numbers++;
			while (*line >= '0' && *line <= '9')
				line++;
		}
		else if (*line == ',')
		{
			count_commas++;
			line++;
			line = ft_skip_whitespaces(line);
			if (*line < '0' || *line > '9')
			{
				printf("Error: Expected a digit after comma in color line\n");
				return (1);
			}
		}
		else if (*line == ' ' || *line == '\t' || *line == '\n')
		{
			line++;
		}
		else
		{
			printf("Error: Invalid character '%c' in color line\n", *line);
			return (1);
		}
	}
	line = ft_skip_whitespaces(line);
	if (*line != '\0')
	{
		printf("Error: Unexpected char '%c' after color components\n", *line);
		return (1);
	}
	if (count_commas != 2 || count_numbers != 3)
	{
		printf("Error: Incorrect number format in color line\n");
		return (1);
	}
	return (0);
}

int	ft_check_color_range(char *line)
{
	int	i;
	int	value;

	i = 0;
	line = ft_skip_whitespaces(line);
	if (*line != 'F' && *line != 'C')
		return (1);
	line++;
	line = ft_skip_whitespaces(line);
	while (i < 3)
	{
		line = ft_skip_whitespaces(line);
		value = ft_atoi(line);
		if (value < 0 || value > 255)
		{
			printf("Error: Color %d is out of range (0-255)\n", value);
			return (1);
		}
		while (*line >= '0' && *line <= '9')
			line++;
		line = ft_skip_whitespaces(line);
		if (i < 2)
		{
			if (*line == ',')
				line++;
			line = ft_skip_whitespaces(line);
		}
		i++;
	}
	return (0);
}

int	ft_check_colours(const char *filename)
{
	int		fd;
	char	*line;
	char	*trim;

	fd = ft_open_file(filename);
	if (fd == -1)
		return (1);
	line = get_next_line(fd);
	while (line != NULL)
	{
		trim = ft_skip_whitespaces(line);
		if (*trim == 'F' || *trim == 'C')
		{
			if (ft_is_valid_color_line(trim) || ft_check_color_range(trim))
			{
				free(line);
				close(fd);
				return (1);
			}
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}
