/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_colours1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltomasze <ltomasze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 17:21:56 by ltomasze          #+#    #+#             */
/*   Updated: 2025/03/15 17:22:32 by ltomasze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	ft_process_number(char **line, int *count_numbers)
{
	(*count_numbers)++;
	while (**line >= '0' && **line <= '9')
		(*line)++;
	*line = ft_skip_whitespaces(*line);
	return (0);
}

int	ft_process_comma(char **line, int *count_commas)
{
	(*count_commas)++;
	(*line)++;
	*line = ft_skip_whitespaces(*line);
	if (**line < '0' || **line > '9')
	{
		printf("Error: Expected a digit after comma in color line\n");
		return (1);
	}
	return (0);
}
