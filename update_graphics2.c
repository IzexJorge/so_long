/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_graphics2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 21:17:59 by jescuder          #+#    #+#             */
/*   Updated: 2024/04/18 23:01:21 by jescuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_entity	*get_zombie(size_t x, size_t y, t_mlx *mlx)
{
	t_list		*zombies;
	t_entity	*zombie;

	zombies = mlx->zombies;
	while (zombies)
	{
		zombie = (t_entity *)zombies->content;
		if (zombie->x == x && zombie->y == y)
			return (zombie);
		zombies = zombies->next;
	}
	return (NULL);
}

void	update_iddle(t_entity *entity, t_anim *anim, t_mlx *mlx)
{
	draw_img(anim->img_set[anim->current_img], entity->x, entity->y, mlx);
	anim->current_img = (anim->current_img + 1) % anim->imgs_count;
	anim->delay_counter = 0;
}

void	update_walk(t_entity *entity, t_anim *anim, int state_val, t_mlx *mlx)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	if (state_val == 1)
		x--;
	else if (state_val == 2)
		x++;
	else if (state_val == 3)
		y--;
	else
		y++;
	draw_background(entity->x + x, entity->y + y, mlx);
	draw_walking(entity, x, y, mlx);
	if (anim->current_img == anim->imgs_count - 1)
		stay_idle(entity, x, y, mlx);
	else
	{
		anim->current_img++;
		anim->delay_counter = 0;
	}
}

void	update_attack(t_entity *entity, t_anim *anim, int state_val, t_mlx *mlx)
{
	size_t	x;
	size_t	y;

	draw_img(anim->img_set[anim->current_img], entity->x, entity->y, mlx);
	if (anim->current_img == anim->imgs_count - 1)
	{
		x = 0;
		y = 0;
		if (state_val == 5)
			x--;
		else if (state_val == 6)
			x++;
		else if (state_val == 7)
			y--;
		else
			y++;
		mlx->kills_left--;
		die(get_zombie(entity->x + x, entity->y + y, mlx), mlx);
		stay_idle(entity, 0, 0, mlx);
	}
	else
	{
		anim->current_img++;
		anim->delay_counter = 0;
	}
}

void	update_dying(t_entity *entity, t_anim *anim, t_mlx *mlx)
{
	draw_img(anim->img_set[anim->current_img], entity->x, entity->y, mlx);
	if (anim->current_img == anim->imgs_count - 1)
	{
		entity->state_val = 10;
		draw_background(entity->x, entity->y, mlx);
	}
	else
	{
		anim->current_img++;
		anim->delay_counter = 0;
	}
}
