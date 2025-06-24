/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_minimap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irkalini <irkalini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 12:24:06 by irkalini          #+#    #+#             */
/*   Updated: 2025/06/24 17:07:13 by irkalini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	my_pixel_put(t_img *img, int x, int y, int color)
{
	char	*pixel;

	//to add safety check
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
			if (cub->file.map[i] == 'N' || cub->file.map[i] == 'S'\
				|| cub->file.map[i] == 'E' || cub->file.map[i] == 'W')
			{
				cub->player_x = j;
				cub->player_y = i;
				return ;
			}
			j++;
		}
		i++;
	}
}

// void	build_minimap(t_cub *cub)
// {

// }

int	render_minimap(t_cub *cub) //330x330
{
	t_img	*img;

	img = &cub->img;
	img->mlx_img = mlx_new_image(cub->mlx, 1920, 1080);
	img->addr = mlx_get_data_addr(img->mlx_img, &img->bpp, &img->line_len, \
			&img->endian);
	render_square(img, 1590, 0, 330, 0x00696969); //background
	render_square(img, 1755, 165, 5, 0x00FF0000); //player in the centre
	// render_square(img, 1590, 0, 30, 0x00101010); //a wall
	mlx_put_image_to_window(cub->mlx, cub->mlx_win, img->mlx_img, 0, 0); //x, y
	return (1);
}
