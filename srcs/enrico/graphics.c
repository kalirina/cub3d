/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irkalini <irkalini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 16:32:03 by enrmarti          #+#    #+#             */
/*   Updated: 2025/07/04 15:01:23 by irkalini         ###   ########.fr       */
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

int	get_wall_color(t_dda *data)
{
	if (data->wall_type == 'N')
		return (0xFF0000);
	if (data->wall_type == 'S')
		return (0xFFFF00);
	if (data->wall_type == 'W')
		return (0x00FF00);
	if (data->wall_type == 'E')
		return (0x0000FF);
	return (0xAAAAAA);
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
		put_pixel(x, y++, cub->file.ceil_color, cub);
	while (y < end)
		put_pixel(x, y++, get_wall_color(data), cub);
	while (y < HEIGHT)
		put_pixel(x, y++, cub->file.floor_color, cub);
}

double	get_line_height(t_dda *data, t_play *player)
{
	double	perp_dist;
	int		line_height;

	if (data->ray_dir[0] == 0 && data->side == 0)
		return (HEIGHT);
	if (data->ray_dir[1] == 0 && data->side != 0)
		return (HEIGHT);
	if (data->side == 0)
		perp_dist = (data->map_cord[0] - player->x
				+ (1 - data->step[0]) / 2) / data->ray_dir[0];
	else
		perp_dist = (data->map_cord[1] - player->y
				+ (1 - data->step[1]) / 2) / data->ray_dir[1];
	line_height = (int)(HEIGHT / perp_dist);
	return (line_height);
}
