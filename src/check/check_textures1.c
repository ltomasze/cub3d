/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_textures1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltomasze <ltomasze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 17:00:18 by ltomasze          #+#    #+#             */
/*   Updated: 2025/03/22 17:01:55 by ltomasze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	ft_check_directory(const char *trimmed)
{
	int	fd;

	fd = ft_open_file(trimmed);
	if (fd == -1)
	{
		printf("Error: Directory not found: %s\n", trimmed);
		return (1);
	}
	close(fd);
	return (0);
}

int	ft_check_xpm_file(const char *trimmed, int len)
{
	int	fd;

	(void)len;
	fd = ft_open_file(trimmed);
	if (fd == -1)
	{
		printf("Error: File not found: %s\n", trimmed);
		return (1);
	}
	close(fd);
	return (0);
}
