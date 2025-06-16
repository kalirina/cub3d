/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irkalini <irkalini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 12:21:12 by irkalini          #+#    #+#             */
/*   Updated: 2025/06/16 15:01:51 by irkalini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	init_data(t_cub *cub)
{
	cub->file.map = NULL;
	cub->file.tok = NULL;
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
	cub->file.max_length = 0;
	cub->file.start_map = 0;
	cub->file.line = NULL;
	cub->file.data_count = 0;
	return (1);
}

int	main(int argc, char **argv)
{
	t_cub	cub;

	if (argc != 2)
		return (printf("Bad arguments\n"), 1);
	if (!is_valid_extension(argv[1], ".cub"))
		return (1);
	if (!init_data(&cub))
		return (1);
	if (!parsing(&cub, argv[1]))
		return (1);
	//next moves
	return (0);
}
