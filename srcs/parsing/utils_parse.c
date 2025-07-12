/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irkalini <irkalini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:38:28 by irkalini          #+#    #+#             */
/*   Updated: 2025/07/12 10:13:26 by irkalini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	init_file_struct(t_cub *cub)
{
	cub->file.map = NULL;
	cub->file.tok = malloc(sizeof(char *) * 3);
	if (!cub->file.tok)
		return (0);
	cub->file.no_t = NULL;
	cub->file.so_t = NULL;
	cub->file.we_t = NULL;
	cub->file.ea_t = NULL;
	cub->file.floor.r = 0;
	cub->file.floor.g = 0;
	cub->file.floor.b = 0;
	cub->file.ceil.r = 0;
	cub->file.ceil.g = 0;
	cub->file.ceil.b = 0;
	cub->file.fd = 0;
	cub->file.i = 0;
	cub->file.player_found = 0;
	cub->file.max_len = 0;
	cub->file.start_map = 0;
	cub->file.line = NULL;
	cub->file.data_count = 0;
	cub->file.player_pos[0] = 0;
	cub->file.player_pos[0] = 0;
	return (1);
}

int	is_digit_string(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
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
			if (cub->file.map[i][j] == 'N' || cub->file.map[i][j] == 'S'\
			|| cub->file.map[i][j] == 'E' || cub->file.map[i][j] == 'W')
			{
				cub->file.player_pos[0] = j;
				cub->file.player_pos[1] = i;
				cub->file.player_dir = cub->file.map[i][j];
			}
			j++;
		}
		i++;
	}
}
