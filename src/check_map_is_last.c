/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_is_last.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltomasze <ltomasze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 18:15:46 by ltomasze          #+#    #+#             */
/*   Updated: 2025/03/04 18:16:32 by ltomasze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int ft_check_map_is_last(const char *filename)
{
    int fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        printf("Error: Cannot open file.\n");
        return 1;
    }

    char *line;
    int has_texture = 0;
    int has_color = 0;

    while ((line = get_next_line(fd)) != NULL)
    {
        if (line == NULL)
        {
            free(line);
            continue;
        }
        char *trimmed = ft_skip_whitespaces(line);
        if (*trimmed == '\0') 
        {
            free(line);
            continue;
        }
        if (ft_is_map_line(trimmed))
        {
            if (!has_texture || !has_color)
            {
                printf("Error: Map line found before texture or color lines.\n");
                free(line);
                close(fd);
                return 1;
            }
        }
        else if (ft_is_texture_line(trimmed))
        {
            has_texture = 1;
        }
        else if (ft_is_color_line(trimmed))
        {
            has_color = 1;
        }
        free(line);
    }
    close(fd);
    return 0;
}