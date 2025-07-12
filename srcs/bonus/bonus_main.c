/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irkalini <irkalini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 10:09:15 by irkalini          #+#    #+#             */
/*   Updated: 2025/07/12 11:42:44 by irkalini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

int	main(int argc, char **argv)
{
	t_cub	*cub;

	if (argc != 2)
		return (printf("Error\nBad arguments\n"), 1);
	if (!is_valid_extension(argv[1], ".cub"))
		return (1);
	cub = malloc(sizeof(t_cub));
	if (!cub)
		return (1);
	ft_memset(cub, 0, sizeof(t_cub));
	if (!init_file_struct(cub))
		return (free_all(cub), printf("Error\nInitialisation problem\n"), 1);
	if (!parsing(cub, argv[1]))
		return (free_all(cub), 1);
	cub->player = malloc(sizeof(t_play));
	if (!cub->player)
		return (safe_exit(cub), 1);
	cub->min = malloc(sizeof(t_min));
	if (!cub->min)
		return (safe_exit(cub), 1);
	if (!init_game(cub))
		return (1);
	free_all(cub);
	return (0);
}
