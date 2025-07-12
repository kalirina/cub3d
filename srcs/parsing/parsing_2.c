/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irkalini <irkalini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 18:30:30 by irkalini          #+#    #+#             */
/*   Updated: 2025/07/12 13:59:28 by irkalini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	drain_gnl(t_file *file)
{
	while (file->line != NULL)
	{
		free(file->line);
		file->line = get_next_line(file->fd);
	}
}

int	is_valid_extension(char *filename, char *ext)
{
	char	*extension;
	int		len;

	len = ft_strlen(ext);
	extension = ft_strrchr(filename, '.');
	if (!extension || ft_strncmp(extension, ext, len) != 0)
		return (printf("Error\nBad extension\n"), 0);
	if (extension[len] != 0)
		return (printf("Error\nBad extension\n"), 0);
	return (1);
}

int	is_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '\f' && line[i] != '\n' && line[i] != '\r' \
			&& line[i] != '\t' && line[i] != '\v' && line[i] != 32)
			return (0);
		i++;
	}
	return (1);
}

int	get_tokens(char *line, t_file *file)
{
	int	i;
	int	j;
	int	start;

	i = 0;
	j = 0;
	while (line[i])
	{
		while (line[i] == '\t' || line[i] == ' ')
			i++;
		if (!line[i] || line[i] == '\n')
			break ;
		start = i;
		while (line[i] && line[i] != '\t' && line[i] != ' ' && line[i] != '\n')
			i++;
		if (j >= 2)
			return (printf("Error\nCannot get data\n"), 0);
		file->tok[j] = malloc(sizeof(char) * (i - start) + 1);
		if (!file->tok[j])
			return (printf("Error\nCannot get data\n"), 0);
		ft_strlcpy(file->tok[j], line + start, i - start + 1);
		j++;
	}
	file->tok[j] = NULL;
	return (1);
}

int	set_color(t_file *file, int i, int num)
{
	if (!ft_strncmp(file->tok[0], "F", 1))
	{
		if (i == 0)
			file->floor.r = num;
		else if (i == 1)
			file->floor.g = num;
		else
			file->floor.b = num;
	}
	else if (!ft_strncmp(file->tok[0], "C", 1))
	{
		if (i == 0)
			file->ceil.r = num;
		else if (i == 1)
			file->ceil.g = num;
		else
			file->ceil.b = num;
	}
	else
		return (printf("Error\nBad type identifier\n"), 0);
	return (1);
}
