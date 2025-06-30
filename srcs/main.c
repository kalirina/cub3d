/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irkalini <irkalini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 12:21:12 by irkalini          #+#    #+#             */
/*   Updated: 2025/06/30 18:47:01 by irkalini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int argc, char **argv)
{
	t_cub	cub;

	if (argc != 2)
		return (printf("Error\nBad arguments\n"), 1);
	if (!is_valid_extension(argv[1], ".cub"))
		return (1);
	if (!init_file_struct(&cub))
		return (printf("Error\nInitialisation problem\n"), 1);
	if (!parsing(&cub, argv[1]))
		return (free_file_struct(&cub), 1);
	if (!init_game(&cub))
		return (1);
	return (0);
}
