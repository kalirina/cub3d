/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_minimap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irkalini <irkalini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 12:24:06 by irkalini          #+#    #+#             */
/*   Updated: 2025/06/30 14:40:05 by irkalini         ###   ########.fr       */
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

// void	find_player(t_cub *cub)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (cub->file.map[i])
// 	{
// 		j = 0;
// 		while (cub->file.map[i][j])
// 		{
// 			if (cub->file.map[i][j] == 'N' || cub->file.map[i][j] == 'S'\
// 				|| cub->file.map[i][j] == 'E' || cub->file.map[i][j] == 'W')
// 			{
// 				cub->min.player_x = j;
// 				cub->min.player_y = i;
// 				return ;
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// }

void	draw_easy_minimap(t_cub * cub)
{
	int	i;
	int	j;

	i = 0;
	cub->min.scale = 30;
	cub->min.draw_y = 0;
	while (cub->file.map[i])
	{
		j = 0;
		cub->min.draw_x = 0;
		while (cub->file.map[i][j])
		{
			if (cub->file.map[i][j] == '1')
				draw_square(cub, cub->min.draw_x, cub->min.draw_y, cub->min.scale, 0x00101010);
			cub->min.draw_x += cub->min.scale;
			j++;
		}
		cub->min.draw_y += cub->min.scale;
		i++;
	}
}

int	render_minimap(t_cub *cub) //330x330
{
	if (cub->min.first)
	{
		clear_image_mini(cub);
		draw_square(cub, 0, 0, 330, 0x00696969); //background
		draw_easy_minimap(cub);
	}
	cub->min.first = 0;
	//render_square(cub, cub->min.player_x, cub->min.player_y, 6, 0x00FF0000); //player in the centre
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
	// find_player(cub);
	// min->player_x += 12;
	// min->player_y += 12;
	return (1);
}
