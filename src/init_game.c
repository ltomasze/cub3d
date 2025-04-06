/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbany <mbany@student.42warsaw.pl>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 15:11:49 by mbany             #+#    #+#             */
/*   Updated: 2025/04/05 19:52:58 by mbany            ###   ########.fr       */
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
	player->x = 587;
	player->y = 166;
	player->angle = PI / 1.8;
	player->key_up = false;
	player->key_down = false;
	player->key_left = false;
	player->key_right = false;
	player->rotate_left = false;
	player->rotate_right = false;
}

t_config	config;
void	init_game_struct(t_game *game)
{
	game->mlx = NULL;
	game->win = NULL;
	game->img = NULL;
	game->data = NULL;
	game->map = game->config.map;
	game->copy_map = NULL;
	game->map = game->config.map;
		
	game->n_tex_path = game->config.textures[0];
    game->s_tex_path = game->config.textures[1];
    game->w_tex_path = game->config.textures[2];
    game->e_tex_path = game->config.textures[3];

	game->n_path = 0;
    game->s_path = 0;
    game->w_path = 0;
    game->e_path = 0;

}

int	init_game(t_game *game, char *file)
{
	init_game_struct(game);
	init_player(&game->player);
	game->fd = open(file, O_RDONLY);
	/////////////////////////////////////////
	// if (!parsing(game))
	// 	return (error(INVALID_MAP, game));

	
	/////////////////////////////////////////
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



/*
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
            if (!line_redirection(line, &is_map_started))
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

int	line_redirection(char *line, int *is_map_started)
{
	if (!ft_strcmp(line, "\n"))
	{
		line = NULL;
		free(line);
		return (1);
	}
	if (!line_check(line))
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



int	line_check(char *line)
{
    if (!ft_strcmp(line, "\n"))
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
	*/
