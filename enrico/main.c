/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrmarti <enrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 10:00:32 by enrmarti          #+#    #+#             */
/*   Updated: 2025/06/25 16:23:29 by enrmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	init_player(t_player *player, int x, int y, int angle)
{
	player->x = (float) x;
	player->y = (float) y;
	player->angle = (float) angle;
	player->key_down = false;
	player->key_up = false;
	player->key_right = false;
	player->key_left = false;
	player->left_rotate = false;
	player->right_rotate = false;
}

int	init_game(t_cub *cub)
{
    init_player(&cub->player, WIDTH / 2, HEIGHT / 2, 0);
	cub->mlx = mlx_init();
	if (!cub->mlx)
		return (-1);
	cub->win = mlx_new_window(cub->mlx, WIDTH, HEIGHT, "cub3d");
	if (!cub->win)
		return (free(cub->mlx), -1);
	cub->img = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	if (!cub->img)
		return (free(cub->mlx), free(cub->win), -1);
	cub->data = mlx_get_data_addr(cub->img, &cub->bpp, &cub->size_line, &cub->endian);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img, 0, 0);
	cub->map = malloc(sizeof(char *) * 11);
    cub->map[0] = "111111111111111";
    cub->map[1] = "100000000000001";
   	cub->map[2] = "100000000000001";
    cub->map[3] = "100000100000001";
    cub->map[4] = "100000000000001";
    cub->map[5] = "100000010000001";
    cub->map[6] = "100001000000001";
    cub->map[7] = "100000000000001";
    cub->map[8] = "100000000000001";
    cub->map[9] = "111111111111111";
    cub->map[10] = NULL;
	return (0);
}

int		game_loop(t_cub	*cub)
{
	t_player	*player = &cub->player;
	
	handle_movement(player);
	clear_image(cub);
	// draw_square(player->x, player->y, 10, 0xFF0000, cub);
	
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img, 0, 0);
	return (0);
}

int main()
{
    t_cub	cub;
	
	init_game(&cub);

	mlx_hook(cub.win, 2, 1L<<0, key_pressed, &cub.player);
	mlx_hook(cub.win, 3, 1L<<1, key_released, &cub.player);
	mlx_hook(cub.win, 17, 0, safe_exit, &cub);

	mlx_loop_hook(cub.mlx, game_loop, &cub);
	mlx_loop(cub.mlx);
    return (0);
}