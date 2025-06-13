/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irkalini <irkalini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 12:18:21 by irkalini          #+#    #+#             */
/*   Updated: 2025/06/13 17:27:26 by irkalini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_valid_extension(char *filename)
{
	char	*extension;

	extension = ft_strrchr(filename, '.');
	if (!extension || ft_strncmp(extension, ".cub", 4) != 0 )
		return (printf("Bad extension\n"), 0);
	if (extension[4] != 0)
		return (printf("Bad extension\n"), 0);
	return (1);
}

int	parsing(t_cub *cub, char *file)
{
	if (!read_file(cub, file))
		return (0);
	return (1);
}

int	is_empty(char *line)
{
	int	i;

	i = 0;
	while (line[i] != NULL)
	{
		if (line[i] != "\f" && line[i] != "\n" && line[i] != "\r" \
			&& line[i] != "\t" && line[i] != "\v" && line[i] != 32)
			return (0);
	}
	return (1);
}

int get_data(t_cub *cub, char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != "\f" && line[i] != "\n" && line[i] != "\r" \
			&& line[i] != "\t" && line[i] != "\v" && line[i] != 32)
			i++;
		if (ft_strncmp(line + i, "NO", 2) || ft_strncmp(line + i, "SO", 2)\
			|| ft_strncmp(line + i, "WE", 2) || ft_strncmp(line + i, "EA", 2))
		{
			while (line[i] && (line[i] == 32 || line[i] == "\t"))
				i++;
			cub->file.
		}
	}
}

int	read_file(t_cub *cub, char *file)
{
	cub->file.fd = open(file, O_RDONLY);
	cub->file.line = get_next_line(cub->file.fd);
	while (cub->file.line != NULL)
	{
		if (!is_empty(cub->file.line))
		{
			if (!get_data(cub,cub->file.line))
		}
	}
	close(cub->file.fd);
	//if map and data are fine
	return (1);
}
