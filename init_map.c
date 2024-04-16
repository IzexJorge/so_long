/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_map_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 20:14:43 by jescuder          #+#    #+#             */
/*   Updated: 2024/04/16 23:21:40 by jescuder         ###   ########.fr       */
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
	init_img_set(g_anim_walk_left, 1, mlx);
	init_img_set(g_anim_walk_right, 2, mlx);
	init_img_set(g_anim_walk_up, 3, mlx);
	init_img_set(g_anim_walk_down, 4, mlx);
	init_img_set(g_anim_stab_left, 5, mlx);
	init_img_set(g_anim_stab_right, 6, mlx);
	init_img_set(g_anim_stab_up, 7, mlx);
	init_img_set(g_anim_stab_down, 8, mlx);
	init_img_set(g_anim_idle_left, 9, mlx);
	init_img_set(g_anim_idle_right, 10, mlx);
	init_img_set(g_anim_idle_up, 11, mlx);
	init_img_set(g_anim_idle_down, 12, mlx);
	init_img_set(g_anim_zombie_idle, 13, mlx);
	init_img_set(g_anim_death, 14, mlx);
}

void	init_animation(t_animation *anim, int isZombie, size_t delay, t_mlx *mlx)
{
	size_t	index;

	if (isZombie)
		index = 13;
	else
		index = 12;
	anim->img_set = mlx->imgs_sets[index];
	anim->imgs_count = mlx->imgs_sets_sizes[index];
	//anim->current_img = delay % anim->imgs_count;
	anim->current_img = 0;
	anim->delay = delay;
	anim->delay_counter = delay;
	ft_printf("init_animation %i %i\n", anim->current_img, anim->imgs_count);
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
		mlx->kills_left++;
	}
	else
		entity = &(mlx->player);
	map = mlx->map;
	delay = 10000 + 5000 * x * y / (ft_arraylen(map) * ft_strlen(map[0]));
	//TODO Buscar una manera de evitar que el delay sea siempre mayor cuanto más abajo a la derecha.
	init_animation(&(entity->anim), isZombie, delay, mlx);
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
				draw_img(mlx->imgs_sets[0][1], x, y, mlx);
			else
			{
				draw_img(mlx->imgs_sets[0][0], x, y, mlx);
				if (row[x] == 'P')
					create_entity(0, x, y, mlx);
				else if (row[x] == 'C')
					create_entity(1, x, y, mlx);
				else if (row[x] == 'E')
					draw_img(mlx->imgs_sets[0][2], x, y, mlx);
			}
		}
	}
}