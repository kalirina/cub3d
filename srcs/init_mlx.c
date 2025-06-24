/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrmarti <enrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 16:28:00 by irkalini          #+#    #+#             */
/*   Updated: 2025/06/24 14:54:10 by enrmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	init_game(t_cub *cub)
{
	cub->mlx = mlx_init();
	if (!cub->mlx)
		return (0);
	cub->win = mlx_new_window(cub->mlx, 1920, 1080, "cub3d");
	if (!cub->win)
		return (free(cub->mlx), 0);
	
	mlx_loop(cub->mlx);
	return (1);
}
