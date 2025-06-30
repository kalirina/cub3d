/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrmarti <enrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 16:32:03 by enrmarti          #+#    #+#             */
/*   Updated: 2025/06/30 18:55:12 by enrmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	put_pixel(int x, int y, int color, t_cub *cub)
{
	int	index;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return;
	index = y * cub->line_len + x * cub->bpp / 8;
	cub->addr[index] = color & 0xFF;
	cub->addr[index + 1] = (color >> 8) & 0xFF;
	cub->addr[index + 2] = (color >> 16) & 0xFF;
}

// int	render_square(t_cub *cub, int x, int y, int size, int color)
// {
// 	int	i;
// 	int	j;

// 	i = y;
// 	while (i < y + size)
// 	{
// 		j = x;
// 		while (j < x + size)
// 			put_pixel(j++, i, color, cub);
// 		i++;
// 	}
// 	return (1);
// }

void clear_image(t_cub *cub)
{
	int	y;
	int	x;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			put_pixel(x, y, 0, cub);
			x++;
		}
		y++;
	}
}
