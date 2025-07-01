/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrmarti <enrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 12:21:29 by irkalini          #+#    #+#             */
/*   Updated: 2025/07/01 09:59:36 by enrmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../get_next_line/get_next_line.h"
# include "../libft/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <stdbool.h>
# include <math.h>
# include "../mlx_linux/minilibx-linux/mlx.h"

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
# define FOV 66

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
	int		max_len;
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

typedef struct s_min
{
	void	*img;
	int		bpp;
	int		line_len;
	int		endian;
	char	*addr;
	float	player_x;
	float	player_y;
	float	scale;
	float	minimap_size;
	int		draw_x;
	int		draw_y;
	int		speed;
	int		first;
}	t_min;

typedef struct	s_dda
{
	double	cam_pos;
	double	delta[2];
	double	ray_dir[2];
	double	res[2];
	double	side_dist[2];
	double	step[2];
	int		map_cord[2];
	int		x;
	int		side;
	char	wall_type;
}	t_dda;

typedef struct	s_play
{
	double	x;
	double	y;
	double	dir[2];
	double	cam[2];
	bool	key_up;
	bool	key_down;
	bool	key_left;
	bool	key_right;
	bool	left_rotate;
	bool	right_rotate;
}	t_play;

typedef struct s_cub
{
	t_file	file;
	t_play	player;
	void	*img;
	void	*mlx;
	void	*win;
	int		bpp;
	int		line_len;
	int		endian;
	char	*addr;
	t_min	min;
}	t_cub;

//parsing
int		is_valid_extension(char *filename, char *ext);
int		parsing(t_cub *cub, char *filename);
int		read_file(t_file *file, char *filename);
int		set_color(t_file *file, int i, int num);
int		is_empty_line(char *line);
int		get_tokens(char *line, t_file *file);
int		read_map_1(t_file *file);
int		read_map_2(t_file *file, char *filename);
int		is_closed_map(t_file *file);
void	drain_gnl(t_file *file);
int		init_file_struct(t_cub *cub);
int		is_digit_string(char *str);
//minilibx
int		init_game(t_cub *cub);
//cleaning
void	free_split(char **split);
void	free_tokens(t_file *file, int i);
void	free_file_struct(t_cub *cub);
//bonus
int		render_minimap(t_cub *cub);
int		init_min_struct(t_cub *cub);
void	clear_image_mini(t_cub *cub);
//movements
void	put_pixel(int x, int y, int color, t_cub *cub);
int		key_pressed(int keycode, t_play *player);
int		key_released(int keycode, t_play	*player);
void	handle_movement(t_play *player);
int		safe_exit(int data);
void	clear_image(t_cub *cub);
// int		render_square(t_cub *cub, int x, int y, int size, int color);
//graphics
void	add_line_to_img(t_cub *cub, t_dda *data, double line_height, int x);
//raycasting
void	raycasting(t_play *player, t_cub *cub);

#endif
