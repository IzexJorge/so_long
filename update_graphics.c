/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_graphics.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 21:19:43 by jescuder          #+#    #+#             */
/*   Updated: 2024/04/18 23:02:19 by jescuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	update_player(t_entity *player, t_anim *anim, t_mlx *mlx)
{
	int		state_val;

	state_val = player->state_val;
	if (state_val == 0)
		update_iddle(player, anim, mlx);
	else if (state_val >= 1 && state_val <= 4)
		update_walk(player, anim, state_val, mlx);
	else
		update_attack(player, anim, state_val, mlx);
}

void	update_zombie(t_entity *zombie, t_anim *anim, t_mlx *mlx)
{
	int		state_val;

	state_val = zombie->state_val;
	if (state_val == 0)
		update_iddle(zombie, anim, mlx);
	else
		update_dying(zombie, anim, mlx);
}

void	update_entity(t_entity *entity, t_mlx *mlx)
{
	t_anim	*anim;

	if (entity->state_val == 10)
		return ;
	anim = &(entity->anim);
	if (anim->delay_counter >= anim->delay)
	{
		draw_background(entity->x, entity->y, mlx);
		if (entity == &(mlx->player))
			update_player(entity, anim, mlx);
		else
			update_zombie(entity, anim, mlx);
	}
	anim->delay_counter++;
}

int	update_graphics(t_mlx *mlx)
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
