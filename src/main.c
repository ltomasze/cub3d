/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltomasze <ltomasze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 15:45:26 by ltomasze          #+#    #+#             */
/*   Updated: 2025/03/25 18:43:51 by ltomasze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int argc, char **argv)
{
	t_config	config;

	config.map = NULL;
	if (ft_check(argc, argv))
		return (1);
	if (ft_parse_cub(argv[1], &config))
	{
		printf("Error: Failed to parse .cub file\n");
		ft_free_config(&config);
		return (1);
	}
	ft_free_config(&config);
	return (0);
}
