/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irkalini <irkalini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 12:18:21 by irkalini          #+#    #+#             */
/*   Updated: 2025/07/04 14:59:09 by irkalini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	parsing(t_cub *cub, char *filename)
{
	t_file	*file;
	int		i;

	i = 0;
	file = &cub->file;
	if (!read_file(file, filename))
		return (0);
	if (file->player_found > 1)
		return (printf("Error\nToo many players\n"), 0);
	if (!is_closed_map(file))
		return (0);
	file->floor_color = file->floor.r * 256 * 256 + file->floor.g * 256 \
		+ file->floor.b;
	file->ceil_color = file->ceil.r * 256 * 256 + file->ceil.g * 256 \
		+ file->ceil.b;
	return (1);
}

int	get_color(t_file *file)
{
	char	**colors;
	int		i;
	int		num;

	i = 0;
	num = 0;
	colors = ft_split(file->tok[1], ',');
	if (!colors || colors[3] != NULL)
		return (free_split(colors), printf("Error\nBad color\n"), 0);
	while (colors[i])
	{
		if (!is_digit_string(colors[i]))
			return (free_split(colors), printf("Error\nBad color\n"), 0);
		num = ft_atoi(colors[i]);
		if (!num && colors[i][0] != '0')
			return (free_split(colors), printf("Error\nft_atoi problem\n"), 0);
		if (num < 0 || num > 255)
			return (free_split(colors), printf("Error\nBad color\n"), 0);
		if (!set_color(file, i, num))
			return (free_split(colors), 0);
		i++;
	}
	free_split(colors);
	file->data_count++;
	return (1);
}

int	get_texture(t_file *file)
{
	int	fd;

	fd = 0;
	if (ft_strncmp(file->tok[1], "./", 2))
		return (printf("Error\nPath should start with ./\n"), 0);
	fd = open(file->tok[1], O_RDONLY);
	if (fd == -1)
		return (close(fd), printf("Error\nFile problem\n"), 0);
	close(fd);
	if (!is_valid_extension(file->tok[1], ".xpm"))
		return (0);
	if (!ft_strncmp(file->tok[0], "NO", 2) && !file->no_t)
		file->no_t = ft_strdup(file->tok[1]);
	else if (!ft_strncmp(file->tok[0], "SO", 2) && !file->so_t)
		file->so_t = ft_strdup(file->tok[1]);
	else if (!ft_strncmp(file->tok[0], "WE", 2) && !file->we_t)
		file->we_t = ft_strdup(file->tok[1]);
	else if (!ft_strncmp(file->tok[0], "EA", 2) && !file->ea_t)
		file->ea_t = ft_strdup(file->tok[1]);
	else
		return (printf("Error\nBad type identifier\n"), 0);
	file->data_count++;
	return (1);
}

int	get_data(t_file *file)
{
	if (file->tok[1] == NULL)
		return (0);
	if (ft_strlen(file->tok[0]) == 2)
	{
		if (!get_texture(file))
			return (0);
	}
	else if (ft_strlen(file->tok[0]) == 1)
	{
		if (!get_color(file))
			return (0);
	}
	else
		return (0);
	return (1);
}

int	read_file(t_file *file, char *filename)
{
	file->fd = open(filename, O_RDONLY);
	file->line = get_next_line(file->fd);
	while (file->line != NULL && file->data_count < 6)
	{
		if (!is_empty_line(file->line))
		{
			if (!get_tokens(file->line, file))
				return (free_tokens(file, 1), drain_gnl(file), 0);
			if (!get_data(file))
				return (free_tokens(file, 1), drain_gnl(file), 0);
			free_tokens(file, 0);
		}
		file->i++;
		free(file->line);
		file->line = get_next_line(file->fd);
	}
	if (file->tok)
		free(file->tok);
	if (!file->line)
		return (printf("Error\nNot enough information\n"), 0);
	if (!read_map_1(file))
		return (0);
	read_map_2(file, filename);
	close(file->fd);
	return (1);
}
