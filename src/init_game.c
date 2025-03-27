/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbany <mbany@student.42warsaw.pl>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 15:11:49 by mbany             #+#    #+#             */
/*   Updated: 2025/03/25 20:12:39 by mbany            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_ray(t_ray *ray, t_player *player, float ray_angle)
{
	ray->raydirx = cosf(ray_angle);
	ray->raydiry = sinf(ray_angle);
	ray->mapx = (int)(player->x / BLOCK);
	ray->mapy = (int)(player->y / BLOCK);
}
void	init_player(t_player *player)
{
	player->x = 820;
	player->y = 200;
	player->angle = PI / 2;
	player->key_up = false;
	player->key_down = false;
	player->key_left = false;
	player->key_right = false;
	player->rotate_left = false;
	player->rotate_right = false;
}

void	init_game_struct(t_game *game)
{
	game->mlx = NULL;
	game->win = NULL;
	game->img = NULL;
	game->data = NULL;
	game->map = NULL;
	game->copy_map = NULL;
	game->n_tex_path = NULL;
	game->s_tex_path = NULL;
	game->w_tex_path = NULL;
	game->e_tex_path = NULL;
}

int	init_game(t_game *game, char *file)
{
	init_game_struct(game);
	// validation
	init_player(&game->player);
	game->fd = open(file, O_RDONLY);
	////////////////////////////////////////////////////////
	if (!parsing(game))
		return (error(INVALID_MAP, game));
	/////////////////////////////////////////////////////////
	//valid_map
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "cub3d");
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->data = mlx_get_data_addr(game->img, &game->bpp,
			&game->line_size, &game->endian);
	if (!load_all_textures(game))
		return (error(INVALID_FILE, game));
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (1);
}


//tmp===================================================



int	parsing(t_game *data)
{
	char	*line;
	int		is_map_started;

	is_map_started = 0;
	while (1)
	{
		line = get_next_line(data->fd);
		if (!line)
			break ;
		if (!is_map_started)
		{
			if (!line_redirection(line, &is_map_started, data))
				return (0);
		}
		if (is_map_started)
		{
			create_map(line, data);
			break ;
		}
		if (line)
			free(line);
	}
	return (1);
}
int	parse_color(char *str)
{
	char	**split;
	int		r;
	int		g;
	int		b;
	int		color;

	split = ft_split(str, ',');
	if (!split || !split[0] || !split[1] || !split[2])
	{
		free_split(split);
		return (-1);
	}
	r = ft_atoi(split[0]);
	g = ft_atoi(split[1]);
	b = ft_atoi(split[2]);
	free_split(split);
	color = (r << 16) | (g << 8) | b;
	return (color);
}

static int	is_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (!line[i] || line[i] == '\n')
		return (0);
	while (line[i] && line[i] != '\n')
	{
		if (!ft_strchr("01NSEW ", line[i]))
			return (0);
		i++;
	}
	return (1);
}

int	line_redirection(char *line, int *is_map_started, t_game *data)
{
	if (!ft_strcmp(line, "\n"))
	{
		line = NULL;
		free(line);
		return (1);
	}
	if (!line_check(line, data))
	{
		free(line);
		return (0);
	}
	if (is_map_line(line))
		*is_map_started = 1;
	return (1);
}


void	free_split(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}



int	line_check(char *line, t_game *data)
{
	if (!ft_strncmp(line, "NO", 2))
		return (texture_identifier(1, line, data));
	else if (!ft_strncmp(line, "SO", 2))
		return (texture_identifier(2, line, data));
	else if (!ft_strncmp(line, "WE", 2))
		return (texture_identifier(3, line, data));
	else if (!ft_strncmp(line, "EA", 2))
		return (texture_identifier(4, line, data));
	else if (!ft_strncmp(line, "F ", 2))
	{
		data->color_floor = parse_color(line + 2);
		return (1);
	}
	else if (!ft_strncmp(line, "C ", 2))
	{
		data->color_ceiling = parse_color(line + 2);
		return (1);
	}
	else if (!ft_strcmp(line, "\n"))
		return (0);
	else
		return (1);
}

int	create_map(char *line, t_game *data)
{
	char	*next;

	while (1)
	{
		next = get_next_line(data->fd);
		if (!next)
			break ;
		line = ft_strjoin_gnl(line, next);
		free(next);
	}
	data->map = ft_split(line, '\n');
	data->copy_map = ft_split(line, '\n');
	close(data->fd);
	free(line);
	return (1);
}

int	texture_identifier(int code, char *line, t_game *game)
{
	char	*path;

	path = tex_path_creator(line);
	path_counter(code, game);
	if (!path)
		return (0);
	if (code == 1)
		game->n_tex_path = path;
	else if (code == 2)
		game->s_tex_path = path;
	else if (code == 3)
		game->w_tex_path = path;
	else if (code == 4)
		game->e_tex_path = path;
	return (1);
}
char	*ft_strjoin_gnl(char *buffer, char *new_s)
{
	int		i;
	int		j;
	char	*string;
	int		length;

	length = 0;
	i = 0;
	j = 0;
	if (!buffer || !new_s)
		return (NULL);
	length = ft_strlen(buffer) + ft_strlen(new_s);
	string = (char *)malloc((sizeof(char) * (length + 1)));
	if (!string)
		return (NULL);
	while (buffer[i] != '\0')
		string[j++] = buffer[i++];
	i = 0;
	while (new_s[i] != '\0')
		string[j++] = new_s[i++];
	string[j] = '\0';
	if (buffer)
		free(buffer);
	buffer = NULL;
	return (string);
}

char	*tex_path_creator(char *line)
{
	int		i;
	int		len;
	char	*path;

	i = 2;
	while (line[i] == ' ')
		i++;
	path = ft_substr(line, i, ft_strlen(line) - i);
	if (!path)
		return (NULL);
	len = ft_strlen(path);
	while (len > 0 && (path[len - 1] == '\n' || path[len - 1] == ' '))
	{
		path[len - 1] = '\0';
		len--;
	}
	return (path);
}
void	path_counter(int code, t_game *data)
{
	char	*path;

	if (code == 1)
	{
		data->n_path++;
		path = data->n_tex_path;
	}
	else if (code == 2)
	{
		data->s_path++;
		path = data->s_tex_path;
	}
	else if (code == 3)
	{
		data->w_path++;
		path = data->w_tex_path;
	}
	else if (code == 4)
	{
		data->e_path++;
		path = data->e_tex_path;
	}
	if (data->n_path > 1 || data->s_path > 1
		|| data->w_path > 1 || data->e_path > 1)
		free(path);
}
