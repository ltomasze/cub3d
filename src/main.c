/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltomasze <ltomasze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 15:45:26 by ltomasze          #+#    #+#             */
/*   Updated: 2025/03/25 15:58:59 by ltomasze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void ft_print_textures(t_config *config)
{
    printf("Textures:\n");
    printf("NO: %s", config->textures[0]);
    printf("SO: %s", config->textures[1]);
    printf("WE: %s", config->textures[2]);
    printf("EA: %s", config->textures[3]);
}

void ft_print_colors(t_config *config)
{
    int floor_r = (config->floor_color >> 16) & 0xFF;
    int floor_g = (config->floor_color >> 8) & 0xFF;
    int floor_b = config->floor_color & 0xFF;

    int ceiling_r = (config->ceiling_color >> 16) & 0xFF;
    int ceiling_g = (config->ceiling_color >> 8) & 0xFF;
    int ceiling_b = config->ceiling_color & 0xFF;

    printf("Colors:\n");
    printf("Floor Color: RGB(%d, %d, %d)\n", floor_r, floor_g, floor_b);
    printf("Ceiling Color: RGB(%d, %d, %d)\n", ceiling_r, ceiling_g, ceiling_b);
}

void ft_print_map(t_config *config)
{
    printf("Map:\n");
    if (config->map)
    {
        for (int i = 0; config->map[i] != NULL; i++)
        {
            printf("%s", config->map[i]);
        }
    }
}

void ft_free_config(t_config *config)
{
    int i;

	i = 0;
    while (i < 4)
    {
        if (config->textures[i] != NULL)
        {
            free(config->textures[i]);
            config->textures[i] = NULL;
        }
		i++;
    }
    if (config->map != NULL)
    {
        i = 0;
        while (config->map[i] != NULL)
        {
            free(config->map[i]);
            config->map[i] = NULL;
            i++;
        }
        free(config->map);
        config->map = NULL;
    }
}

int	main(int argc, char **argv)
{
	t_config config;

	config.map = NULL;
	if (ft_check(argc, argv))
		return (1);
	if (ft_parse_cub(argv[1], &config))
	{
		printf("Error: Failed to parse .cub file\n");
		ft_free_config(&config);
		return (1);
	}
	// Sprawdzenie, czy dane zostały prawidłowo załadowane
    ft_print_textures(&config);
    ft_print_colors(&config);
    ft_print_map(&config);
	printf("\n");
	ft_free_config(&config);
	return (0);
}
