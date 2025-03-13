/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_colours.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltomasze <ltomasze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 14:49:36 by ltomasze          #+#    #+#             */
/*   Updated: 2025/03/13 14:50:52 by ltomasze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int ft_is_valid_color_line(char *line)
{
    // Pomijamy początkowe białe znaki
    line = ft_skip_whitespaces(line);

    // Sprawdzamy, czy linia zaczyna się od 'F' lub 'C'
    if (*line != 'F' && *line != 'C')
        return 0; // To nie jest linia koloru, więc nie sprawdzamy dalej

    line++; // Pomijamy literę 'F' lub 'C'

    // Pomijamy kolejne białe znaki po 'F' lub 'C'
    line = ft_skip_whitespaces(line);

    int count_numbers = 0;
    int count_commas = 0;

    while (*line)
    {
        if (*line >= '0' && *line <= '9') // Jeśli cyfra
        {
            count_numbers++;
            // Przechodzimy przez całą liczbę
            while (*line >= '0' && *line <= '9')
                line++;
        }
        else if (*line == ',') // Jeśli przecinek
        {
            count_commas++;
            line++; // Przechodzimy przecinek

            // Pomijamy białe znaki po przecinku
            line = ft_skip_whitespaces(line);

            // Jeśli po przecinku nie ma cyfry lub jest przecinek od razu, błąd
            if (*line < '0' || *line > '9')
            {
                printf("Error: Expected a digit after comma in color line\n");
                return 1;
            }
        }
        else if (*line == ' ' || *line == '\t' || *line == '\n')
        {
            // Jeśli napotkamy białe znaki, pomijamy je
            line++;
        }
        else // Jeśli napotkamy inny znak
        {
            printf("Error: Invalid character '%c' in color line\n", *line);
            return 1;
        }
    }

    // Po przejściu przez całą linię ponownie pomijamy białe znaki (na wszelki wypadek)
    // i sprawdzamy, czy doszliśmy do końca ciągu
    // (w tym momencie białe znaki już nie powinny występować)
    line = ft_skip_whitespaces(line);
    if (*line != '\0')
    {
        printf("Error: Unexpected character '%c' after color components\n", *line);
        return 1;
    }

    // Sprawdzenie formatu: powinna być dokładnie jedna linia z dwoma przecinkami (czyli trzy liczby)
    if (count_commas != 2 || count_numbers != 3)
    {
        printf("Error: Incorrect number format in color line\n");
        return 1;
    }

    return 0; // Linia koloru jest poprawna
}

int ft_check_color_range(char *line)
{
    // Pomijamy początkowe białe znaki
    line = ft_skip_whitespaces(line);

    // Zakładamy, że linia zaczyna się od 'F' lub 'C'
    if (*line != 'F' && *line != 'C')
        return 1; // Nie jest to linia koloru – ale to powinno być obsłużone przez ft_is_valid_color_line

    line++; // Pomijamy literę 'F' lub 'C'
    line = ft_skip_whitespaces(line); // Pomijamy białe znaki po prefiksie

    int i = 0;
    while (i < 3)
    {
        // Pomijamy białe znaki przed liczbą (na wszelki wypadek)
        line = ft_skip_whitespaces(line);

        // Konwertujemy liczbę przy pomocy ft_atoi (zakładamy, że ft_atoi jest poprawnie zaimplementowane)
        int value = ft_atoi(line);
        if (value < 0 || value > 255)
        {
            printf("Error: Color component %d is out of range (0-255)\n", value);
            return 1;
        }

        // Przechodzimy przez cyfry danej liczby
        while (*line >= '0' && *line <= '9')
            line++;

        // Pomijamy białe znaki po liczbie
        line = ft_skip_whitespaces(line);

        // Jeśli to nie była ostatnia liczba, oczekujemy przecinka i pomijamy go
        if (i < 2)
        {
            if (*line == ',')
                line++;
            line = ft_skip_whitespaces(line);
        }
        i++;
    }
    return 0;
}

int ft_check_colours(const char *filename)
{
    int fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        printf("Error: Could not open file %s\n", filename);
        return 1; // Błąd otwarcia pliku
    }

    char *line;
    while ((line = get_next_line(fd)) != NULL) // Odczytujemy plik linia po linii
    {
        char *trimmed = ft_skip_whitespaces(line);

        // Sprawdzamy, czy linia zaczyna się od 'F' lub 'C'
        if (*trimmed == 'F' || *trimmed == 'C')
        {
            if (ft_is_valid_color_line(trimmed) || ft_check_color_range(trimmed)) // Walidacja linii koloru
            {
                free(line);
                close(fd);
                return 1; // Błąd w linii koloru
            }
        }
        free(line);
    }

    close(fd);
    return 0; // Wszystkie linie kolorów są poprawne
}