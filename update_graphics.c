
#include "so_long.h"

void	update_player(t_entity *player, t_animation *anim, t_mlx *mlx)
{
	int		state_value;

	state_value = player->state_value;
	if (state_value == 0)
		update_iddle(player, anim, mlx);
	else if (state_value >= 1 && state_value <= 4)
		update_walk(player, anim, state_value, mlx);
	else
		update_attack(player, anim, state_value, mlx);
}

void	update_zombie(t_entity *zombie, t_animation *anim, t_mlx *mlx)
{
	int		state_value;

	state_value = zombie->state_value;
	if (state_value == 0)
		update_iddle(zombie, anim, mlx);
	else
		update_dying(zombie, anim, mlx);
}

void	update_entity(t_entity *entity, t_mlx *mlx)
{
	t_animation	*anim;

	if (entity->state_value == 10)
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