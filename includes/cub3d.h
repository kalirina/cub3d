/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irkalini <irkalini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 12:21:29 by irkalini          #+#    #+#             */
/*   Updated: 2025/06/16 15:01:26 by irkalini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include "../get_next_line/get_next_line.h"
#include "../libft/libft.h"
#include <stdio.h>
#include <fcntl.h>

typedef struct s_col
{
	int	r;
	int	g;
	int	b;
}	t_col;

typedef struct s_file
{
	char	**tok;
	int		data_count;
	int		fd;
	int		i;
	int		player_found;
	int		max_length;
	int		start_map;
	char	*line;
	char	**map;
	char	*no_t;
	char	*so_t;
	char	*we_t;
	char	*ea_t;
	t_col	floor;
	t_col	ceil;
}	t_file;

typedef struct s_cub
{
	t_file	file;
}	t_cub;

//parsing
int		is_valid_extension(char *filename, char *ext);
int		parsing(t_cub *cub, char *filename);
int		read_file(t_file *file, char *filename);
int		set_color(t_file *file, int i, int num);
int		is_empty_line(char *line);
int		get_tokens(char *line, t_file *file);
void	free_tokens(t_file *file);
int		read_map_1(t_file *file);
int		read_map_2(t_file *file, char *filename);

#endif
