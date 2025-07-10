/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_parsing_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irkalini <irkalini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 10:40:28 by irkalini          #+#    #+#             */
/*   Updated: 2025/07/10 11:40:29 by irkalini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	is_closed_map(t_file *file)
{
	int	i;
	int	j;

	i = 0;
	while (file->map[i])
	{
		j = 0;
		while (file->map[i][j])
		{
			if (file->map[i][j] == '0' || file->map[i][j] == 'N'\
				|| file->map[i][j] == 'S' || file->map[i][j] == 'E'\
				|| file->map[i][j] == 'W' || file->map[i][j] == 'D') //BONUS
			{
				if (i == 0 || i == file->i || j == 0 || j == file->max_len - 1)
					return (printf("Error\nMap is not closed\n"), 0);
				if (file->map[i][j - 1] == 'P' || file->map[i][j + 1] == 'P'\
					|| file->map[i - 1][j] == 'P'\
					|| file->map[i + 1][j] == 'P')
					return (printf("Error\nMap is not closed\n"), 0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	is_valid_map_line(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '\n')
	{
		if (s[i] != ' ' && s[i] != '1' && s[i] != '0' && s[i] != 'N' \
			&& s[i] != 'S' && s[i] != 'E' && s[i] != 'W' && s[i] != 'D') //BONUS
			return (0);
		i++;
	}
	return (1);
}

void	replace_spaces(t_file *file)
{
	char	*new;
	int		i;

	i = 0;
	new = NULL;
	while (file->line[i])
	{
		if (file->line[i] == ' ')
			file->line[i] = 'P';
		if (file->line[i] == 'N' || file->line[i] == 'S'\
			|| file->line[i] == 'E' || file->line[i] == 'W')
			file->player_found++;
		i++;
	}
	if (file->line[ft_strlen(file->line) - 1] == '\n')
		file->line[ft_strlen(file->line) - 1] = '\0';
	while (ft_strlen(file->line) < file->max_len)
	{
		new = ft_strjoin(file->line, "P");
		free(file->line);
		file->line = new;
	}
}

int	read_map_1(t_file *file)
{
	while (file->line && is_empty_line(file->line))
	{
		free(file->line);
		file->line = get_next_line(file->fd);
		file->i++;
	}
	if (!file->line)
		return (printf("Error\nNo map data\n"), 0);
	file->start_map = file->i;
	file->max_len = ft_strlen(file->line);
	while (file->line != NULL)
	{
		if (is_empty_line(file->line))
			return (printf("Error\nEmpty line in map\n"), drain_gnl(file), 0);
		if (!is_valid_map_line(file->line))
			return (printf("Error\nInvalid map char\n"), drain_gnl(file), 0);
		if (ft_strlen(file->line) > file->max_len)
			file->max_len = ft_strlen(file->line);
		file->i++;
		free(file->line);
		file->line = get_next_line(file->fd);
	}
	close(file->fd);
	return (1);
}

int	read_map_2(t_file *file, char *filename)
{
	int	i;

	i = -1;
	file->map = malloc(sizeof(char *) * (file->i - file->start_map + 1));
	if (!file->map)
		return (printf("Error\nMalloc\n"), 0);
	file->fd = open(filename, O_RDONLY);
	file->line = get_next_line(file->fd);
	while (++i < file->start_map)
	{
		free(file->line);
		file->line = get_next_line(file->fd);
	}
	i = 0;
	while (file->line != NULL)
	{
		replace_spaces(file);
		file->map[i++] = ft_strdup(file->line);
		free(file->line);
		file->line = get_next_line(file->fd);
	}
	file->map[i] = NULL;
	free(file->line);
	close(file->fd);
	return (1);
}
