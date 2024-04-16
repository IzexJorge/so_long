
#include "so_long.h"

void	update_iddle(t_entity *entity, t_animation *anim, t_mlx *mlx)
{
	draw_img(anim->img_set[anim->current_img], entity->x, entity->y, mlx);
	anim->current_img = (anim->current_img + 1) % anim->imgs_count;
	anim->delay_counter = 0;
}

void	update_walk(t_entity *entity, t_animation *anim, int state_value, t_mlx *mlx)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
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
	if (anim->current_img == anim->imgs_count - 1)
		stay_idle(entity, x, y, mlx);
	else
	{
		anim->current_img++;
		anim->delay_counter = 0;
	}
}

void	update_attack(t_entity *entity, t_animation *anim, int state_value, t_mlx *mlx)
{
	size_t	x;
	size_t	y;

	draw_img(anim->img_set[anim->current_img], entity->x, entity->y, mlx);
	if (anim->current_img == anim->imgs_count - 1)
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
		die(get_zombie(entity->x + x, entity->y + y, mlx), mlx);
		stay_idle(entity, 0, 0, mlx);
	}
	else
	{
		anim->current_img++;
		anim->delay_counter = 0;
	}
}

void	update_dying(t_entity *entity, t_animation *anim, t_mlx *mlx)
{
	draw_img(anim->img_set[anim->current_img], entity->x, entity->y, mlx);
	if (anim->current_img == anim->imgs_count - 1)
	{
		entity->state_value = 10;
		draw_background(entity->x, entity->y, mlx);
		mlx->kills_left--;
	}
	else
	{
		anim->current_img++;
		anim->delay_counter = 0;
	}
}