/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 22:03:19 by jescuder          #+#    #+#             */
/*   Updated: 2024/04/18 23:03:50 by jescuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	walk(t_entity *entity, int x, int y, t_mlx *mlx)
{
	size_t	direction_value;
	t_anim	*anim;

	if (x == -1)
		direction_value = 1;
	else if (x == 1)
		direction_value = 2;
	else if (y == -1)
		direction_value = 3;
	else
		direction_value = 4;
	entity->state_val = direction_value;
	anim = &(entity->anim);
	anim->img_set = mlx->imgs_sets[direction_value];
	anim->imgs_count = mlx->imgs_sets_sizes[direction_value];
	anim->current_img = 0;
	anim->delay_counter = 0;
	anim->delay = 2000;
	mlx->walk_count++;
	ft_printf("Movimientos: %i\n", mlx->walk_count);
}

void	attack(t_entity *entity, int x, int y, t_mlx *mlx)
{
	size_t	direction_value;
	t_anim	*anim;

	direction_value = 4;
	if (x == -1)
		direction_value += 1;
	else if (x == 1)
		direction_value += 2;
	else if (y == -1)
		direction_value += 3;
	else
		direction_value += 4;
	entity->state_val = direction_value;
	anim = &(entity->anim);
	anim->img_set = mlx->imgs_sets[direction_value];
	anim->imgs_count = mlx->imgs_sets_sizes[direction_value];
	anim->current_img = 0;
	anim->delay_counter = 0;
	anim->delay = 2000;
}

void	stay_idle(t_entity *entity, int x, int y, t_mlx *mlx)
{
	int		state_val;
	size_t	index;
	t_anim	*anim;

	entity->x = entity->x + x;
	entity->y = entity->y + y;
	state_val = entity->state_val;
	if (state_val == 1 || state_val == 5)
		index = 9;
	else if (state_val == 2 || state_val == 6)
		index = 10;
	else if (state_val == 3 || state_val == 7)
		index = 11;
	else
		index = 12;
	entity->state_val = 0;
	anim = &(entity->anim);
	anim->img_set = mlx->imgs_sets[index];
	anim->imgs_count = mlx->imgs_sets_sizes[index];
	anim->current_img = 0;
	anim->delay_counter = 7000;
	anim->delay = 9000;
}

void	die(t_entity *entity, t_mlx *mlx)
{
	t_anim	*anim;

	entity->state_val = 9;
	anim = &(entity->anim);
	anim->img_set = mlx->imgs_sets[14];
	anim->imgs_count = mlx->imgs_sets_sizes[14];
	anim->current_img = 0;
	anim->delay_counter = 0;
	anim->delay = 2000;
}
