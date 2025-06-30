/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irkalini <irkalini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:47:58 by enrmarti          #+#    #+#             */
/*   Updated: 2025/06/30 14:50:54 by irkalini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	raycasting(t_play *player, t_cub *cub, float start_x, int i)
{
	float cos_angle = cos(start_x);
	float sin_angle = sin(start_x);
	float ray_x = player->x;
	float ray_y = player->y;

	while (!touch(ray_x, ray_y, cub))
	{
		ray_x += cos_angle;
		ray_y += sin_angle;
	}
	float dist = fixed_dist(player->x, player->y, ray_x, ray_y, cub);
	float height = (BLOCK / dist) * (WIDTH / 2);
	int start_y = (HEIGHT - height) / 2;
	int end = start_y + height;
	while (start_y < end)
	{
		put_pixel(i, start_y, 255, cub);
		start_y++;
	}
}
