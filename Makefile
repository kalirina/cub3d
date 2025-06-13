# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: irkalini <irkalini@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/13 12:37:33 by irkalini          #+#    #+#              #
#    Updated: 2025/06/13 14:49:39 by irkalini         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

SRCS = srcs/main.c srcs/parsing.c \
		get_next_line/get_next_line.c get_next_line/get_next_line_utils.c

OBJS = ${SRCS:.c=.o}

INCLUDES = -I includes

LIBFT_A = ./libft/libft.a
LIBFT_DIR = ./libft

CC = cc
FLAGS = -Wall -Wextra -Werror

all: $(LIBFT_A) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) -o $(NAME) $(OBJS) $(INCLUDES) $(LIBFT_A)

$(LIBFT_A):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -f $(OBJS)
	$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	rm -f $(LIBFT_A)

re: fclean all
