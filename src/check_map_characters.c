/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_characters.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltomasze <ltomasze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:31:40 by ltomasze          #+#    #+#             */
/*   Updated: 2025/03/06 13:32:36 by ltomasze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int ft_check_map_line_chars(const char *line)
{
    int i = 0;
    while (line[i])
    {
        if (line[i] != '1' && line[i] != '0' &&
            line[i] != 'N' && line[i] != 'S' &&
            line[i] != 'W' && line[i] != 'E' &&
            line[i] != ' ' && line[i] != '\t' &&
            line[i] != '\n' && line[i] != '\v' &&
            line[i] != '\f' && line[i] != '\r')
            return 1; // Zwracamy 1, gdy znaleziono niedozwolony znak
        i++;
    }
    return 0; // Wszystkie znaki są dozwolone
}

int ft_check_map_characters(const char *filename)
{
    int fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        printf("Error: Cannot open file.\n");
        return 1;
    }
    
    char *line;
    int error = 0;
    
    while ((line = get_next_line(fd)) != NULL)
    {
        char *trimmed = ft_skip_whitespaces(line);
        
        // Pomijamy puste linie (lub linie zawierające tylko białe znaki)
        if (*trimmed == '\0')
        {
            free(line);
            continue;
        }
        
        // Jeśli linia jest linią mapy, sprawdzamy, czy zawiera wyłącznie dozwolone znaki
        if (ft_is_map_line(trimmed))
        {
            if (ft_check_map_line_chars(trimmed))
            {
                error = 1;
                free(line);
                break;
            }
        }
        
        free(line);
    }
    
    close(fd);
    
    if (error)
    {
        printf("Error: Map line have forbidden characters.\n");
        return 1;
    }
    
    return 0;
}