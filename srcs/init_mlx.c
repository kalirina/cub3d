/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irkalini <irkalini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 16:28:00 by irkalini          #+#    #+#             */
/*   Updated: 2025/06/30 18:07:42 by irkalini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	render_game(t_cub *cub)
{
	handle_movement(&cub->player);
	clear_image(cub);
	render_square(cub, cub->player.x, cub->player.y, 10, 0xFF0000);
	//render_main_frame(cub); //raycasting goes there
	render_minimap(cub);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img, 0, 0); //x, y
	mlx_put_image_to_window(cub->mlx, cub->win, cub->min.img, 1590, 0);
	return (0);
}

void	init_player(t_play *player, int x, int y, int angle)
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
	init_player(&cub->player, 960, 540, 0);
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
	if (!init_min_struct(cub))
		return (0);
	mlx_hook(cub->win, 2, 1L<<0, key_pressed, &cub->player);
	mlx_hook(cub->win, 3, 1L<<1, key_released, &cub->player);
	mlx_hook(cub->win, 17, 0, safe_exit, &cub);
	mlx_loop_hook(cub->mlx, render_game, cub);
	mlx_loop(cub->mlx);
	return (1);
}
