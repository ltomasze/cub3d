/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltomasze <ltomasze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 15:16:49 by ltomasze          #+#    #+#             */
/*   Updated: 2025/03/22 15:26:16 by ltomasze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include "../minilibx-linux/mlx.h"
#include "../minilibx-linux/mlx_int.h"
#include "../libft/libft.h"

typedef struct s_pos_in_map
{
    int y;
    int x;
    int dy;
    int dx;
    int height;
    char **map;
} t_pos_in_map;

//get_next_line.c
char	*get_next_line(int fd);
//ft_check_line.c
int		ft_is_tcmnl_line(char *line);
int		ft_check_line(const char *filename);
//check_tcm.c
char	*ft_skip_whitespaces(char *line);
int		ft_process_tcm_lines(int fd, int *has_texture, int *has_color, int *has_map);
int		ft_check_tcm(const char *filename);
//check_tcm1.c
int		ft_is_texture_line(char *line);
int		ft_is_color_line(char *line);
int		ft_is_map_line(char *line);
//ft_check_only_one_tc.c
int		ft_check_only_one_tc(const char *filename);
int		ft_check_only_textures(const char *filename);
int		ft_check_only_colors(const char *filename);
//ft_check_only_one_tc1.c
int		ft_check_texture_count(int no, int so, int we, int ea);
int		ft_check_color_count(int f, int c);
int		ft_process_no_so_lines(const char *filename, int *no, int *so);
int		ft_process_we_ea_lines(const char *filename, int *we, int *ea);
int		ft_process_color_lines(const char *filename, int *f, int *c);
//check_textures.c
int		check_path_exists(const char *path);
int		ft_check_textures(const char *filename);
//check_colours.c
int		ft_parse_color_line(char **line, int *count_numbers, int *count_commas);
int		ft_is_valid_color_line(char *line);
int		ft_check_color_value(char **line);
int		ft_check_color_range(char *line);
int		ft_check_colours(const char *filename);
//check_colours1.c
int		ft_process_number(char **line, int *count_numbers);
int		ft_process_comma(char **line, int *count_commas);
//check_map_is_last.c
int		ft_check_line_type(char *line, int *has_texture, int *has_color);
int		ft_check_tc_line_order(int fd, int *has_texture, int *has_color);
int		ft_check_map_is_last(const char *filename);
//check_map_vertical_integrity.c
int		ft_find_start_map(int fd, char **line, int *map_started);
int		ft_process4_map_lines(int fd);
int		ft_check_map_vertical_integrity(const char *filename);
//check_map_characters.c
int		ft_check_map_line_chars(const char *line);
int		ft_process2_map_lines(int fd);
int		ft_check_map_characters(const char *filename);
//check_map_player_count.c
int		ft_count_players_in_line(char *line);
int		ft_process3_map_lines(int fd);
int		ft_check_map_player_count(const char *filename);
//check_map_border.c
char	**ft_get_map_lines(const char *filename, int *height, int *width);
int		ft_check_floor_border(char **map, int height, int max_width);
int		ft_check_player_border(char **map, int height);
void	ft_free_map(char **map, int height);
int		ft_check_map_border(const char *filename);
//check_map_border1.c
int		ft_get_map_height(char **map);
int		ft_get_map_width(char **map);
//check_map_border2.c
char	**ft_allocate_map(int count);
char	**ft_add_line_to_map(char **map, char *line, int *count);
void	ft_process_map_line(char ***map, char *line, int *height, size_t *max_width);
char	**ft_process_map_lines(int fd, int *height, int *width);
//check_map_border3.c
char	ft_check_ngh_floor(t_pos_in_map pos);
int		ft_check_dx(t_pos_in_map pos);
int		ft_check_nghs_floor(char **map, int height, int y, int x);
char	ft_get_ngh_player(char **map, int height, int ny, int nx);
int		ft_check_nghs_player(char **map, int height, int y, int x);
//check_utils.c
int		ft_open_file(const char *filename);
