/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irkalini <irkalini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 11:29:11 by irkalini          #+#    #+#             */
/*   Updated: 2025/07/12 11:29:35 by irkalini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

void	init_dda(t_dda *t)
{
	int	i;

	t->cam_pos = 0;
	t->perp_dist = 0;
	t->line_height = 0;
	t->draw_start = 0;
	t->draw_end = 0;
	t->texture_index = 0;
	t->x = 0;
	t->side = 0;
	t->wall_type = 0;
	t->is_door = false;
	t->hit = false;
	i = -1;
	while (++i < 2)
	{
		t->delta[i] = 0;
		t->ray_dir[i] = 0;
		t->side_dist[i] = 0;
		t->step[i] = 0;
		t->map_cord[i] = 0;
	}
}
