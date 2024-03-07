/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_map_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 20:14:43 by jescuder          #+#    #+#             */
/*   Updated: 2024/03/08 00:12:27 by jescuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_img_set(t_mlx *mlx, const char **img_paths, size_t index)
{
	t_img	*img_set;
	size_t	i;

	img_set = ft_calloc(ft_arraylen((char**)img_paths) + 1, sizeof(t_img));
	if (!img_set)
		finish_game(mlx);
	mlx->imgs_sets[index] = img_set;
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
	init_img_set(mlx, g_single_img_paths, 0);
	init_img_set(mlx, g_anim_left_paths, 1);
	init_img_set(mlx, g_anim_right_paths, 2);
	init_img_set(mlx, g_anim_up_paths, 3);
	init_img_set(mlx, g_anim_down_paths, 4);
	init_img_set(mlx, g_anim_attack_paths, 5);
	init_img_set(mlx, g_anim_die_paths, 6);
}

void	init_animation(t_animation *animation, int isZombie, t_mlx *mlx)
{
	if (isZombie)
	{
		animation->img_set = mlx->imgs_sets[2];
		//TODO Crear arraylen genérico
		animation->imgs_count = ft_arraylen(animation->img_set);
		//TODO Número aleatorio entre 0 y imgs_count para que los zombies estén desincronizados.
		animation->current_img = 0;
	}
	else
	{
		animation->img_set = mlx->imgs_sets[1];
		animation->imgs_count = ft_arraylen(animation->img_set);
		animation->current_img = 0;
	}
	animation->delay = 0;
	//TODO Resto de fields en caso de haberlos.
}

void	add_entity(int isZombie, size_t x, size_t y, t_mlx *mlx)
{
	t_entity	*entity;
	t_list		*new_node;

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
	init_animation(&(entity->animation), isZombie, mlx);
	entity->x = x;
	entity->y = y;
	entity->dead = 0;
	entity->is_animated = 1;
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
					add_entity(0, x, y, mlx);
				else if (row[x] == 'C')
					add_entity(1, x, y, mlx);
				else if (row[x] == 'E')
					draw_img(mlx->imgs_sets[0][4], x, y, mlx);
			}
		}
	}
}