/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrmarti <enrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 12:21:29 by irkalini          #+#    #+#             */
/*   Updated: 2025/06/25 16:49:32 by enrmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdbool.h>
# include <fcntl.h>
# include <stdlib.h>
# include <math.h> 
# include "mlx/mlx.h"

# define WIDTH 1920
# define HEIGHT 1080
# define BLOCK 64

# define W 119
# define A 97
# define S 115
# define D 100
# define LEFT 65361
# define RIGHT 65363
# define ESC 65307

# define PI 3.14159265359
# define FOV 66 * (PI / 180)

// typedef struct s_col
// {
// 	int	r;
// 	int	g;
// 	int	b;
// }	t_col;

// typedef struct s_file
// {
// 	char	**tok;
// 	int		data_count;
// 	int		fd;
// 	int		i;
// 	int		player_found;
// 	int		max_len;
// 	int		start_map;
// 	char	*line;
// 	char	**map;
// 	char	*no_t;
// 	char	*so_t;
// 	char	*we_t;
// 	char	*ea_t;
// 	t_col	floor;
// 	t_col	ceil;
// }	t_file;

typedef struct	s_player
{
	float	x;
	float	y;
	float	angle;

	bool	key_up;
    bool	key_down;
    bool	key_left;
    bool	key_right;

    bool	left_rotate;
    bool	right_rotate;
}	t_player;

typedef struct s_cub
{
//	t_file		file;
	t_player	player;
	void		*mlx;
	void		*win;
	void		*img;
	char		*data;
	int			bpp;
	int			size_line;
	int			endian;

	char		**map;
}	t_cub;

// //parsing
// int		is_valid_extension(char *filename, char *ext);
// int		parsing(t_cub *cub, char *filename);
// int		Endianness refers to the byte order used to store multi-byte values (like 32-bit color) in memory. It matters when interpreting color data from raw image memory.read_file(t_file *file, char *filename);
// int		set_color(t_file *file, int i, int num);
// int		is_empty_line(char *line);
// int		get_tokens(char *line, t_file *file);
// int		read_map_1(t_file *file);
// int		read_map_2(t_file *file, char *filename);
// int		is_closed_map(t_file *file);
// void	drain_gnl(t_file *file);
// int		init_file_struct(t_cub *cub);
// int		is_digit_string(char *str);
// //minilibx
// int		init_game(t_cub *cub);
// //cleaning
// void	free_split(char **split);
// void	free_tokens(t_file *file, int i);
// void	free_file_struct(t_cub *cub);

//MOVEMENTS
int		key_pressed(int keycode, t_player *player);
int		key_released(int keycode, t_player	*player);
void	handle_movement(t_player *player);


int		safe_exit();
void	clear_image(t_cub *cub);
void	draw_line(t_player *player, t_cub *cub, float start_x, int i);
void	draw_square(int x, int y, int size, int color, t_cub *game);


#endif
