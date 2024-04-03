/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_map_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 20:14:43 by jescuder          #+#    #+#             */
/*   Updated: 2024/04/04 00:06:00 by jescuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_img_set(const char **img_paths, size_t index, t_mlx *mlx)
{
	size_t	set_size;
	t_img	*img_set;
	size_t	i;

	set_size = ft_arraylen((char**)img_paths);
	img_set = ft_calloc(set_size, sizeof(t_img));
	if (!img_set)
		finish_game(mlx);
	mlx->imgs_sets[index] = img_set;
	mlx->imgs_sets_sizes[index] = set_size;
	i = -1;
	while (img_paths[++i])
	{
		img_set[i].img = mlx_xpm_file_to_image(mlx->mlx, (char *)img_paths[i],
							&(img_set[i].width), &(img_set[i].height));
		if (!img_set[i].img)
		{
			ft_printf("The file \"%s\" could not be read.\n", img_paths[i]);
			finish_game(mlx);
		}
	}
}

void	init_img_sets(t_mlx *mlx)
{
	init_img_set(g_single_img, 0, mlx);
	init_img_set(g_anim_move_left, 1, mlx);
	init_img_set(g_anim_move_right, 2, mlx);
	init_img_set(g_anim_move_up, 3, mlx);
	init_img_set(g_anim_move_down, 4, mlx);
	init_img_set(g_anim_idle_down, 5, mlx);
	init_img_set(g_anim_zombie_idle_down, 6, mlx);
	init_img_set(g_anim_attack, 7, mlx);
	init_img_set(g_anim_death, 8, mlx);
}

void	init_animation(t_animation *animation, int isZombie, size_t delay, t_mlx *mlx)
{
	size_t	index;

	if (isZombie)
		index = 6;
	else
		index = 5;
	animation->img_set = mlx->imgs_sets[index];
	animation->imgs_count = mlx->imgs_sets_sizes[index];
	//animation->current_img = delay % animation->imgs_count;
	animation->current_img = 0;
	animation->delay = delay;
	animation->delay_counter = delay;
	ft_printf("init_animation %i %i\n", animation->current_img, animation->imgs_count);
	//TODO Resto de fields en caso de haberlos.
}

void	create_entity(int isZombie, size_t x, size_t y, t_mlx *mlx)
{
	t_entity	*entity;
	t_list		*new_node;
	char		**map;
	size_t		delay;

	if (isZombie)
	{
		entity = malloc(sizeof(t_entity));
		if (!entity)
			finish_game(mlx);
		new_node = ft_lstnew(entity);
		if (!new_node)
			finish_game(mlx);
		ft_lstadd_front(&(mlx->zombies), new_node);
	}
	else
		entity = &(mlx->player);
	map = mlx->map;
	delay = 10000 + 5000 * x * y / (ft_arraylen(map) * ft_strlen(map[0]));
	//TODO Buscar una manera de evitar que el delay sea siempre mayor cuanto más abajo a la derecha.
	init_animation(&(entity->animation), isZombie, delay, mlx);
	entity->state_value = 0;
	entity->x = x;
	entity->y = y;
}

void	init_map(t_mlx *mlx)
{
	size_t	y;
	size_t	x;
	char	*row;

	y = -1;
	while (mlx->map[++y])
	{
		row = mlx->map[y];
		x = -1;
		while (row[++x])
		{
			if (row[x] == '1')
				draw_img_tile(mlx->imgs_sets[0][1], x, y, mlx);
			else
			{
				draw_img_tile(mlx->imgs_sets[0][0], x, y, mlx);
				if (row[x] == 'P')
					create_entity(0, x, y, mlx);
				else if (row[x] == 'C')
					create_entity(1, x, y, mlx);
				else if (row[x] == 'E')
					draw_img_tile(mlx->imgs_sets[0][2], x, y, mlx);
			}
		}
	}
}