
#include "so_long.h"

void	walk(t_entity *entity, int x, int y, t_mlx *mlx)
{
	size_t		direction_value;
	t_animation	*anim;

	if (x == -1)
		direction_value = 1;
	else if (x == 1)
		direction_value = 2;
	else if (y == -1)
		direction_value = 3;
	else
		direction_value = 4;
	entity->state_value = direction_value;
	anim = &(entity->anim);
	anim->img_set = mlx->imgs_sets[direction_value];
	anim->imgs_count = mlx->imgs_sets_sizes[direction_value];
	anim->current_img = 0;
	anim->delay_counter = 0;
	anim->delay = 2000;
	mlx->walk_count++;
}

void	attack(t_entity *entity, int x, int y, t_mlx *mlx)
{
	size_t		direction_value;
	t_animation	*anim;

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
	anim = &(entity->anim);
	anim->img_set = mlx->imgs_sets[direction_value];
	anim->imgs_count = mlx->imgs_sets_sizes[direction_value];
	anim->current_img = 0;
	anim->delay_counter = 0;
	anim->delay = 2000;
}

void	stay_idle(t_entity *entity, int x, int y, t_mlx *mlx)
{
	int			state_value;
	size_t		index;
	t_animation	*anim;

	entity->x = entity->x + x;
	entity->y = entity->y + y;
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
	anim = &(entity->anim);
	anim->img_set = mlx->imgs_sets[index];
	anim->imgs_count = mlx->imgs_sets_sizes[index];
	anim->current_img = 0;
	anim->delay_counter = 7000;
	anim->delay = 9000;
}

void	die(t_entity *entity, t_mlx *mlx)
{
	t_animation	*anim;

	entity->state_value = 9;
	anim = &(entity->anim);
	anim->img_set = mlx->imgs_sets[14];
	anim->imgs_count = mlx->imgs_sets_sizes[14];
	anim->current_img = 0;
	anim->delay_counter = 0;
	anim->delay = 2000;
}