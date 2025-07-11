/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrmarti <enrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:52:10 by irkalini          #+#    #+#             */
/*   Updated: 2025/07/11 12:53:56 by enrmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

void	free_tokens(t_file *file, int flag)
{
	int	i;

	i = 0;
	while (file->tok[i])
		free(file->tok[i++]);
	if (flag)
	{
		if (file->tok)
			free(file->tok);
	}
}

void	free_file_struct(t_cub *cub)
{
	t_file	*file;

	file = &cub->file;
	if (file->no_t)
		free(file->no_t);
	if (file->so_t)
		free(file->so_t);
	if (file->ea_t)
		free(file->ea_t);
	if (file->we_t)
		free(file->we_t);
	if (file->line)
		free(file->line);
	if (file->map)
		free_split(file->map);
}

void	free_all(t_cub *cub)
{
	free_file_struct(cub);
	if (cub->player)
		free(cub->player);
	free(cub);
}

int	safe_exit(void *param)
{
	t_cub	*cub;

	cub = (t_cub *)param;
	if (cub->img)
		mlx_destroy_image(cub->mlx, cub->img);
	if (cub->win)
		mlx_destroy_window(cub->mlx, cub->win);
	mlx_destroy_display(cub->mlx);
	free(cub->mlx);
	free_all(cub);
	exit(0);
}
