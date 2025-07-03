/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_minimap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irkalini <irkalini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 12:24:06 by irkalini          #+#    #+#             */
/*   Updated: 2025/07/03 16:38:30 by irkalini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	draw_pixel(int x, int y, int color, t_cub *cub)
{
	int	index;

	if (x < 0 || x >= 330 || y < 0 || y >= 330)
		return;
	index = y * cub->min.line_len + x * cub->min.bpp / 8;
	cub->min.addr[index] = color & 0xFF;
	cub->min.addr[index + 1] = (color >> 8) & 0xFF;
	cub->min.addr[index + 2] = (color >> 16) & 0xFF;
}

void clear_image_mini(t_cub *cub)
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

int	draw_square(t_cub *cub, int x, int y, int size, int color)
{
	int	i;
	int	j;

	i = y;
	while (i < y + size)
	{
		j = x;
		while (j < x + size)
			draw_pixel(j++, i, color, cub);
		i++;
	}
	return (1);
}

void	init_player_pos(t_cub *cub)
{
	int	i;
	int	j;

	i = 0;
	while (cub->file.map[i])
	{
		j = 0;
		while (cub->file.map[i][j])
		{
			if (cub->file.map[i][j] == 'N' || cub->file.map[i][j] == 'S'\
				|| cub->file.map[i][j] == 'E' || cub->file.map[i][j] == 'W')
			{
				cub->min.player_x = j * cub->min.scale + cub->min.scale / 2;
				cub->min.player_y = i * cub->min.scale + cub->min.scale / 2;
				//set angle
				return ;
			}
			j++;
		}
		i++;
	}
}

void	draw_tile(t_cub *cub, int screen_x, int screen_y, char wall)
{
	int	tile_color;
	int	x;
	int	y;

	if (wall == '1')
		tile_color = 0x00333333;
	else
		tile_color = 0x00CCCCCC;
	y = 0;
	while (y < cub->min.scale)
	{
		x = 0;
		while (x < cub->min.scale)
		{
			int px = screen_x + x;
			int py = screen_y + y;
			if (px >= 0 && px < MINIMAP_SIZE && py >= 0 && py < MINIMAP_SIZE)
				draw_pixel(px, py, tile_color, cub);
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
			if (screen_x + cub->min.scale < 0 || screen_x >= MINIMAP_SIZE ||
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
	offset_x = cub->player.x - (MINIMAP_SIZE / (2.0 * cub->min.scale));
	offset_y = cub->player.y - (MINIMAP_SIZE / (2.0 * cub->min.scale));
	draw_minimap(cub, offset_x, offset_y);
	draw_square(cub, MINIMAP_SIZE / 2 - 3, MINIMAP_SIZE / 2 - 3, 6, 0xFF0000);
	return (1);
}

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
	//init_player_pos(cub);
	return (1);
}
