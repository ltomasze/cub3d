/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltomasze <ltomasze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 15:16:49 by ltomasze          #+#    #+#             */
/*   Updated: 2025/03/04 17:31:05 by ltomasze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"
# include "../libft/libft.h"
/*
typedef struct s_game
{
    void    *mlx;
    void    *win;
	char    **map;
}   t_game;

#define ESC_KEY 65307  // ESC
*/
//get_next_line.c
char	*get_next_line(int fd);
//check_tcm.c
char *ft_skip_whitespaces(char *line);
int ft_is_texture_line(char *line);
int ft_is_color_line(char *line);
int ft_is_map_line(char *line);
int ft_check_tcm(const char *filename);
