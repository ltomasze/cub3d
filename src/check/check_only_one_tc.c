/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_only_one_tc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltomasze <ltomasze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:04:26 by ltomasze          #+#    #+#             */
/*   Updated: 2025/03/22 14:48:26 by ltomasze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	ft_check_only_textures(const char *filename)
{
	int	no;
	int	so;
	int	we;
	int	ea;

	no = 0;
	so = 0;
	we = 0;
	ea = 0;
	if (ft_process_no_so_lines(filename, &no, &so)
		|| ft_process_we_ea_lines(filename, &we, &ea))
		return (1);
	return (ft_check_texture_count(no, so, we, ea));
}

int	ft_check_only_colors(const char *filename)
{
	int	f;
	int	c;

	f = 0;
	c = 0;
	if (ft_process_color_lines(filename, &f, &c))
		return (1);
	return (ft_check_color_count(f, c));
}

int	ft_check_only_one_tc(const char *filename)
{
	if (ft_check_only_textures(filename) || ft_check_only_colors(filename))
		return (1);
	return (0);
}
