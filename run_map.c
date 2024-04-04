/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 21:43:21 by jescuder          #+#    #+#             */
/*   Updated: 2024/04/05 00:14:52 by jescuder         ###   ########.fr       */
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

void	kill_zombie(t_mlx *mlx)
{
	(void)mlx;
}

void	walk(t_entity *entity, int x, int y, t_mlx *mlx)
{
	size_t		direction_value;
	t_animation	*animation;

	if (x == -1)
		direction_value = 1;
	else if (x == 1)
		direction_value = 2;
	else if (y == -1)
		direction_value = 3;
	else
		direction_value = 4;
	entity->state_value = direction_value;
	animation = &(entity->animation);
	animation->img_set = mlx->imgs_sets[direction_value];
	animation->imgs_count = mlx->imgs_sets_sizes[direction_value];
	animation->current_img = 0;
	animation->delay_counter = 0;
	animation->delay = 2000;
}

void	attack(t_entity *entity, int x, int y, t_mlx *mlx)
{
	size_t		direction_value;
	t_animation	*animation;

	direction_value = 4;
	if (x == -1)
		direction_value += 1;
	else if (x == 1)
		direction_value += 2;
	else if (y == -1)
		direction_value += 3;
	else
		direction_value += 4;
	entity->state_value = direction_value;
	animation = &(entity->animation);
	animation->img_set = mlx->imgs_sets[direction_value];
	animation->imgs_count = mlx->imgs_sets_sizes[direction_value];
	animation->current_img = 0;
	animation->delay_counter = 0;
	animation->delay = 2000;
}

void	check_walk_player(int x, int y, t_mlx *mlx)
{
	t_entity	*player;
	char		element;

	player = &(mlx->player);
	if (player->state_value != 0)
		return ;
	element = mlx->map[player->y + y][player->x + x];
	if (element == '1')
		return ;
	else if (element == 'C')//TODO Cambiar a comprobar si hay un zombie vivo en esa posición.
		attack(player, x, y, mlx);
	else if (element == 'E')//&& no quedan coleccionables
		finish_game(mlx);
	else
		walk(player, x, y, mlx);
}

int		on_keydown(int keycode, t_mlx *mlx)
{
	if (keycode == 2 || keycode == 124)//Derecha
		check_walk_player(1, 0, mlx);
	else if (keycode == 0 || keycode == 123)//Izquierda
		check_walk_player(-1, 0, mlx);
	else if (keycode == 1 || keycode == 125)//Abajo
		check_walk_player(0, 1, mlx);
	else if (keycode == 13 || keycode == 126)//Arriba
		check_walk_player(0, -1, mlx);
	else if (keycode == 53)//Escape
		finish_game(mlx);
	return (0);
}

void	draw_img(t_img img, size_t x, size_t y, t_mlx *mlx)
{
	mlx_put_image_to_window(mlx->mlx, mlx->win, img.img, x, y);
}

void	draw_img_tile(t_img img, size_t x, size_t y, t_mlx *mlx)
{
	draw_img(img, x * g_tile_size, y * g_tile_size, mlx);
}

void	draw_background(size_t x, size_t y, t_mlx *mlx)
{
	t_list		*zombies;
	t_entity	*zombie;

	draw_img_tile(mlx->imgs_sets[0][0], x, y, mlx);
	zombies = mlx->zombies;
	while (zombies)
	{
		zombie = zombies->content;
		if (zombie->x == x && zombie->y == y)
		{
			if (zombie->state_value == 10)
				draw_img_tile(mlx->imgs_sets[14][3], x, y, mlx);
			return ;
		}
		zombies = zombies->next;
	}
}

void	update_iddle(t_entity *entity, t_animation *animation, t_mlx *mlx)
{
	draw_background(entity->x, entity->y, mlx);
	draw_img_tile(animation->img_set[animation->current_img], entity->x, entity->y, mlx);
	animation->current_img = (animation->current_img + 1) % animation->imgs_count;
	animation->delay_counter = 0;
}

void	get_idle(t_entity *entity, t_mlx *mlx)
{
	int			state_value;
	size_t		index;
	t_animation	*animation;

	state_value = entity->state_value;
	if (state_value == 1 || state_value == 5)
		index = 9;
	else if(state_value == 2 || state_value == 6)
		index = 10;
	else if(state_value == 3 || state_value == 7)
		index = 11;
	else
		index = 12;
	entity->state_value = 0;
	animation = &(entity->animation);
	animation->img_set = mlx->imgs_sets[index];
	animation->imgs_count = mlx->imgs_sets_sizes[index];
	animation->current_img = 0;
	animation->delay_counter = 7000;
	animation->delay = 9000;
}

