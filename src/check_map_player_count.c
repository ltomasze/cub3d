/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_player_count.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltomasze <ltomasze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 14:03:54 by ltomasze          #+#    #+#             */
/*   Updated: 2025/03/06 14:05:16 by ltomasze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int ft_check_map_player_count(const char *filename)
{
    int fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        printf("Error: Cannot open file.\n");
        return 1;
    }

    char *line;
    int player_count = 0;

    while ((line = get_next_line(fd)) != NULL)
    {
        char *trimmed = ft_skip_whitespaces(line);

        if (*trimmed == '\0')
        {
            free(line);
            continue;
        }

        if (ft_is_map_line(trimmed))
        {
            int i = 0;
            while (trimmed[i])
            {
                if (trimmed[i] == 'N' || trimmed[i] == 'S' ||
                    trimmed[i] == 'W' || trimmed[i] == 'E')
                    player_count++;
                i++;
            }
        }

        free(line);
    }
    close(fd);

    if (player_count != 1)
    {
        printf("Error: Map must contain exactly one starting position (N, S, W, or E). Found: %d\n", player_count);
        return 1;
    }

    return 0;
}