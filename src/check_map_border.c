/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_border.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltomasze <ltomasze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 18:19:41 by ltomasze          #+#    #+#             */
/*   Updated: 2025/03/16 13:24:20 by ltomasze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	ft_get_map_height(char **map)
{
	int	count;

	count = 0;
	while (map[count] != NULL)
		count++;
	return (count);
}

int	ft_get_map_width(char **map)
{
	int	max_width;
	int	i;
	int	len;

	max_width = 0;
	i = 0;
	while (map[i] != NULL)
	{
		len = ft_strlen(map[i]);
		if (len > max_width)
			max_width = len;
		i++;
	}
	return (max_width);
}

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

char	**ft_process_map_lines(int fd, int *height, int *width)
{
	char		**map;
	char		*line;
	int			map_started;
	size_t		max_width;

	map = NULL;
	map_started = 0;
	*height = 0;
	max_width = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (!map_started && ft_is_map_line(line))
			map_started = 1;
		if (map_started)
		{
			if (line[0] == '\n' || line[0] == '\0')
			{
				free(line);
				break ;
			}
			map = ft_add_line_to_map(map, line, height);
			if (!map)
				return (NULL);
			if (ft_strlen(line) > max_width)
				max_width = ft_strlen(line);
		}
		else
			free(line);
		line = get_next_line(fd);
	}
	*width = max_width;
	return (map);
}

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

int ft_check_floor_border(char **map, int height, int max_width)
{
    (void)max_width;
    int y = 0;
    while (y < height)
    {
        int row_len = ft_strlen(map[y]);
        int x = 0;
        while (x < row_len)
        {
            if (map[y][x] == '0')
            {
                int dy = -1;
                while (dy <= 1)
                {
                    int dx = -1;
                    while (dx <= 1)
                    {
                        if (!(dy == 0 && dx == 0))
                        {
                            int ny = y + dy;
                            int nx = x + dx;
                            char neighbor;
                            if (ny < 0 || ny >= height)
                                neighbor = ' ';
                            else
                            {
                                int neighbor_len = ft_strlen(map[ny]);
                                if (nx < 0 || nx >= neighbor_len)
                                    neighbor = ' ';
                                else
                                    neighbor = map[ny][nx];
                            }
                            if (neighbor != '1' && neighbor != '0' &&
                                neighbor != 'N' && neighbor != 'S' &&
                                neighbor != 'W' && neighbor != 'E')
                            {
                                printf("Error: Missing border for floor\n");
                                return 1;
                            }
                        }
                        dx++;
                    }
                    dy++;
                }
            }
            x++;
        }
        y++;
    }
    return 0;
}

void ft_free_map(char **map, int height)
{
    int i = 0;
    while (i < height)
    {
        free(map[i]);
        i++;
    }
    free(map);
}

int ft_check_player_border(char **map, int height)
{
    int y = 0;
    while (y < height)
    {
        int row_len = ft_strlen(map[y]);
        int x = 0;
        while (x < row_len)
        {
            if (map[y][x] == 'N' || map[y][x] == 'W' ||
                map[y][x] == 'E' || map[y][x] == 'S')
            {
                int dy = -1;
                while (dy <= 1)
                {
                    int dx = -1;
                    while (dx <= 1)
                    {
                        if (!(dy == 0 && dx == 0)) // Pomijamy środek (gracza)
                        {
                            int ny = y + dy;
                            int nx = x + dx;
                            char neighbor;
                            if (ny < 0 || ny >= height)
                                neighbor = ' '; // Poza mapą -> błąd
                            else
                            {
                                int neighbor_len = ft_strlen(map[ny]);
                                if (nx < 0 || nx >= neighbor_len)
                                    neighbor = ' '; // Poza mapą -> błąd
                                else
                                    neighbor = map[ny][nx];
                            }
                            if (neighbor != '0' && neighbor != '1')
                            {
                                printf("Error: Player is not properly enclosed at (%d, %d)\n", y, x);
                                return 1;
                            }
                        }
                        dx++;
                    }
                    dy++;
                }
            }
            x++;
        }
        y++;
    }
    return 0;
}

int	ft_check_map_border(const char *filename)
{
	int	height;
	int	width;
	char **map = ft_get_map_lines(filename, &height, &width);
	if (!map)
		return (1);
    if (ft_check_floor_border(map, height, width) ||
        ft_check_player_border(map, height))
    {
        ft_free_map(map, height);
        return 1;
    }
    ft_free_map(map, height);
    return 0;
}