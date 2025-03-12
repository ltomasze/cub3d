/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltomasze <ltomasze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 13:18:25 by ltomasze          #+#    #+#             */
/*   Updated: 2025/03/12 13:20:10 by ltomasze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int ft_is_tcmnl_line(char *line)
{
    line = ft_skip_whitespaces(line);

    if (*line == '\0' || *line == '\n')
        return 0;
    if (ft_is_texture_line(line))
        return 0;
    if (ft_is_color_line(line))
        return 0;
    if (ft_is_map_line(line))
        return 0;

    return 1; // Linia jest niepoprawna
}

int ft_check_line(const char *filename)
{
    int fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        printf("Error: Cannot open file %s\n", filename);
        return 1;
    }

    char *line;
    int line_number = 1;
    int error_found = 0;

    while ((line = get_next_line(fd)) != NULL)
    {
        if (ft_is_tcmnl_line(line))
        {
            printf("Error: Invalid line %d\n", line_number);
            error_found = 1;
        }
        free(line);
        line_number++;
    }
    close(fd);

    return error_found;
}