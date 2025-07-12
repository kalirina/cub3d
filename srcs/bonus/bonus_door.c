/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_door.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irkalini <irkalini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 13:09:51 by enrmarti          #+#    #+#             */
/*   Updated: 2025/07/12 11:40:55 by enrmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

void	update_door(t_door *d, double delta)
{
	if (d->status == DOOR_CLOSING)
	{
		d->progress += delta * d->speed;
		if (d->progress >= 1.0)
		{
			d->progress = 1.0;
			d->status = DOOR_CLOSED;
		}
	}
	else if (d->status == DOOR_OPENING)
	{
		d->progress -= delta * d->speed;
		if (d->progress <= 0.0)
		{
			d->progress = 0.0;
			d->status = DOOR_OPEN;
		}
	}	
}

void	check_doors(t_cub *cub)
{
	int		i;
	double	delta;
	t_door	*d;

	delta = 0.016;
	i = 0;
	while (i < cub->n_doors)
	{
		d = cub->doors[i];
		update_door(d, delta);
		i++;
	}
}

void	change_door_status(t_door *d)
{
	if (d->status == DOOR_CLOSED)
		d->status = DOOR_OPENING;
	else if (d->status == DOOR_OPEN)
		d->status = DOOR_CLOSING;
}

bool	is_door_near(t_cub *cub, int door_y, int door_x)
{
	int	px;
	int	py;

	px = cub->player->x;
	py = cub->player->y;
	if (px == door_x)
	{
		if (py == door_y + 1 || py == door_y - 1)
			return (true);
	}
	if (py == door_y)
	{
		if (px == door_x + 1 || px == door_x - 1)
			return (true);
	}
	return (false);
}

void	open_door(t_cub *cub)
{
	int	i;

	i = 0;
	while (i < cub->n_doors)
	{
		if (is_door_near(cub, cub->doors[i]->y, cub->doors[i]->x))
			change_door_status(cub->doors[i]);
		i++;
	}
}
