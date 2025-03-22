/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tcm1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltomasze <ltomasze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 15:23:52 by ltomasze          #+#    #+#             */
/*   Updated: 2025/03/22 15:25:03 by ltomasze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	ft_is_texture_line(char *line)
{
	line = ft_skip_whitespaces(line);
	if (ft_strncmp(line, "NO", 2) == 0)
		return (1);
	else if (ft_strncmp(line, "SO", 2) == 0)
		return (1);
	else if (ft_strncmp(line, "WE", 2) == 0)
		return (1);
	else if (ft_strncmp(line, "EA", 2) == 0)
		return (1);
	return (0);
}

int	ft_is_color_line(char *line)
{
	line = ft_skip_whitespaces(line);
	if (line[0] == 'F')
		return (1);
	else if (line[0] == 'C')
		return (1);
	return (0);
}

int	ft_is_map_line(char *line)
{
	line = ft_skip_whitespaces(line);
	if (line[0] == '1')
		return (1);
	return (0);
}
