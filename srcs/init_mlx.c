/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irkalini <irkalini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 16:28:00 by irkalini          #+#    #+#             */
/*   Updated: 2025/06/25 16:43:59 by irkalini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	render_game(t_cub *cub)
{
	render_minimap(cub);
	return (0);
}

void	move_player(t_cub *cub, int	key)
{
	if (key == 119)
		cub->min.player_y += cub->min.speed;
	if (key == 115)
		cub->min.player_y -= cub->min.speed;
	if (key == 97)
		cub->min.player_x -= cub->min.speed;
	if (key == 100)
		cub->min.player_x += cub->min.speed;
}

int	key_manager(int keycode, t_cub *cub)
{
	if (keycode == 119) //W
		move_player(cub, keycode);
	else if (keycode == 97) //A
		move_player(cub, keycode);
	else if (keycode == 115) //S
		move_player(cub, keycode);
	else if (keycode == 100) //D
		move_player(cub, keycode);
	return (0);
}

void	init_min_struct(t_cub *cub)
{
	t_min	*min;

	min = &cub->min;
	find_player(cub);
	min->player_x += 12;
	min->player_y += 12;
}

int	init_game(t_cub *cub)
{
	cub->mlx = mlx_init();
	if (!cub->mlx)
		return (0);
	cub->mlx_win = mlx_new_window(cub->mlx, 1920, 1080, "cub3d");
	if (!cub->mlx_win)
		return (free(cub->mlx), 0);
	init_min_struct(cub);
	mlx_key_hook(cub->mlx_win, key_manager, cub);
	mlx_loop_hook(cub->mlx, render_game, cub);
	mlx_loop(cub->mlx);
	return (1);
}
