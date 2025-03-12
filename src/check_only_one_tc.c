/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_only_one_tc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltomasze <ltomasze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:04:26 by ltomasze          #+#    #+#             */
/*   Updated: 2025/03/12 15:04:49 by ltomasze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int ft_check_only_one_tc(const char *filename)
{
    int fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        printf("Error: Cannot open file %s\n", filename);
        return 1;
    }

    char *line;
    int count_no = 0, count_so = 0, count_we = 0, count_ea = 0, count_f = 0, count_c = 0;

    while ((line = get_next_line(fd)) != NULL)
    {
        char *trim_line = ft_skip_whitespaces(line);

        if (ft_strncmp(trim_line, "NO", 2) == 0)
            count_no++;
        else if (ft_strncmp(trim_line, "SO", 2) == 0)
            count_so++;
        else if (ft_strncmp(trim_line, "WE", 2) == 0)
            count_we++;
        else if (ft_strncmp(trim_line, "EA", 2) == 0)
            count_ea++;
        else if (trim_line[0] == 'F')
            count_f++;
        else if (trim_line[0] == 'C')
            count_c++;

        free(line);
    }
    close(fd);

    if (count_no != 1 || count_so != 1 || count_we != 1 || count_ea != 1 || count_f != 1 || count_c != 1)
    {
        printf("Error: Incorrect number of texture/color lines (NO: %d, SO: %d, WE: %d, EA: %d, F: %d, C: %d)\n",
               count_no, count_so, count_we, count_ea, count_f, count_c);
        return 1;
    }

    return 0;
}