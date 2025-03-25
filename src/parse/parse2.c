/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltomasze <ltomasze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 17:01:33 by ltomasze          #+#    #+#             */
/*   Updated: 2025/03/25 17:31:39 by ltomasze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_free_config(t_config *config)
{
	int	i;

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