void	stop_walking(t_entity *entity, int x, int y, t_mlx *mlx)
{
	//t_animation	*animation;
	//size_t		index;

	// index = entity->state_value + 8;
	// entity->state_value = 0;
	// entity->x = entity->x + x;
	// entity->y = entity->y + y;
	// animation = &(entity->animation);
	// animation->img_set = mlx->imgs_sets[index];
	// animation->imgs_count = mlx->imgs_sets_sizes[index];
	// animation->current_img = 0;
	// animation->delay_counter = 7000;
	// animation->delay = 9000;

	get_idle(entity, mlx);
	entity->x = entity->x + x;
	entity->y = entity->y + y;
}

void	draw_walking(t_entity *entity, float x, float y, t_mlx *mlx)
{
	float		pixel_x;
	float		pixel_y;
	t_animation	*animation;

	animation = &(entity->animation);
	pixel_x = g_tile_size * (entity->x + x * (animation->current_img + 1) / 4);
	pixel_y = g_tile_size * (entity->y + y * (animation->current_img + 1) / 4);
	draw_img(animation->img_set[animation->current_img], pixel_x, pixel_y, mlx);
}

void	update_walk(t_entity *entity, t_animation *animation, int state_value, t_mlx *mlx)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	draw_background(entity->x, entity->y, mlx);
	if (state_value == 1)
		x--;
	else if(state_value == 2)
		x++;
	else if(state_value == 3)
		y--;
	else
		y++;
	draw_background(entity->x + x, entity->y + y, mlx);
	draw_walking(entity, x, y, mlx);
	if (animation->current_img == animation->imgs_count - 1)
		stop_walking(entity, x, y, mlx);
	else
	{
		animation->current_img++;
		animation->delay_counter = 0;
	}
}

void	update_attack(t_entity *entity, t_animation *animation, int state_value, t_mlx *mlx)
{
	size_t	x;
	size_t	y;

	draw_background(entity->x, entity->y, mlx);
	draw_img_tile(animation->img_set[animation->current_img], entity->x, entity->y, mlx);
	if (animation->current_img == animation->imgs_count - 1)
	{
		x = 0;
		y = 0;
		if (state_value == 5)
			x--;
		else if(state_value == 6)
			x++;
		else if(state_value == 7)
			y--;
		else
			y++;
		//zombie_die(entity, entity->x + x, entity->y + y, mlx);
	}
	else
	{
		animation->current_img++;
		animation->delay_counter = 0;
	}
}

void	update_player(t_entity *player, t_animation *animation, t_mlx *mlx)
{
	int		state_value;

	state_value = player->state_value;
	if (state_value == 0)
		update_iddle(player, animation, mlx);
	else if (state_value >= 1 && state_value <= 4)
		update_walk(player, animation, state_value, mlx);
	else
		update_attack(player, animation, state_value, mlx);
}

void	update_zombie(t_entity *zombie, t_animation *animation, t_mlx *mlx)
{
	update_iddle(zombie, animation, mlx);
}

void	update_entity(t_entity *entity, t_mlx *mlx)
{
	t_animation	*animation;

	if (entity->state_value == 10)
		return ;
	animation = &(entity->animation);
	if (animation->delay_counter >= animation->delay)
	{
		if (entity == &(mlx->player))
			update_player(entity, animation, mlx);
		else
			update_zombie(entity, animation, mlx);
	}
	animation->delay_counter++;
}

int		update_graphics(t_mlx *mlx)
{
	t_list	*zombies;

	update_entity(&(mlx->player), mlx);
	zombies = mlx->zombies;
	while (zombies)
	{
		update_entity((t_entity *)zombies->content, mlx);
		zombies = zombies->next;
	}
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
	init_img_sets(&mlx);
	init_map(&mlx);

	mlx_hook(mlx.win, 2, 0, on_keydown, &mlx);
	mlx_hook(mlx.win, 17, 0, on_destroy, &mlx);

	mlx_loop_hook(mlx.mlx, update_graphics, &mlx);
	mlx_loop(mlx.mlx);

	return (1);
}