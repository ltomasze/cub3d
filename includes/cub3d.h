/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltomasze <ltomasze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 15:16:49 by ltomasze          #+#    #+#             */
/*   Updated: 2025/03/13 12:52:26 by ltomasze         ###   ########.fr       */
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
//ft_check_line.c
int ft_is_tcmnl_line(char *line);
int ft_check_line(const char *filename);
//check_tcm.c
char *ft_skip_whitespaces(char *line);
int ft_is_texture_line(char *line);
int ft_is_color_line(char *line);
int ft_is_map_line(char *line);
int ft_check_tcm(const char *filename);
//ft_check_only_one_tc.c
int ft_check_only_one_tc(const char *filename);
//check_textures.c
int check_path_exists(const char *path);
int ft_check_textures(const char *filename);
//check_map_is_last.c
int ft_check_map_is_last(const char *filename);
//check_map_vertical_integrity.c
int ft_check_map_vertical_integrity(const char *filename);
//check_map_characters.c
int ft_check_map_line_chars(const char *line);
int ft_check_map_characters(const char *filename);
//check_map_player_count.c
int ft_check_map_player_count(const char *filename);
//check_map_border.c
int ft_get_map_height(char **map);
int ft_get_map_width(char **map);
char **ft_get_map_lines(const char *filename, int *height, int *width);
int ft_check_floor_border(char **map, int height, int max_width);
void ft_free_map(char **map, int height);
int ft_check_player_border(char **map, int height);
int ft_check_map_border(const char *filename);
