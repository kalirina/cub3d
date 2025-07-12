/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_init_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrmarti <enrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 17:12:03 by enrmarti          #+#    #+#             */
/*   Updated: 2025/07/12 12:32:01 by enrmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

int	count_doors(char **map)
{
	int	x;
	int	y;
	int	count;

	count = 0;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'D')
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

void	empty_door(t_door *d, int x, int y)
{
	d->x = x;
	d->y = y;
	d->status = 1;
	d->progress = 1.0;
	d->speed = 1.5;
}

void	init_doors(t_cub *cub)
{
	int	x;
	int	y;
	int	i;

	i = 0;
	y = 0;
	cub->n_doors = count_doors(cub->file.map);
	if (cub->n_doors == 0)
		return ;
	cub->doors = malloc(sizeof(t_door *) * cub->n_doors);
	while (cub->file.map[y])
	{
		x = 0;
		while (cub->file.map[y][x])
		{
			if (cub->file.map[y][x] == 'D')
			{
				cub->doors[i] = malloc(sizeof(t_door));
				empty_door(cub->doors[i], x, y);
				i++;
			}
			x++;
		}
		y++;
	}
}
