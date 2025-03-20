/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_only_one_tc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltomasze <ltomasze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:04:26 by ltomasze          #+#    #+#             */
/*   Updated: 2025/03/20 15:01:19 by ltomasze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int ft_check_texture_count(int no, int so, int we, int ea)
{
    if (no != 1 || so != 1 || we != 1 || ea != 1)
    {
        printf("Error: Incorrect number of texture lines (NO: %d, SO: %d, WE: %d, EA: %d)\n",
               no, so, we, ea);
        return 1;
    }
    return 0;
}

int ft_check_color_count(int f, int c)
{
    if (f != 1 || c != 1)
    {
        printf("Error: Incorrect number of color lines (F: %d, C: %d)\n", f, c);
        return 1;
    }
    return 0;
}

int ft_process_no_so_lines(const char *filename, int *no, int *so)
{
    int fd;
    char *line;
    char *trim_line;

    fd = ft_open_file(filename);
    if (fd == -1)
        return (1);
    while ((line = get_next_line(fd)) != NULL)
    {
        trim_line = ft_skip_whitespaces(line);
        if (ft_strncmp(trim_line, "NO", 2) == 0)
            (*no)++;
        else if (ft_strncmp(trim_line, "SO", 2) == 0)
            (*so)++;
        free(line);
    }
    close(fd);
    return (0);
}

int ft_process_we_ea_lines(const char *filename, int *we, int *ea)
{
    int fd;
    char *line;
    char *trim_line;

    fd = ft_open_file(filename);
    if (fd == -1)
        return (1);
    while ((line = get_next_line(fd)) != NULL)
    {
        trim_line = ft_skip_whitespaces(line);
        if (ft_strncmp(trim_line, "WE", 2) == 0)
            (*we)++;
        else if (ft_strncmp(trim_line, "EA", 2) == 0)
            (*ea)++;
        free(line);
    }
    close(fd);
    return (0);
}

int ft_process_color_lines(const char *filename, int *f, int *c)
{
    int fd;
    char *line;
    char *trim_line;

    fd = ft_open_file(filename);
    if (fd == -1)
        return (1);
    while ((line = get_next_line(fd)) != NULL)
    {
        trim_line = ft_skip_whitespaces(line);
        if (trim_line[0] == 'F')
            (*f)++;
        else if (trim_line[0] == 'C')
            (*c)++;
        free(line);
    }
    close(fd);
    return (0);
}

int ft_check_only_one_tc(const char *filename)
{
    int no;
    int so;
    int we;
    int ea;
    int f;
    int c;

    no = 0;
    so = 0;
    we = 0;
    ea = 0;
    f = 0;
    c = 0;
    if (ft_process_no_so_lines(filename, &no, &so) ||
        ft_process_we_ea_lines(filename, &we, &ea) ||
        ft_process_color_lines(filename, &f, &c))
        return (1);
    return (ft_check_texture_count(no, so, we, ea) ||
            ft_check_color_count(f, c));
}
