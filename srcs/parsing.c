/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irkalini <irkalini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 12:18:21 by irkalini          #+#    #+#             */
/*   Updated: 2025/06/14 18:26:50 by irkalini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_valid_extension(char *filename, char *ext)
{
	char	*extension;
	int		len;

	len = ft_strlen(ext);
	extension = ft_strrchr(filename, '.');
	if (!extension || ft_strncmp(extension, ext, len) != 0 )
		return (printf("Bad extension\n"), 0);
	if (extension[len] != 0)
		return (printf("Bad extension\n"), 0);
	return (1);
}

int	parsing(t_cub *cub, char *filename)
{
	t_file	*file;

	file = &cub->file;
	if (!read_file(file, filename))
		return (0);
	printf("NO:%s\n", file->no_t);
	printf("SO:%s\n", file->so_t);
	printf("WE:%s\n", file->we_t);
	printf("EA:%s\n", file->ea_t);
	printf("F:%d,%d,%d\n", file->floor.r,file->floor.g,file->floor.b);
	printf("C:%d,%d,%d\n", file->ceil.r,file->ceil.g,file->ceil.b);
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
		return (0);
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
	if (!colors)
		return (0); //free
	if (colors[3] != NULL)
		return (0); //free
	while (colors[i])
	{
		num = ft_atoi(colors[i]);
		if (!num && colors[i][0] != '0')
			return (0);
		if (num < 0 || num > 255)
			return (0);
		if (!set_color(file, i, num))
			return (0);
		i++;
	}
	file->data_count++;
	return (1);
}

int	get_texture(t_file *file)
{
	int	fd;

	fd = 0;
	if (ft_strncmp(file->tok[1], "./", 2))
		return (0);
	fd = open(file->tok[1], O_RDONLY);
	if (fd == -1)
		return (close(fd), 0);
	close(fd);
	if (!is_valid_extension(file->tok[1], ".xpm"))
		return (0);
	if (!ft_strncmp(file->tok[0], "NO", 2))
		file->no_t = ft_strdup(file->tok[1]);
	else if (!ft_strncmp(file->tok[0], "SO", 2))
		file->so_t = ft_strdup(file->tok[1]);
	else if (!ft_strncmp(file->tok[0], "WE", 2))
		file->we_t = ft_strdup(file->tok[1]);
	else if (!ft_strncmp(file->tok[0], "EA", 2))
		file->ea_t = ft_strdup(file->tok[1]);
	else
		return (0);
	file->data_count++;
	return (1);
}

int	get_data(t_file *file)
{
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
			return (0);
		file->tok[j] = malloc(sizeof(char) * (i - start) + 1);
		if (!file->tok[j])
			return (0); //free
		ft_strlcpy(file->tok[j], line + start, i - start + 1);
		j++;
	}
	file->tok[j] = NULL;
	return (1);
}

void	free_tokens(t_file *file)
{
	int	i;

	i = 0;
	while (file->tok[i])
		free(file->tok[i++]);
}

// int	read_map(t_file *file)
// {

// }

int	read_file(t_file *file, char *filename)
{
	file->fd = open(filename, O_RDONLY);
	file->line = get_next_line(file->fd);
	while (file->line != NULL && file->data_count < 6)
	{
		if (!is_empty_line(file->line))
		{
			if (!get_tokens(file->line, file))
				return (0);
			if (!get_data(file))
				return (0);
			free_tokens(file);
		}
		file->line = get_next_line(file->fd);
	}
	if (!file->line)
		return (0);
	// if (read_map(file))
	// 	return (0);
	close(file->fd);
	return (1);
}
