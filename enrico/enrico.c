/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enrico.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrmarti <enrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 10:00:32 by enrmarti          #+#    #+#             */
/*   Updated: 2025/06/24 17:39:24 by enrmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

// void	ciao(char **map, double playerX, double playerY, double playerOrientation)
// {
// 	double	dirX, dirY;
// 	double	planeX, planeY;

// 	// all the void ptrs will probably be in the main struct
// 	void	*mlx_ptr;
// 	void	*win_ptr;
// 	void	**texture_ptr;	// Array of pointers to the images
// 	int		width, height;  //probably defined in the beginning and stored in the main struct
	
// 	double	incrementAngle = 66 / width; //maybe?    //66 is the FOV
// }

void	init_player(t_player *player, int x, int y, int angle)
{
	player->x = (float) x;
	player->y = (float) y;
	player->angle = (float) angle;
	player->key_down = false;
	player->key_up = false;
	player->key_right = false;
	player->key_left = false;
	player->left_rotate = false;
	player->right_rotate = false;
}

int	init_game(t_cub *cub)
{
    init_player(cub->player, 5, 5, 0);
	cub->mlx = mlx_init();
	if (!cub->mlx)
		return (-1);
	cub->win = mlx_new_window(cub->mlx, WIDTH, HEIGHT, "cub3d");
	if (!cub->win)
		return (free(cub->mlx), -1);
	cub->img = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	if (!cub->img)
		return (free(cub->mlx), free(cub->win), -1);
	cub->data = mlx_get_data_addr(cub->img, &cub->bpp, &cub->size_line, &cub->endian);
	    mlx_put_image_to_window(cub->mlx, cub->win, cub->img, 0, 0);
	cub->map = malloc(sizeof(char *) * 11);
    cub->map[0] = "111111111111111";
    cub->map[1] = "100000000000001";
   	cub->map[2] = "100000000000001";
    cub->map[3] = "100000100000001";
    cub->map[4] = "100000000000001";
    cub->map[5] = "100000010000001";
    cub->map[6] = "100001000000001";
    cub->map[7] = "100000000000001";
    cub->map[8] = "100000000000001";
    cub->map[9] = "111111111111111";
    cub->map[10] = NULL;
	return (0);
}

bool touch(float px, float py, t_cub *cub)
{
    int x = px / BLOCK;
    int y = py / BLOCK;
    if(cub->map[y][x] == '1')
        return true;
    return false;
}

float distance(float x, float y){
    return sqrt(x * x + y * y);
}

float fixed_dist(float x1, float y1, float x2, float y2, t_cub *cub)
{
    float delta_x = x2 - x1;
    float delta_y = y2 - y1;
    float angle = atan2(delta_y, delta_x) - cub->player->angle;
    float fix_dist = distance(delta_x, delta_y) * cos(angle);
    return fix_dist;
}


void draw_line(t_player *player, t_cub *cub, float start_x, int i)
{
    float cos_angle = cos(start_x);
    float sin_angle = sin(start_x);
    float ray_x = player->x;
    float ray_y = player->y;
   
	while (!touch(ray_x, ray_y, cub))
	{
		ray_x += cos_angle;
		ray_y += sin_angle;
	}
    float dist = fixed_dist(player->x, player->y, ray_x, ray_y, cub);
	float height = (BLOCK / dist) * (WIDTH / 2);
    int start_y = (HEIGHT - height) / 2;
    int end = start_y + height;
    while(start_y < end)
    {
        put_pixel(i, start_y, 255, cub);
        start_y++;
    }
}


int		game_loop(t_cub	*cub)
{
	t_player	*player;
	handle_movement(player);
	clear_image(cub);
	float fraction = PI / 3 / WIDTH;
    float start_x = player->angle - PI / 6;
    int i = 0;
    while(i < WIDTH)
    {
        draw_line(player, cub, start_x, i);
        start_x += fraction;
        i++;
    }
    mlx_put_image_to_window(cub->mlx, cub->win, cub->img, 0, 0);
    return 0;
	return (0);
}

int main()
{
    t_cub	cub;
	
	init_game(&cub);

	mlx_hook(cub.win, 2, 1L<<0, key_pressed, &cub.player);
	mlx_hook(cub.win, 3, 1L<<1, key_released, &cub.player);

	mlx_loop_hook(cub.mlx, game_loop, &cub);
	mlx_loop(cub.mlx);
    return (0);
}