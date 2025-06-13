/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irkalini <irkalini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 12:21:12 by irkalini          #+#    #+#             */
/*   Updated: 2025/06/13 13:55:20 by irkalini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_data(t_cub *cub)
{
	cub->file.map = NULL;
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
	cub->file.line = NULL;
}

int	main(int argc, char **argv)
{
	t_cub	cub;

	if (argc != 2)
		return (printf("Bad arguments\n"), 1);
	if (!is_valid_extension(argv[1]))
		return (1);
	init_data(&cub);
	if (!parsing(&cub, argv[1]))
		return (1);
	//next moves
	return (0);
}
