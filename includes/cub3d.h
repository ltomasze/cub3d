/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbany <mbany@student.42warsaw.pl>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 15:16:49 by ltomasze          #+#    #+#             */
/*   Updated: 2025/04/08 18:47:40 by mbany            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include "../minilibx-linux/mlx.h"
#include "../minilibx-linux/mlx_int.h"
#include "../libft/libft.h"
#include <stdbool.h>
#include <math.h>

//for minimap
typedef struct s_draw_data
{
	int	tile_size;
	int	offset_x;
	int	offset_y;
	int	color;
}	t_draw_data;

typedef struct s_pos_in_map
{
	int		y;
	int		x;
	int		dy;
	int		dx;
	int		height;
	char	**map;
}	t_pos_in_map;

typedef struct s_config
{
	char	*textures[4];
	int		floor_color;
	int		ceiling_color;
	char	**map;
}	t_config;

typedef struct s_player
{
	bool		key_left;
	bool		key_right;
	bool		key_up;
	bool		key_down;
	bool		rotate_left;
	bool		rotate_right;
	float		x;
	float		y;
	float		angle;
	float		look_offset;

}	t_player;

typedef struct s_texture
{
	int			line_size;
	int			h;
	int			endian;
	int			w;
	char		*data;
	int			bpp;
	void		*img;
}	t_tex;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*data;
	char		**map;
	char		**copy_map;
	int			fd;
	int			bpp;
	int			line_size;
	int			endian;
	int			color_floor;
	int			color_ceiling;
	int			n_path;
	int			s_path;
	int			w_path;
	int			e_path;
	char		*n_tex_path;
	char		*s_tex_path;
	char		*w_tex_path;
	char		*e_tex_path;
	int			prev_mouse_x;
	int			prev_mouse_y;
	t_player	player;
	t_tex		n_tex;
	t_tex		s_tex;
	t_tex		w_tex;
	t_tex		e_tex;
	t_config	config;
}	t_game;

typedef enum s_error
{
	NO_FILE,
	INVALID_FILE,
	INVALID_SPAWN,
	INVALID_MAP,
	INVALID_INPUT
}	t_error;

typedef struct s_line
{
	float		dist;
	float		wall_h;
	int			start_y;
	int			end_y;
	int			tex_x;
}	t_line;

typedef struct s_ray
{
	float		deltadistx;
	float		raydirx;
	float		sidedistx;
	float		deltadisty;
	float		raydiry;
	float		sidedisty;
	float		perpwalldist;
	int			mapx;
	int			mapy;
	int			stepx;
	int			stepy;
	int			hit;
	int			side;
}	t_ray;

#define ESC_KEY 65307
#define W_KEY 119
#define A_KEY 97
#define S_KEY 115
#define D_KEY 100

#define LEFT_ARROW_KEY 65361
#define RIGHT_ARROW_KEY 65363

#define WIDTH 960
#define HEIGHT 720
#define BLOCK 64
#define DEBUG 0
#define COLLISION_RADIUS 10
#define PI 3.14159265359

// #define FLOOR 0x009600
// #define CELING 0x000096

#define NORTH_TEXTURE_PATH "./textures/north.xpm"
#define SOUTH_TEXTURE_PATH "./textures/south.xpm"
#define WEST_TEXTURE_PATH "./textures/west.xpm"
#define EAST_TEXTURE_PATH "./textures/east.xpm"

//get_next_line.c
char	*get_next_line(int fd);
//DIRECTORY CHECK
//check.c
int		ft_check_args(int argc, char **argv);
int		ft_check(int argc, char **argv);
//check_line.c
int		ft_is_tcmnl_line(char *line);
int		ft_check_line(const char *filename);
//check_tcm.c
char	*ft_skip_whitespaces(char *line);
int		ft_process_tcm_lines(int fd, int *has_texture, int *has_color,
			int *has_map);
int		ft_check_tcm(const char *filename);
//check_tcm1.c
int		ft_is_texture_line(char *line);
int		ft_is_color_line(char *line);
int		ft_is_map_line(char *line);
//check_only_one_tc.c
int		ft_check_only_one_tc(const char *filename);
int		ft_check_only_textures(const char *filename);
int		ft_check_only_colors(const char *filename);
//check_only_one_tc1.c
int		ft_check_texture_count(int no, int so, int we, int ea);
int		ft_check_color_count(int f, int c);
int		ft_process_no_so_lines(const char *filename, int *no, int *so);
int		ft_process_we_ea_lines(const char *filename, int *we, int *ea);
int		ft_process_color_lines(const char *filename, int *f, int *c);
//check_textures.c
void	ft_trim_whitespace_end_tx(char *trimmed);
int		ft_trim_path_tx(const char *path, char *trimmed);
int		check_path_exists(const char *path);
int		check_path_exists(const char *path);
int		ft_check_textures(const char *filename);
//check_textures1.c
int		ft_check_directory(const char *trimmed);
int		ft_check_xpm_file(const char *trimmed, int len);
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
void	ft_free_map_for_check(char **map, int height);
int		ft_check_map_border(const char *filename);
//check_map_border1.c
int		ft_get_map_height(char **map);
int		ft_get_map_width(char **map);
//check_map_border2.c
char	**ft_allocate_map(int count);
char	**ft_add_line_to_map(char **map, char *line, int *count);
void	ft_process_map_line(char ***map, char *line, int *height,
			size_t *max_width);
char	**ft_process_map_lines(int fd, int *height, int *width);
//check_map_border3.c
char	ft_check_ngh_floor(t_pos_in_map pos);
int		ft_check_dx(t_pos_in_map pos);
int		ft_check_nghs_floor(char **map, int height, int y, int x);
char	ft_get_ngh_player(char **map, int height, int ny, int nx);
int		ft_check_nghs_player(char **map, int height, int y, int x);
//check_utils.c
int		ft_open_file(const char *filename);
//DIRECTORY PARSE
//parse.c
int		ft_get_texture_index(char *line);
void	ft_parse_texture(char *line, t_config *config);
int		ft_extract_rgb(char *line, int *r, int *g, int *b);
void	ft_parse_color(char *line, t_config *config);
int		ft_parse(const char *filename, t_config *config);
//parse1.c
int		ft_count_map_lines(const char *filename);
void	ft_free_map_for_parse(t_config *config);
int		ft_init_map(t_config *config, int map_lines);
void	ft_load_map(const char *filename, t_config *config);
void	ft_parse_map(const char *filename, t_config *config);
//parse2.c
void	ft_free_config(t_config *config);

//main.c
int		close_game(t_game *game);
int		close_button(t_game *game);
int		draw_loop(t_game *game);

//kay.c
// int mouse_move(int x, int y, t_game *game);
int		mouse_move(int x, int y, t_game *game);
int		key_down(int keycode, t_game *game);
int		key_up(int keycode, t_player *player);
void	rotate_player(t_player *player);
void	move_player(t_player *player, t_game *game);

//map.c
void	draw_map(t_game *game);

//window.c
void	new_window(t_game *game, const char *map_file);
void	put_pixel(int x, int y, int color, t_game *game);
void	clear_image(t_game *game);
void	draw_floor_ceiling(t_game *game);
bool	touch(float px, float py, t_game *game);
void	draw_ceiling(t_game *game, int celing_color);
void	draw_floor(t_game *game, int floor_color);

//raycasting.c
void	draw_3d_view(t_game *game);
void	draw_column(t_game *game, t_tex *texture, int column, t_line *line);
float	compute_corrected_dist(t_ray *ray, t_player *player, float ray_angle);
void	perform_dda(t_ray *ray, t_game *game);
void	calc_delta_dist(t_ray *ray);
void	calc_line(t_player *player, t_ray *ray, t_tex *tex, t_line *line);
void	init_sidedist_step(t_ray *ray, t_player *player);
void	draw_line(t_player *player, t_game *game, float ray_angle, int column);

//textures.c
//void load_textures(t_game *game);
int		load_texture(t_game *game, t_tex *tex, char *path);
int		load_all_textures(t_game *game);
t_tex	*choose_texture(t_ray *ray, t_game *game);

//free.c
// void free_textures(t_game *game);
void	free_map(char **map);
void	free_texture(t_game *game, t_tex *texture);
void	clean_exit(t_game *game);
void	free_texture_paths(t_game *game);
void	free_all_textures(t_game *game);

//error.c
//static void	error_clean_up(t_game *game);
int		error(t_error code, t_game *game);

//init_game.c
void	init_ray(t_ray *ray, t_player *player, float ray_angle);
void	set_player_position(t_game *game);
int		init_game(t_game *game, char *file);
void	init_game_struct(t_game *game);
void	init_player(t_player *player);
int		parsing(t_game *data);
int		parse_color(char *str);
int		line_redirection(char *line, int *is_map_started);
int		parsing(t_game *data);
void	free_split(char **split);
int		line_check(char *line);
int		create_map(char *line, t_game *data);
int		texture_identifier(int code, char *line, t_game *game);
char	*ft_strjoin_gnl(char *buffer, char *new_s);
char	*tex_path_creator(char *line);
void	path_counter(int code, t_game *data);
char	*load_map(const char *file_path);

// init_game1.c
int		set_player_angle_and_position(t_game *game, int x, int y,
			char direction);
void	set_player_position(t_game *game);
void	init_player(t_player *player);
