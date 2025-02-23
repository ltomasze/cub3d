/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltomasze <ltomasze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 15:45:26 by ltomasze          #+#    #+#             */
/*   Updated: 2025/02/23 15:21:54 by ltomasze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int check_textures(char *line, int *textures_found)
{
    if (ft_strncmp(line, "NO ", 3) == 0) // North Texture
    {
        if (textures_found[0])
		return 0; // Już znaleziono
        textures_found[0] = 1;
    }
    else if (ft_strncmp(line, "SO ", 3) == 0) // South Texture
    {
        if (textures_found[1]) 
		return 0;
        textures_found[1] = 1;
    }
    else if (ft_strncmp(line, "WE ", 3) == 0) // West Texture
    {
        if (textures_found[2]) 
		return 0;
        textures_found[2] = 1;
    }
    else if (ft_strncmp(line, "EA ", 3) == 0) // East Texture
    {
        if (textures_found[3]) 
		return 0;
        textures_found[3] = 1;
    }
    return 1;
}

int check_colors(char *line, int *colors_found)
{
    if (strncmp(line, "F ", 2) == 0) // Floor Color
    {
        if (colors_found[0]) return 0; // Już znaleziono
        colors_found[0] = 1;
    }
    else if (strncmp(line, "C ", 2) == 0) // Ceiling Color
    {
        if (colors_found[1]) return 0;
        colors_found[1] = 1;
    }
    return 1;
}


void ft_error(char *str)
{
	printf("%s\n", str);
	exit(1);
}

void ft_check_args(int argc, char **argv)
{
	if(argc != 2)
		ft_error("Error: wrong number of arguments.");
	int len;
	len = ft_strlen(argv[1]);
	if(len < 4 || ft_strncmp(argv[1] + len - 4, ".cub", len) != 0)
		ft_error("Error: wrong file extension, expected '.cub'.");
	int fd = open(argv[1], O_RDONLY);
	if(fd == - 1)
		ft_error("Error: file does not exist.");
	check_cub(fd);
	close(fd);
}

int	main(int argc, char **argv)
{
	ft_check_args(argc, argv);
	return 0;
}