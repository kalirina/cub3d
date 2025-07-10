/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrmarti <enrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 16:32:03 by enrmarti          #+#    #+#             */
/*   Updated: 2025/07/10 10:53:19 by enrmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	put_pixel(int x, int y, int color, t_cub *cub)
{
	int	index;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	index = y * cub->line_len + x * cub->bpp / 8;
	cub->addr[index] = color & 0xFF;
	cub->addr[index + 1] = (color >> 8) & 0xFF;
	cub->addr[index + 2] = (color >> 16) & 0xFF;
}

void	clear_image(t_cub *cub)
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


void	add_line_to_img(t_cub *cub, t_dda *data, int x)
{
	unsigned int	color;
	double	start;
	double	end;
	double	step;
	double	tex_pos;
	int		tex_x;
	int		tex_y;
	int		y;

	start = HEIGHT / 2 - data->line_height / 2;
	end = HEIGHT / 2 + data->line_height / 2;
	if (start < 0)
		start = 0;
	if (end > HEIGHT)
		end = HEIGHT;
	y = 0;
	tex_x = find_texture_x(data, &cub->player);
	step = 1.0 * TEXTURE_SIDE / data->line_height;
	tex_pos = (start - HEIGHT / 2 + data->line_height / 2) * step;
	while (y < start)
		put_pixel(x, y++, 0xAAAAAA, cub);
	while (y < end)
	{
		tex_y = (int) tex_pos & (TEXTURE_SIDE - 1);
		tex_pos += step;
		color = cub->textures[data->texture_index][TEXTURE_SIDE * tex_y + tex_x];
		put_pixel(x, y++, color, cub);
	}
	while (y < HEIGHT)
		put_pixel(x, y++, 0xAAAAAA, cub);
}

double	get_line_height(t_dda *data, t_play *player)
{
	double	line_height;

	if (data->ray_dir[0] == 0 && data->side == 0)
		return (HEIGHT);
	if (data->ray_dir[1] == 0 && data->side != 0)
		return (HEIGHT);
	if (data->side == 0)
		data->perp_dist = (data->map_cord[0] - player->x
				+ (1 - data->step[0]) / 2) / data->ray_dir[0];
	else
		data->perp_dist = (data->map_cord[1] - player->y
				+ (1 - data->step[1]) / 2) / data->ray_dir[1];
	line_height = HEIGHT / data->perp_dist;
	return (line_height);
}
