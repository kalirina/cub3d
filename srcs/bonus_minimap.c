/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_minimap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irkalini <irkalini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 12:24:06 by irkalini          #+#    #+#             */
/*   Updated: 2025/06/25 16:43:38 by irkalini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	my_pixel_put(t_img *img, int x, int y, int color)
{
	char	*pixel;

	if (x < 0 || y < 0 || x >= 1920 || y >= 1080)
		return;
	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(int *)pixel = color;
}

int	render_square(t_img *img, int x, int y, int size, int color)
{
	int	i;
	int	j;

	i = y;
	while (i < y + size)
	{
		j = x;
		while (j < x + size)
			my_pixel_put(img, j++, i, color);
		i++;
	}
	return (1);
}

void	find_player(t_cub *cub)
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
				cub->min.player_x = j;
				cub->min.player_y = i;
				return ;
			}
			j++;
		}
		i++;
	}
}

void	easy_minimap(t_cub * cub)
{
	int	i;
	int	j;

	i = 0;
	cub->min.scale = 30;
	cub->min.draw_y = 0;
	while (cub->file.map[i])
	{
		j = 0;
		cub->min.draw_x = 1590;
		while (cub->file.map[i][j])
		{
			if (cub->file.map[i][j] == '1')
				render_square(&cub->img, cub->min.draw_x, cub->min.draw_y, cub->min.scale, 0x00101010);
			cub->min.draw_x += cub->min.scale;
			j++;
		}
		cub->min.draw_y += cub->min.scale;
		i++;
	}
}

int	render_minimap(t_cub *cub) //330x330
{
	t_img	*img;

	img = &cub->img;
	img->mlx_img = mlx_new_image(cub->mlx, 1920, 1080);
	img->addr = mlx_get_data_addr(img->mlx_img, &img->bpp, &img->line_len, \
			&img->endian);
	render_square(img, 1590, 0, 330, 0x00696969); //background
	easy_minimap(cub);
	render_square(img, cub->min.player_x, cub->min.player_y, 6, 0x00FF0000); //player in the centre
	mlx_put_image_to_window(cub->mlx, cub->mlx_win, img->mlx_img, 0, 0); //x, y
	return (1);
}
