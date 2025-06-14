/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irkalini <irkalini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 18:34:06 by irkalini          #+#    #+#             */
/*   Updated: 2025/06/14 19:31:14 by irkalini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
	int	i;

	i = 0;
	while (file->line[i])
	{
		if (file->line[i] == ' ')
			file->line[i] = 'S';
		i++;
	}
	if (file->line[ft_strlen(file->line) - 1] == '\n')
		file->line[ft_strlen(file->line) - 1] = '\0';
}

int	read_map(t_file *file)
{
	while (is_empty_line(file->line))
		file->line = get_next_line(file->fd);
	while (file->line != NULL)
	{
		if (is_empty_line(file->line))
			return (0);
		if (!is_valid_map_line(file->line))
			return (0);
		replace_spaces(file);
		file->map;
		printf("%s\n", file->line);
		file->line = get_next_line(file->fd);
	}
	return (1);
}
