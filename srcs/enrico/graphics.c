/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrmarti <enrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 16:32:03 by enrmarti          #+#    #+#             */
/*   Updated: 2025/07/01 10:29:24 by enrmarti         ###   ########.fr       */
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

int get_wall_color(t_dda *data)
{
	if (data->wall_type == 'N')
		return 0xFF0000; // red
	if (data->wall_type  == 'S')
		return 0xFFFF00; // yellow
	if (data->wall_type  == 'W')
			return 0x00FF00; // green
	if (data->wall_type  == 'E')
		return 0x0000FF; // blue
	return 0xAAAAAA; //  gray
}


void	add_line_to_img(t_cub *cub, t_dda *data, double line_height, int x)
{
	double	start;
	double	end;
	int		y;

	start = HEIGHT / 2 - line_height / 2;
	end = HEIGHT / 2 + line_height / 2;
	if (start < 0)
		start = 0;
	if (end > HEIGHT)
		end = HEIGHT;
	y = 0;
	while (y < start)
		put_pixel(x, y++, 0xAAAAAA, cub);
	while (y < end)
		put_pixel(x, y++, get_wall_color(data), cub);
	while (y < HEIGHT)
		put_pixel(x, y++, 0xAAAAAA, cub);
}
