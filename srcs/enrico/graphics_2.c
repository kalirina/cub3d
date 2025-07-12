/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrmarti <enrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:06:53 by enrmarti          #+#    #+#             */
/*   Updated: 2025/07/12 09:23:48 by enrmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	load_texture(t_cub *cub, void *tmp, int i, int y)
{
	int		bpp;
	int		size_line;
	int		endian;
	int		x;
	char	*data;	

	data = mlx_get_data_addr(tmp, &bpp, &size_line, &endian);
	while (y < TEXTURE_SIDE)
	{
		x = 0;
		while (x < TEXTURE_SIDE)
		{
			cub->textures[i][y * TEXTURE_SIDE + x] = *(unsigned int *)
				(data + y * size_line + x * (bpp / 8));
			x++;
		}
		y++;
	}
	mlx_destroy_image(cub->mlx, tmp);
}

void	init_textures(t_cub *cub)
{
	void	*tmp;
	int		width;
	int		height;

	cub->textures = malloc(sizeof(unsigned int *) * 4);
	for(int i = 0; i < 4; i++)
		cub->textures[i] = malloc(sizeof(unsigned int) * TEXTURE_SIDE * TEXTURE_SIDE);
	tmp = mlx_xpm_file_to_image(cub->mlx, cub->file.no_t, &width, &height);
	if (!tmp)
		return ;
	load_texture(cub, tmp, 0, 0);
	tmp = mlx_xpm_file_to_image(cub->mlx, cub->file.so_t, &width, &height);
	if (!tmp)
		return ;
	load_texture(cub, tmp, 1, 0);
	tmp = mlx_xpm_file_to_image(cub->mlx, cub->file.we_t, &width, &height);
	if (!tmp)
		return ;
	load_texture(cub, tmp, 2, 0);
	tmp = mlx_xpm_file_to_image(cub->mlx, cub->file.ea_t, &width, &height);
	if (!tmp)
		return ;
	load_texture(cub, tmp, 3, 0);
}

int	find_texture_x(t_dda *data, t_play *player)
{
	double	wall_x;
	int		tex_x;

	if (data->side == 1)
		wall_x = player->x + data->perp_dist * data->ray_dir[0];
	else
		wall_x = player->y + data->perp_dist * data->ray_dir[1];
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (double) TEXTURE_SIDE);
	if (data->side == 0 && data->ray_dir[0] > 0)
		tex_x = TEXTURE_SIDE - tex_x - 1;
	if (data->side == 1 && data->ray_dir[1] < 0)
		tex_x = TEXTURE_SIDE - tex_x - 1;
	return (tex_x);
}
