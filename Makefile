# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbany <mbany@student.42warsaw.pl>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/22 13:48:19 by ltomasze          #+#    #+#              #
#    Updated: 2025/04/06 15:46:44 by mbany            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
SOURCES = src/get_next_line.c src/main.c \
src/check/check.c \
src/check/check_line.c \
src/check/check_tcm.c \
src/check/check_tcm1.c \
src/check/check_only_one_tc.c \
src/check/check_only_one_tc1.c \
src/check/check_textures.c \
src/check/check_textures1.c \
src/check/check_colours.c \
src/check/check_colours1.c \
src/check/check_map_is_last.c \
src/check/check_map_vertical_integrity.c \
src/check/check_map_characters.c \
src/check/check_map_player_count.c \
src/check/check_map_border.c \
src/check/check_map_border1.c \
src/check/check_map_border2.c \
src/check/check_map_border3.c \
src/check/check_utils.c \
src/parse/parse.c \
src/parse/parse1.c \
src/parse/parse2.c \
src/key.c \
src/key2.c \
src/map.c \
src/free.c \
src/window.c \
src/window2.c \
src/raycasting.c \
src/raycasting2.c \
src/textures.c \
src/init_game.c\
src/error.c\

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