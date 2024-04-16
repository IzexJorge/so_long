
#include "so_long.h"

void	draw_img(t_img img, float x, float y, t_mlx *mlx)
{
	x = g_tile_size * x;
	y = g_tile_size * y;
	mlx_put_image_to_window(mlx->mlx, mlx->win, img.img, x, y);
}

void	draw_background(size_t x, size_t y, t_mlx *mlx)
{
	t_list		*zombies;
	t_entity	*zombie;

	draw_img(mlx->imgs_sets[0][0], x, y, mlx);
	zombies = mlx->zombies;
	while (zombies)
	{
		zombie = zombies->content;
		if (zombie->x == x && zombie->y == y)
		{
			if (zombie->state_value == 10)
				draw_img(mlx->imgs_sets[14][3], x, y, mlx);
			return ;
		}
		zombies = zombies->next;
	}
}

void	draw_walking(t_entity *entity, float x, float y, t_mlx *mlx)
{
	t_animation	*anim;
	float		tile_perc;

	anim = &(entity->anim);
	tile_perc = ((float)anim->current_img + 1) / anim->imgs_count;
	x = entity->x + x * tile_perc;
	y = entity->y + y * tile_perc;
	draw_img(anim->img_set[anim->current_img], x, y, mlx);
}