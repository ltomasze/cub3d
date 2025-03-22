/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_player_count.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltomasze <ltomasze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 14:03:54 by ltomasze          #+#    #+#             */
/*   Updated: 2025/03/20 13:07:37 by ltomasze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	ft_count_players_in_line(char *line)
{
	int	i;
	int	player_count;

	i = 0;
	player_count = 0;
	while (line[i])
	{
		if (line[i] == 'N' || line[i] == 'S'
			|| line[i] == 'W' || line[i] == 'E')
			player_count++;
		i++;
	}
	return (player_count);
}

int	ft_process3_map_lines(int fd)
{
	int		player_count;
	char	*line;
	char	*trimmed;

	player_count = 0;
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
		if (ft_is_map_line(trimmed))
			player_count += ft_count_players_in_line(trimmed);
		free(line);
		line = get_next_line(fd);
	}
	return (player_count);
}

int	ft_check_map_player_count(const char *filename)
{
	int	fd;
	int	player_count;

	fd = ft_open_file(filename);
	if (fd == -1)
		return (1);
	player_count = ft_process3_map_lines(fd);
	close(fd);
	if (player_count != 1)
	{
		printf("Error: Only one player. Found: %d\n", player_count);
		return (1);
	}
	return (0);
}

/*
int	ft_check_map_player_count(const char *filename)
{
	int		fd;
	char	*line;
	int		player_count;

	fd = ft_open_file(filename);
	if (fd == -1)
		return (1);
	player_count = 0;
    while ((line = get_next_line(fd)) != NULL)
    {
        char *trimmed = ft_skip_whitespaces(line);

        if (*trimmed == '\0')
        {
            free(line);
            continue;
        }

        if (ft_is_map_line(trimmed))
        {
            int i = 0;
            while (trimmed[i])
            {
                if (trimmed[i] == 'N' || trimmed[i] == 'S' ||
                    trimmed[i] == 'W' || trimmed[i] == 'E')
                    player_count++;
                i++;
            }
		}
		free(line);
	}
	close(fd);
	if (player_count != 1)
    {
		printf("Error: Only one player. Found: %d\n", player_count);
		return (1);
    }
	return (0);
}*/
