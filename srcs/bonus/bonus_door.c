/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_door.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrmarti <enrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 13:09:51 by enrmarti          #+#    #+#             */
/*   Updated: 2025/07/10 17:19:51 by enrmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

typedef struct s_opener
{
	double	delta[2];
	double	ray_dir[2];
	double	side_dist[2];
	double	step[2];
	int		map_cord[2];
}	t_open;

void	find_door_step(t_play *player, t_open *op)
{
	if (op->ray_dir[0] < 0)
	{
		op->step[0] = -1;
		op->side_dist[0] = (player->x - op->map_cord[0]) * op->delta[0];
	}
	else
	{
		op->step[0] = 1;
		op->side_dist[0] = (op->map_cord[0] + 1.0
				- player->x) * op->delta[0];
	}
	if (op->ray_dir[1] < 0)
	{
		op->step[1] = -1;
		op->side_dist[1] = (player->y - op->map_cord[1]) * op->delta[1];
	}
	else
	{
		op->step[1] = 1;
		op->side_dist[1] = (op->map_cord[1] + 1.0
				- player->y) * op->delta[1];
	}
}

void	config_opener(t_cub *cub, t_open *op)
{
	op->ray_dir[0] = cub->player.dir[0];
	op->ray_dir[1] = cub->player.dir[1];
	op->map_cord[0] = (int) floor(cub->player.x);
	op->map_cord[1] = (int) floor(cub->player.y);
	op->delta[0] = fabs(1 / op->ray_dir[0]);
	op->delta[1] = fabs(1 / op->ray_dir[1]);
	find_door_step(&cub->player, op);
}

bool	short_dda(t_cub *cub, t_open *op)
{
	while (1)
	{
		if (op->side_dist[0] < op->side_dist[1])
		{
			op->side_dist[0] += op->delta[0];
			op->map_cord[0] += (int) op->step[0];
		}
		else
		{
			op->side_dist[1] += op->delta[1];
			op->map_cord[1] += (int) op->step[1];
		}
		if (op->side_dist[0] > 3 || op->side_dist[1] > 3)
			return (false);
		if (cub->file.map[op->map_cord[1]][op->map_cord[0]] == 'D')
			return (true);
	}
}

void	open_door(t_cub *cub)
{
	t_open op;
	
	config_opener(cub, &op);
	if (short_dda(cub, &op))
	{
		printf("DOOOOOOOOR!\n");
	}
	else
		printf("NO\n");
}