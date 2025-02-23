/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltomasze <ltomasze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 15:45:26 by ltomasze          #+#    #+#             */
/*   Updated: 2025/02/23 15:51:36 by ltomasze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"




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
	close(fd);
}

int	main(int argc, char **argv)
{
	ft_check_args(argc, argv);
	return 0;
}