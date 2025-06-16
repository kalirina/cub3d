/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irkalini <irkalini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 18:34:06 by irkalini          #+#    #+#             */
/*   Updated: 2025/06/16 17:52:25 by irkalini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
				|| file->map[i][j] == 'W')
			{
				
			}
		}
		i++;
	}
}

int	is_valid_map_line(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '\n')
	{
		if (s[i] != ' ' && s[i] != '1' && s[i] != '0' && s[i] != 'N' \
			&& s[i] != 'S' && s[i] != 'E' && s[i] != 'W')
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
			file->line[i] = 'S';
		if (file->line[i] == 'N' || file->line[i] == 'S'\
			|| file->line[i] == 'E' || file->line[i] == 'W')
			file->player_found++;
		i++;
	}
	if (file->line[ft_strlen(file->line) - 1] == '\n')
		file->line[ft_strlen(file->line) - 1] = '\0';
	while (ft_strlen(file->line) < file->max_length)
	{
		new = ft_strjoin(file->line, "S");
		free(file->line);
		file->line = new;
	}
}

int	read_map_1(t_file *file)
{
	while (is_empty_line(file->line))
	{
		file->line = get_next_line(file->fd);
		file->i++;
	}
	file->start_map = file->i;
	file->max_length = ft_strlen(file->line);
	while (file->line != NULL)
	{
		if (is_empty_line(file->line))
			return (0);
		if (!is_valid_map_line(file->line))
			return (0);
		if (ft_strlen(file->line) > file->max_length)
			file->max_length = ft_strlen(file->line);
		file->i++;
		file->line = get_next_line(file->fd);
	}
	close(file->fd);
	return (1);
}

int	read_map_2(t_file *file, char *filename)
{
	int	i;

	i = 0;
	file->map = malloc(sizeof(char *) * file->i - file->start_map + 1);
	if (!file->map)
		return (0);
	file->fd = open(filename, O_RDONLY);
	file->line = get_next_line(file->fd);
	while (i < file->start_map)
	{
		file->line = get_next_line(file->fd);
		i++;
	}
	i = 0;
	while (file->line != NULL)
	{
		replace_spaces(file);
		file->map[i] = malloc(sizeof(char) * file->max_length + 1);
		if (!file->map[i])
			return (0);
		file->map[i++] = ft_strdup(file->line);
		file->line = get_next_line(file->fd);
	}
	file->map[i] = NULL;
	return (1);
}
