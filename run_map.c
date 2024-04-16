/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 21:43:21 by jescuder          #+#    #+#             */
/*   Updated: 2024/04/16 23:52:26 by jescuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// Sólo imprime los caracteres, para probar.
int		print_map(char **map)
{
	size_t	i;
	char	*row;
	size_t	j;

	i = -1;
	while (map[++i])
	{
		row = map[i];
		j = -1;
		while (row[++j])
			ft_putchar_fd(row[j], 1);
		ft_putchar_fd('\n', 1);
	}
	return (1);
}

int		enough_space(void *mlx, int map_x, int map_y, int tile_s)
{
	int	screen_x;
	int	screen_y;

	(void)mlx;
	screen_x = 1;
	screen_y = 2;
	//mlx_get_screen_size(mlx, &screen_x, &screen_y);
	if ((screen_x > map_x * tile_s) && (screen_y > map_y * tile_s))
		return (1);
	else
		return (0);
}

//Tal vez haya que destruir las imagenes con destroy_image.
//Añadir argumento para errores. Quizá también otro opcional para mensaje de error custom.
void	finish_game(t_mlx *mlx)
{
	ft_printf("finish game\n");
	mlx_destroy_window(mlx->mlx, mlx->win);
	free(mlx->mlx);
	free_array(mlx->map);
	(void)mlx;
	exit(0);
}

//Comprobar por qué la ausencia estos free no hacen saltar el sanitizer. Especialmente el de map.
int		on_destroy(t_mlx *mlx)
{
	ft_printf("on_destroy\n");
	free(mlx->win);
	free(mlx->mlx);
	free_array(mlx->map);
	(void)mlx;
	exit(0);
}

t_entity	*get_zombie(size_t x, size_t y, t_mlx *mlx)
{
	t_list		*zombies;
	t_entity	*zombie;

	zombies = mlx->zombies;
	while (zombies)
	{
		zombie = (t_entity *)zombies->content;
		if (zombie->x == x && zombie->y == y)
			return zombie;
		zombies = zombies->next;
	}
	return NULL;
}

void	direction_action(int x, int y, t_mlx *mlx)
{
	t_entity	*player;
	char		element;
	t_entity	*zombie;

	player = &(mlx->player);
	if (player->state_value != 0)
		return ;
	element = mlx->map[player->y + y][player->x + x];
	if (element == '0' || element == 'P')
		walk(player, x, y, mlx);
	else if (element == 'C')
	{
		zombie = get_zombie(player->x + x, player->y + y, mlx);
		if (zombie->state_value == 9)
			return ;
		else if(zombie->state_value == 10)
			walk(player, x, y, mlx);
		else
			attack(player, x, y, mlx);
	}
	else if (element == 'E' && mlx->kills_left == 0)
		finish_game(mlx);
}

int		on_keydown(int keycode, t_mlx *mlx)
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
		finish_game(mlx);
	return (0);
}

//TODO Setear fps para que haya consistencia de las animaciones en el tiempo y entre equipos.

int		run_map(char **map)
{
	t_mlx	mlx;

	print_map(map);//Para probar

	mlx.mlx = mlx_init();
	if (!mlx.mlx)
		return (0);
	mlx.win = mlx_new_window(mlx.mlx, 1920, 1080, "Hello world!");//No hardcoded
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