/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltomasze <ltomasze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 12:48:26 by ltomasze          #+#    #+#             */
/*   Updated: 2025/03/13 12:51:47 by ltomasze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int check_path_exists(const char *path)
{
    if (ft_strlen(path) >= 1023)
    {
        printf("Error: Path too long\n");
        return 1;
    }
    char trimmed[1024];
    int i = 0;
    while (path[i] && i < 1023)
    {
         trimmed[i] = path[i];
         i++;
    }
    trimmed[i] = '\0';

    int len = ft_strlen(trimmed);
    while (len > 0 && (trimmed[len - 1] == ' ' ||
                       trimmed[len - 1] == '\t' ||
                       trimmed[len - 1] == '\n'))
    {
         trimmed[len - 1] = '\0';
         len--;
    }

    if (len == 0)
    {
         printf("Error: Empty path\n");
         return 1;
    }
    
    int fd;
    if (trimmed[len - 1] == '/')
    {
        fd = open(trimmed, O_RDONLY);
        if (fd == -1)
        {
            printf("Error: Directory not found: %s\n", trimmed);
            return 1;
        }
        close(fd);
        return 0;
    }
    else if (len >= 4 && ft_strncmp(trimmed + len - 4, ".xpm", 4) == 0)
    {
        fd = open(trimmed, O_RDONLY);
        if (fd == -1)
        {
            printf("Error: File not found: %s\n", trimmed);
            return 1;
        }
        close(fd);
        return 0;
    }
    else
    {
        printf("Error: Path '%s' does not end with '/' or '.xpm'\n", trimmed);
        return 1;
    }
}

int ft_check_textures(const char *filename)
{
    int fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        printf("Error: Cannot open file %s\n", filename);
        return 1;
    }

    char *line;
    int error_found = 0;

    while ((line = get_next_line(fd)) != NULL)
    {
        if (ft_is_texture_line(line))
        {
            char *path = ft_skip_whitespaces(line);
            while (*path && *path != ' ' && *path != '\t')
                path++;
            path = ft_skip_whitespaces(path);
            if (check_path_exists(path) == 1)
                error_found = 1;
        }
        free(line);
    }
    close(fd);
    return error_found;
}