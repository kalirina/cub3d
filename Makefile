# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: enrmarti <enrmarti@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/13 12:37:33 by irkalini          #+#    #+#              #
#    Updated: 2025/07/12 09:22:01 by enrmarti         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

SRCS = srcs/main.c srcs/parsing/parsing_1.c srcs/parsing/parsing_2.c \
		srcs/parsing/parsing_3.c srcs/parsing/utils_parse.c\
		srcs/clean.c srcs/init_mlx.c srcs/enrico/utils.c\
		srcs/enrico/graphics.c srcs/enrico/graphics_2.c\
		srcs/enrico/movements.c srcs/enrico/raycasting.c\
		get_next_line/get_next_line.c get_next_line/get_next_line_utils.c

BONUS =srcs/main.c srcs/parsing/parsing_1.c srcs/parsing/parsing_2.c \
		srcs/bonus/bonus_parsing_3.c srcs/parsing/utils_parse.c\
		srcs/bonus/bonus_clean.c srcs/bonus/bonus_init_mlx.c \
		srcs/bonus/bonus_raycasting.c srcs/bonus/bonus_init_2.c \
		srcs/bonus/bonus_graphics.c srcs/bonus/bonus_movements.c \
		srcs/enrico/utils.c srcs/bonus/bonus_raycasting_2.c \
		get_next_line/get_next_line.c get_next_line/get_next_line_utils.c \
		srcs/bonus/bonus_graphics_2.c srcs/bonus/bonus_door.c \
		srcs/bonus/bonus_wall_coll.c srcs/bonus/bonus_minimap.c \
		srcs/bonus/bonus_minimap_2.c srcs/bonus/bonus_mouse_rotate.c \

OBJS = ${SRCS:.c=.o}
BONUS_OBJS = ${BONUS:.c=.o}

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

bonus: $(LIBFT_A) $(MLX_A) $(BONUS_OBJS)
	$(CC) $(FLAGS) -o $(NAME) $(BONUS_OBJS) $(MLX_FLAGS) $(INCLUDES) $(LIBFT_A)

clean:
	rm -f $(OBJS) $(BONUS_OBJS)
	$(MAKE) clean -C $(MLX_DIR)
	$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	rm -f $(LIBFT_A)
	rm -f $(MLX_A)

re: fclean all

reb: fclean bonus
