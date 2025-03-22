/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_border2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltomasze <ltomasze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 10:58:19 by ltomasze          #+#    #+#             */
/*   Updated: 2025/03/20 11:13:25 by ltomasze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	**ft_allocate_map(int count)
{
	char	**tmp;

	tmp = malloc(sizeof(char *) * (count + 1));
	if (!tmp)
		printf("Error: Memory allocation failed\n");
	return (tmp);
}

char	**ft_add_line_to_map(char **map, char *line, int *count)
{
	char	**tmp;
	int		i;

	tmp = ft_allocate_map(*count + 1);
	if (!tmp)
		return (NULL);
	i = 0;
	while (i < *count)
	{
		tmp[i] = map[i];
		i++;
	}
	free(map);
	tmp[*count] = line;
	(*count)++;
	return (tmp);
}

void	ft_process_map_line(char ***map, char *line, int *height,
	size_t *max_width)
{
	if (line[0] == '\n' || line[0] == '\0')
	{
		free(line);
		return ;
	}
	*map = ft_add_line_to_map(*map, line, height);
	if (ft_strlen(line) > *max_width)
		*max_width = ft_strlen(line);
}

char	**ft_process_map_lines(int fd, int *height, int *width)
{
	char		**map;
	char		*line;
	size_t		max_width;

	map = NULL;
	*height = 0;
	max_width = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (ft_is_map_line(line))
			ft_process_map_line(&map, line, height, &max_width);
		else
			free(line);
		line = get_next_line(fd);
	}
	*width = max_width;
	return (map);
}
