/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_minimap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrmarti <enrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 12:24:06 by irkalini          #+#    #+#             */
/*   Updated: 2025/07/11 16:55:29 by enrmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

void	draw_pixel(int x, int y, int color, t_cub *cub)
{
	int	index;

	if (x < 0 || x >= 330 || y < 0 || y >= 330)
		return ;
	index = y * cub->min.line_len + x * cub->min.bpp / 8;
	cub->min.addr[index] = color & 0xFF;
	cub->min.addr[index + 1] = (color >> 8) & 0xFF;
	cub->min.addr[index + 2] = (color >> 16) & 0xFF;
}

int	draw_square(t_cub *cub, int x, int y, int size)
{
	int	i;
	int	j;

	i = y;
	while (i < y + size)
	{
		j = x;
		while (j < x + size)
			draw_pixel(j++, i, cub->min.player_color, cub);
		i++;
	}
	return (1);
}

void	draw_tile(t_cub *cub, int screen_x, int screen_y, char wall)
{
	int	x;
	int	y;
	int	px;
	int	py;

	y = 0;
	while (y < cub->min.scale)
	{
		x = 0;
		while (x < cub->min.scale)
		{
			px = screen_x + x;
			py = screen_y + y;
			if (px >= 0 && px < MINIMAP_SIZE && py >= 0 && py < MINIMAP_SIZE)
			{
				if (wall == '1')
					draw_pixel(px, py, cub->min.wall_color, cub);
				else if (wall != 'P')
					draw_pixel(px, py, cub->min.space_color, cub);
			}
			x++;
		}
		y++;
	}
}

void	draw_minimap(t_cub *cub, double offset_x, double offset_y)
{
	int	map_i;
	int	map_j;
	int	screen_x;
	int	screen_y;

	map_i = 0;
	while (cub->file.map[map_i])
	{
		map_j = 0;
		while (cub->file.map[map_i][map_j])
		{
			screen_x = (map_j - offset_x) * cub->min.scale;
			screen_y = (map_i - offset_y) * cub->min.scale;
			if (screen_x + cub->min.scale < 0 || screen_x >= MINIMAP_SIZE || \
				screen_y + cub->min.scale < 0 || screen_y >= MINIMAP_SIZE)
			{
				map_j++;
				continue ;
			}
			draw_tile(cub, screen_x, screen_y, cub->file.map[map_i][map_j]);
			map_j++;
		}
		map_i++;
	}
}

int	render_minimap(t_cub *cub)
{
	double	offset_x;
	double	offset_y;

	clear_image_mini(cub);
	offset_x = cub->player->x - (MINIMAP_SIZE / (2.0 * cub->min.scale));
	offset_y = cub->player->y - (MINIMAP_SIZE / (2.0 * cub->min.scale));
	draw_minimap(cub, offset_x, offset_y);
	draw_square(cub, MINIMAP_SIZE / 2 - 3, MINIMAP_SIZE / 2 - 3, 6);
	return (1);
}
