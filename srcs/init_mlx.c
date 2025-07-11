/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irkalini <irkalini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 16:28:00 by irkalini          #+#    #+#             */
/*   Updated: 2025/07/11 17:39:54 by irkalini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	render_game(t_cub *cub)
{
	handle_movement(cub->player, cub);
	raycasting(cub->player, cub);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img, 0, 0);
	return (0);
}

void	init_camera(t_play *player)
{
	double	length;

	length = tan((FOV * PI / 180.0) / 2.0);
	player->cam[0] = -player->dir[1] * length;
	player->cam[1] = player->dir[0] * length;
}

void	init_vectors(t_play *player, char direction)
{
	if (direction == 'N')
	{
		player->dir[0] = 0;
		player->dir[1] = -1;
	}
	else if (direction == 'S')
	{
		player->dir[0] = 0;
		player->dir[1] = 1;
	}
	else if (direction == 'E')
	{
		player->dir[0] = 1;
		player->dir[1] = 0;
	}
	else if (direction == 'W')
	{
		player->dir[0] = -1;
		player->dir[1] = 0;
	}
	init_camera(player);
}

void	init_player(t_play *player, double x, double y, char direction)
{

	player->x = x;
	player->y = y;
	init_vectors(player, direction);
	player->key_down = false;
	player->key_up = false;
	player->key_right = false;
	player->key_left = false;
	player->left_rotate = false;
	player->right_rotate = false;
	// player->move_speed = 0.05;
}

int	init_game(t_cub *cub)
{
	cub->player = malloc(sizeof(t_play));
	find_player(cub);
	init_player(cub->player, cub->file.player_pos[0] + 0.5, \
		cub->file.player_pos[1] + 0.5, cub->file.player_dir);
	cub->mlx = mlx_init();
	if (!cub->mlx)
		return (0);
	cub->win = mlx_new_window(cub->mlx, WIDTH, HEIGHT, "cub3d");
	if (!cub->win)
		return (free(cub->mlx), 0);
	cub->img = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	if (!cub->img)
		return (free(cub->mlx), free(cub->win), 0);
	cub->addr = mlx_get_data_addr(cub->img, &cub->bpp, &cub->line_len, \
			&cub->endian);
	init_textures(cub);
	mlx_hook(cub->win, 2, 1L << 0, key_pressed, cub);
	mlx_hook(cub->win, 3, 1L << 1, key_released, cub);
	mlx_hook(cub->win, 17, 0, safe_exit, cub);
	mlx_loop_hook(cub->mlx, render_game, cub);
	mlx_loop(cub->mlx);
	return (1);
}
