/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irkalini <irkalini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 12:21:29 by irkalini          #+#    #+#             */
/*   Updated: 2025/07/12 13:29:41 by irkalini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include "../get_next_line/get_next_line.h"
# include "../libft/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <stdbool.h>
# include <math.h>
# include "../mlx_linux/minilibx-linux/mlx.h"

# define WIDTH 1920
# define HEIGHT 1080

# define W 119
# define A 97
# define S 115
# define D 100
# define LEFT 65361
# define RIGHT 65363
# define ESC 65307

# define TEXTURE_SIDE 128

# define PI 3.14159265359
# define FOV 66

# define ROT_KEY_SPEED 0.025
# define MOVE_SPEED 0.025
# define ROT_MOUS_SPEED 0.0025
# define MINIMAP_SIZE 330
# define E 101
# define DOOR_OPEN 0
# define DOOR_CLOSED 1
# define DOOR_OPENING 2
# define DOOR_CLOSING 3

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
	int		player_pos[2];
	char	player_dir;
	int		max_len;
	int		start_map;
	char	*line;
	char	**map;
	char	*no_t;
	char	*so_t;
	char	*we_t;
	char	*ea_t;
	int		floor_color;
	int		ceil_color;
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
	float	scale;
	int		wall_color;
	int		space_color;
	int		player_color;
	int		door_color;
}	t_min;

typedef struct s_dda
{
	double	cam_pos;
	double	delta[2];
	double	ray_dir[2];
	double	side_dist[2];
	double	step[2];
	double	perp_dist;
	double	line_height;
	double	draw_start;
	double	draw_end;
	int		texture_index;
	int		map_cord[2];
	int		x;
	int		side;
	char	wall_type;
	bool	is_door;
}	t_dda;

typedef struct s_play
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

typedef struct s_door
{
	int		x;
	int		y;
	int		status;
	double	progress;
	double	speed;
}	t_door;

typedef struct s_cub
{
	t_file			file;
	t_play			*player;
	t_door			**doors;
	t_min			*min;
	unsigned int	**textures;
	void			*img;
	void			*mlx;
	void			*win;
	int				bpp;
	int				line_len;
	int				endian;
	int				n_doors;
	char			*addr;
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
void	find_player(t_cub *cub);
//minilibx
int		init_game(t_cub *cub);
//cleaning
void	free_split(char **split);
void	free_tokens(t_file *file, int i);
void	free_file_struct(t_cub *cub);
void	free_all(t_cub *cub);
//bonus
void	open_door(t_cub *cub);
void	check_doors(t_cub *cub);
t_door	*find_door(t_cub *cub, int x, int y);
bool	is_door_open(t_cub *cub, t_dda *data);
void	init_doors(t_cub *cub);
int		render_minimap(t_cub *cub);
int		init_min_struct(t_cub *cub);
void	clear_image_mini(t_cub *cub);
void	draw_pixel(int x, int y, int color, t_cub *cub);
int		mouse_move_handler(int x, int y, void *param);
void	move_bonus(t_play *player, t_cub *cub);
void	move_left_right(t_play *player, t_cub *cub, int key);
void	handle_movement_bonus(t_play *player, t_cub *cub);
//movements
void	put_pixel(int x, int y, int color, t_cub *cub);
int		key_pressed(int keycode, void *param);
int		key_released(int keycode, void *param);
int		safe_exit(void *param);
//graphics
void	init_textures(t_cub *cub);
int		allocate_textures(t_cub *cub);
int		find_texture_x(t_dda *data, t_play *player);
double	get_line_height(t_dda *data, t_play *player);
void	add_line_to_img(t_cub *cub, t_dda *data, int x, int tex_x);
//raycasting
void	raycasting(t_play *player, t_cub *cub);
void	init_dda(t_dda *t);

#endif
