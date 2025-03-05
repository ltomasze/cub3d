/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_continuous.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltomasze <ltomasze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 14:02:26 by ltomasze          #+#    #+#             */
/*   Updated: 2025/03/05 14:07:10 by ltomasze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int ft_check_map_continuous(const char *filename)
{
    int fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        printf("Error: Cannot open file.\n");
        return 1;
    }

    char *line;
    int map_started = 0;

    while ((line = get_next_line(fd)) != NULL)
    {
        char *trimmed = ft_skip_whitespaces(line);

        if (*trimmed == '\0')
        {
            free(line);
            continue;
        }

        if (ft_is_map_line(trimmed))
            map_started = 1;
        else if (map_started)
        {
            free(line);
            close(fd);
            printf("Error: Invalid map(wrong char before 1, or new line).\n");
            return 1;
        }

        free(line);
    }

    close(fd);
    return 0;
}