/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_minimap_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrmarti <enrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 10:50:28 by irkalini          #+#    #+#             */
/*   Updated: 2025/07/11 19:19:45 by enrmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

int	init_min_struct(t_cub *cub)
{
	t_min	*min;

	min = &cub->min;
	min->img = mlx_new_image(cub->mlx, 330, 330);
	if (!min->img)
		return (free(cub->mlx), free(cub->win), 0);
	min->addr = mlx_get_data_addr(min->img, &min->bpp, &min->line_len, \
			&min->endian);
	min->first = 1;
	min->scale = 30;
	min->wall_color = 0x00333333;
	min->space_color = 0x00CCCCCC;
	min->player_color = 0xFF0000;
	return (1);
}

void	clear_image_mini(t_cub *cub)
{
	int	y;
	int	x;

	y = 0;
	while (y < 330)
	{
		x = 0;
		while (x < 330)
		{
			draw_pixel(x, y, 0, cub);
			x++;
		}
		y++;
	}
}
