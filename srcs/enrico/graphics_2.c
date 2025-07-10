/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrmarti <enrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:06:53 by enrmarti          #+#    #+#             */
/*   Updated: 2025/07/10 10:42:34 by enrmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	load_texture(t_cub *cub, char *path, int i)
{
	int		width;
	int		height;
	int		bpp;
	int		size_line;
	int 	endian;
	int		x;
	int		y;
	char	*data;
	void	*tmp;
	
	tmp = mlx_xpm_file_to_image(cub->mlx, path, &width, &height);
	if (!tmp)
		return ;
	data = mlx_get_data_addr(tmp, &bpp, &size_line, &endian);
	y = 0;
	while (y < TEXTURE_SIDE)
	{
		x = -1;
		while (++x < TEXTURE_SIDE)
			cub->textures[i][y * TEXTURE_SIDE + x] = *(unsigned int *) (data + y * size_line + x * (bpp / 8));
		y++;
	}
	mlx_destroy_image(cub->mlx, tmp);
}

void	init_textures(t_cub *cub)
{
	load_texture(cub, "textures/north.xpm", 0);
	load_texture(cub, "textures/south.xpm", 1);
	load_texture(cub, "textures/west.xpm", 2);
	load_texture(cub, "textures/east.xpm", 3);
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
	tex_x = (int) (wall_x * (double) TEXTURE_SIDE);
	if (data->side == 0 && data->ray_dir[0] > 0 )
		tex_x = TEXTURE_SIDE - tex_x - 1;
	if (data->side == 1 && data->ray_dir[1] < 0 )
		tex_x = TEXTURE_SIDE - tex_x - 1;
	return (tex_x);
}