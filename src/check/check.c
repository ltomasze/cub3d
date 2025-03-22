/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltomasze <ltomasze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 17:27:47 by ltomasze          #+#    #+#             */
/*   Updated: 2025/03/22 17:39:21 by ltomasze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	ft_check_args(int argc, char **argv)
{
	int	len;
	int	fd;

	if (argc != 2)
		return (printf("Error: wrong number of arguments.\n"), 1);
	len = ft_strlen(argv[1]);
	if (len < 4 || ft_strncmp(argv[1] + len - 4, ".cub", len) != 0)
		return (printf("Error: wrong file extension, expected '.cub'.\n"), 1);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (printf("Error: file does not exist.\n"), 1);
	close(fd);
	return (0);
}

int	ft_check(int argc, char **argv)
{
	if (ft_check_args(argc, argv))
	{
		printf("Usage: ./cub3d maps/<map_file.cub>\n");
		return (1);
	}
	if (ft_check_line(argv[1])
		|| ft_check_tcm(argv[1])
		|| ft_check_only_one_tc(argv[1])
		|| ft_check_textures(argv[1])
		|| ft_check_colours(argv[1])
		|| ft_check_map_is_last(argv[1])
		|| ft_check_map_vertical_integrity(argv[1])
		|| ft_check_map_characters(argv[1])
		|| ft_check_map_player_count(argv[1])
		|| ft_check_map_border(argv[1]))
		return (1);
	return (0);
}
