# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ltomasze <ltomasze@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/22 13:48:19 by ltomasze          #+#    #+#              #
#    Updated: 2025/03/22 15:26:28 by ltomasze         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
SOURCES = src/get_next_line.c src/main.c \
src/check_line.c \
src/check_tcm.c \
src/check_tcm1.c \
src/check_only_one_tc.c \
src/check_only_one_tc1.c \
src/check_textures.c \
src/check_colours.c \
src/check_colours1.c \
src/check_map_is_last.c \
src/check_map_vertical_integrity.c \
src/check_map_characters.c \
src/check_map_player_count.c \
src/check_map_border.c \
src/check_map_border1.c \
src/check_map_border2.c \
src/check_map_border3.c \
src/check_utils.c \

OBJECTS = $(SOURCES:%.c=%.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror -Iincludes -g
LIBFT = libft/libft.a
MINILIBX = minilibx-linux/libmlx_Linux.a

all: $(NAME)

$(LIBFT):
	$(MAKE) -C libft

$(MINILIBX):
	$(MAKE) -C minilibx-linux

$(NAME): $(OBJECTS) $(MINILIBX) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJECTS) $(LIBFT) $(MINILIBX) -o $(NAME) -lXext -lX11 -lm -lz -D LINUX -no-pie

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS)
	$(MAKE) -C libft clean
	$(MAKE) -C minilibx-linux clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C libft fclean
	$(MAKE) -C minilibx-linux clean

re: fclean all

full: all clean

.PHONY: all clean fclean re full