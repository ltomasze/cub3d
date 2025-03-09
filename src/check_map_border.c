/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_border.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltomasze <ltomasze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 18:19:41 by ltomasze          #+#    #+#             */
/*   Updated: 2025/03/09 12:47:54 by ltomasze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"


int ft_get_map_height(char **map) 
{
    int count = 0;
    while (map[count] != NULL)
        count++;
    return count;
}

int ft_get_map_width(char **map)
{
    int max_width = 0;
    int i = 0;
    while (map[i] != NULL)
    {
        int len = ft_strlen(map[i]);
        if (len > max_width)
            max_width = len;
        i++;
    }
    return max_width;
}

char **ft_get_map_lines(const char *filename, int *height, int *width) 
{
    int fd = open(filename, O_RDONLY);
    if (fd == -1) 
    {
        printf("Error: Cannot open file %s\n", filename);
        return NULL;
    }
    
    char **map = NULL;
    int count = 0;
    int max_width = 0;
    int map_started = 0;
    char *line = NULL;
    
    while ((line = get_next_line(fd)) != NULL) 
    {
        if (!map_started && ft_is_map_line(line)) 
        {
            map_started = 1;
        }
        if (map_started) 
        {
            if (line[0] == '\n' || line[0] == '\0')
            {
                free(line);
                break;
            }
            char **tmp = malloc(sizeof(char *) * (count + 1));
            if (!tmp) 
            {
                printf("Error: Memory allocation failed\n");
                close(fd);
                return NULL;
            }
            int i = 0;
            while (i < count) 
            {
                tmp[i] = map[i];
                i++;
            }
            // Zwalniamy starą tablicę (same wskaźniki nie są zwalniane, bo nadal wskazują na zaalokowane linie)
            free(map);
            map = tmp;
            map[count] = line;
            int len = ft_strlen(line);
            if (len > max_width)
                max_width = len;
            count++;
        } 
        else 
        {
            free(line);
        }
    }
    close(fd);
    char **tmp = malloc(sizeof(char *) * (count + 1));
    if (!tmp) 
    {
        printf("Error: Memory allocation failed\n");
        return NULL;
    }
     int i = 0;
    while (i < count) 
    {
        tmp[i] = map[i];
        i++;
    }
    free(map);
    map = tmp;
    map[count] = NULL;
    
    *height = count;
    *width = max_width;
    return map;
    
}

int ft_check_floor_border(char **map, int height, int max_width)
{
    (void)max_width;
    int y = 0;
    while (y < height)
    {
        int row_len = ft_strlen(map[y]);
        int x = 0;
        while (x < row_len)
        {
            if (map[y][x] == '0')
            {
                int dy = -1;
                while (dy <= 1)
                {
                    int dx = -1;
                    while (dx <= 1)
                    {
                        if (!(dy == 0 && dx == 0))
                        {
                            int ny = y + dy;
                            int nx = x + dx;
                            char neighbor;
                            if (ny < 0 || ny >= height)
                                neighbor = ' ';
                            else
                            {
                                int neighbor_len = ft_strlen(map[ny]);
                                if (nx < 0 || nx >= neighbor_len)
                                    neighbor = ' ';
                                else
                                    neighbor = map[ny][nx];
                            }
                            if (neighbor != '1' && neighbor != '0' &&
                                neighbor != 'N' && neighbor != 'S' &&
                                neighbor != 'W' && neighbor != 'E')
                            {
                                printf("Error: Missing border for floor\n");
                                return 1;
                            }
                        }
                        dx++;
                    }
                    dy++;
                }
            }
            x++;
        }
        y++;
    }
    return 0;
}

void ft_free_map(char **map, int height)
{
    int i = 0;
    while (i < height)
    {
        free(map[i]);
        i++;
    }
    free(map);
}

int ft_check_map_border(const char *filename)
{
    int height, width;
    char **map = ft_get_map_lines(filename, &height, &width);
    if (!map)
        return 1;
    if (ft_check_floor_border(map, height, width))
    {
        ft_free_map(map, height);
        return 1;
    }
    ft_free_map(map, height);
    return 0;
}