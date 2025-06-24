/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irkalini <irkalini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 16:28:00 by irkalini          #+#    #+#             */
/*   Updated: 2025/06/24 16:47:39 by irkalini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	render_game(t_cub *cub)
{
	render_minimap(cub);
	return (0);
}

int	init_game(t_cub *cub)
{
	cub->mlx = mlx_init();
	if (!cub->mlx)
		return (0);
	cub->mlx_win = mlx_new_window(cub->mlx, 1920, 1080, "cub3d");
	if (!cub->mlx_win)
		return (free(cub->mlx), 0);
	mlx_loop_hook(cub->mlx, render_game, cub);
	mlx_loop(cub->mlx);
	return (1);
}
