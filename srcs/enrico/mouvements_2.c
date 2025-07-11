/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouvements_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irkalini <irkalini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 17:15:31 by irkalini          #+#    #+#             */
/*   Updated: 2025/07/11 17:15:55 by irkalini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	check_border(t_cub *cub, t_play *p, double n_x, double n_y)
{
	if ((int)n_y == 0 || (int)n_y == cub->file.i - cub->file.start_map - 1 || \
		(int)p->x == 0 || (int)p->x == ft_strlen(cub->file.map[(int)n_y]) - 1)
		safe_exit(cub);
	if ((int)p->y == 0 || (int)p->y == cub->file.i - cub->file.start_map - 1 || \
		(int)n_x == 0 || (int)n_x == ft_strlen(cub->file.map[(int)p->y]) - 1)
		safe_exit(cub);
}

void	proceed_move(t_cub *cub, t_play *p, double n_x, double n_y)
{
	check_border(cub, p, n_x, n_y);
	if (cub->file.map[(int)n_y][(int)p->x] == '1' && (
		((int)n_y > 0 && cub->file.map[(int)n_y - 1][(int)p->x] == 'P') || \
		((int)n_y + 1 < (cub->file.i - cub->file.start_map) && \
		cub->file.map[(int)n_y + 1][(int)p->x] == 'P') || \
		((int)p->x > 0 && cub->file.map[(int)n_y][(int)p->x - 1] == 'P') || \
		((int)p->x + 1 < ft_strlen(cub->file.map[(int)n_y]) && \
		cub->file.map[(int)n_y][(int)p->x + 1] == 'P')))
		safe_exit(cub);
	else
		p->y = n_y;
	if (cub->file.map[(int)p->y][(int)n_x] == '1' && ((
		((int)p->y > 0 && cub->file.map[(int)p->y - 1][(int)n_x] == 'P') || \
		((int)p->y + 1 < (cub->file.i - cub->file.start_map) && \
		cub->file.map[(int)p->y + 1][(int)n_x] == 'P') || \
		((int)n_x > 0 && cub->file.map[(int)p->y][(int)n_x - 1] == 'P') || \
		((int)n_x + 1 < ft_strlen(cub->file.map[(int)p->y]) && \
		cub->file.map[(int)p->y][(int)n_x + 1] == 'P'))))
		safe_exit(cub);
	else
		p->x = n_x;
}
