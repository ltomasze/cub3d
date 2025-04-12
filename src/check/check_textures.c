/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltomasze <ltomasze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 12:48:26 by ltomasze          #+#    #+#             */
/*   Updated: 2025/03/22 17:00:54 by ltomasze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_trim_whitespace_end_tx(char *trimmed)
{
	int	len;

	len = ft_strlen(trimmed);
	while (len > 0 && (trimmed[len - 1] == ' '
			|| trimmed[len - 1] == '\t' || trimmed[len - 1] == '\n'))
	{
		trimmed[len - 1] = '\0';
		len--;
	}
}

int	ft_trim_path_tx(const char *path, char *trimmed)
{
	int	i;
	int	len;

	if (ft_strlen(path) >= 1023)
	{
		printf("Error: Path too long\n");
		return (1);
	}
	i = 0;
	while (path[i] && i < 1023)
	{
		trimmed[i] = path[i];
		i++;
	}
	trimmed[i] = '\0';
	len = ft_strlen(trimmed);
	ft_trim_whitespace_end_tx(trimmed);
	if (ft_strlen(trimmed) == 0)
	{
		printf("Error: Empty path\n");
		return (1);
	}
	return (0);
}

int	check_path_exists(const char *path)
{
	char	trimmed[1024];
	int		len;

	if (ft_trim_path_tx(path, trimmed))
		return (1);
	len = ft_strlen(trimmed);
	if (trimmed[len - 1] == '/')
		return (ft_check_directory(trimmed));
	if (len >= 4 && ft_strncmp(trimmed + len - 4, ".xpm", 4) == 0)
		return (ft_check_xpm_file(trimmed, len));
	printf("Error: Path '%s' does not end with '/' or '.xpm'\n", trimmed);
	return (1);
}

int	ft_process_textures(int fd)
{
	char	*line;
	int		error_found;
	char	*path;

	error_found = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (ft_is_texture_line(line))
		{
			path = ft_skip_whitespaces(line);
			while (*path && *path != ' ' && *path != '\t')
				path++;
			path = ft_skip_whitespaces(path);
			if (check_path_exists(path))
				error_found = 1;
		}
		free(line);
		line = get_next_line(fd);
	}
	return (error_found);
}

int	ft_check_textures(const char *filename)
{
	int	fd;

	fd = ft_open_file(filename);
	if (fd == -1)
		return (1);
	return (ft_process_textures(fd));
}
