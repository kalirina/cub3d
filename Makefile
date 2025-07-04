# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: irkalini <irkalini@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/13 12:37:33 by irkalini          #+#    #+#              #
#    Updated: 2025/07/04 12:51:02 by irkalini         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

SRCS = srcs/main.c srcs/parsing/parsing_1.c srcs/parsing/parsing_2.c \
		srcs/parsing/parsing_3.c srcs/parsing/utils_parse.c\
		srcs/clean.c srcs/init_mlx.c \
		srcs/bonus/bonus_minimap.c srcs/bonus/bonus_minimap_2.c \
		srcs/enrico/graphics.c srcs/enrico/movements.c \
		srcs/enrico/raycasting.c \
		get_next_line/get_next_line.c get_next_line/get_next_line_utils.c

OBJS = ${SRCS:.c=.o}

INCLUDES = -I includes

LIBFT_A = ./libft/libft.a
LIBFT_DIR = ./libft

MLX_A = ./mlx_linux/minilibx-linux/libmlx.a
MLX_DIR = ./mlx_linux/minilibx-linux

MLX_FLAGS = -Lmlx_linux/minilibx-linux -l:libmlx_Linux.a -L/usr/lib -lX11 -lXext -lXrandr -lXrender -lm -lpthread -lbsd

CC = cc
FLAGS = -Wall -Wextra -Werror

all: $(LIBFT_A) $(MLX_A) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) -o $(NAME) $(OBJS) $(MLX_FLAGS) $(INCLUDES) $(LIBFT_A)

$(LIBFT_A):
	$(MAKE) -C $(LIBFT_DIR)

$(MLX_A):
	$(MAKE) -C $(MLX_DIR)

valgrind: all
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./cub3d small.cub

clean:
	rm -f $(OBJS)
	$(MAKE) clean -C $(MLX_DIR)
	$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	rm -f $(LIBFT_A)
	rm -f $(MLX_A)

re: fclean all
