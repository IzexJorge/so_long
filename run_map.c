/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 21:43:11 by jescuder          #+#    #+#             */
/*   Updated: 2024/04/19 18:56:55 by jescuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	finish_game(int error, t_mlx *mlx)
{
	mlx_destroy_window(mlx->mlx, mlx->win);
	free(mlx->mlx);
	free_array(mlx->map);
	if (error)
		ft_perror();
	exit(0);
}

int	on_destroy(t_mlx *mlx)
{
	finish_game(0, mlx);
	return (0);
}

void	direction_action(int x, int y, t_mlx *mlx)
{
	t_entity	*player;
	char		element;
	t_entity	*zombie;

	player = &(mlx->player);
	if (player->state_val != 0)
		return ;
	element = mlx->map[player->y + y][player->x + x];
	if (element == '0' || element == 'P')
		walk(player, x, y, mlx);
	else if (element == 'C')
	{
		zombie = get_zombie(player->x + x, player->y + y, mlx);
		if (zombie->state_val == 9)
			return ;
		else if (zombie->state_val == 10)
			walk(player, x, y, mlx);
		else
			attack(player, x, y, mlx);
	}
	else if (element == 'E' && mlx->kills_left == 0)
		finish_game(0, mlx);
}

int	on_keydown(int keycode, t_mlx *mlx)
{
	if (keycode == 2 || keycode == 124)
		direction_action(1, 0, mlx);
	else if (keycode == 0 || keycode == 123)
		direction_action(-1, 0, mlx);
	else if (keycode == 1 || keycode == 125)
		direction_action(0, 1, mlx);
	else if (keycode == 13 || keycode == 126)
		direction_action(0, -1, mlx);
	else if (keycode == 53)
		finish_game(0, mlx);
	return (0);
}

int	run_map(char **map)
{
	t_mlx	mlx;

	mlx.mlx = mlx_init();
	if (!mlx.mlx)
		return (0);
	mlx.win = mlx_new_window(mlx.mlx, 1920, 1080, "so_long");
	if (!mlx.win)
	{
		free(mlx.mlx);
		return (0);
	}
	mlx.map = map;
	mlx.zombies = NULL;
	mlx.walk_count = 0;
	mlx.kills_left = 0;
	init_img_sets(&mlx);
	init_map(&mlx);
	mlx_hook(mlx.win, 2, 0, on_keydown, &mlx);
	mlx_hook(mlx.win, 17, 0, on_destroy, &mlx);
	mlx_loop_hook(mlx.mlx, update_graphics, &mlx);
	mlx_loop(mlx.mlx);
	return (1);
}
