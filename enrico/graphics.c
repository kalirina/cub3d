/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrmarti <enrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 16:32:03 by enrmarti          #+#    #+#             */
/*   Updated: 2025/06/25 16:25:28 by enrmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	put_pixel(int x, int y, int color, t_cub *cub)
{
	int	index;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
    	return;
	index = y * cub->size_line + x * cub->bpp / 8;
	cub->data[index] = color & 0xFF;
	cub->data[index + 1] = (color >> 8) & 0xFF;
	cub->data[index + 2] = (color >> 16) & 0xFF;
}

// void draw_square(int x, int y, int size, int color, t_cub *game)
// {
//     for(int i = 0; i < size; i++)
//         put_pixel(x + i, y, color, game);
//     for(int i = 0; i < size; i++)
//         put_pixel(x, y + i, color, game);
//     for(int i = 0; i < size; i++)
//         put_pixel(x + size, y + i, color, game);
//     for(int i = 0; i < size; i++)
//         put_pixel(x + i, y + size, color, game);
// }

void clear_image(t_cub *cub)
{
	int y;
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
