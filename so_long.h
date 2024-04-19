/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 22:25:47 by jescuder          #+#    #+#             */
/*   Updated: 2024/04/19 19:40:29 by jescuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include "libft/libft.h"
# include "printf/ft_printf.h"
# include <mlx.h>

static const size_t	g_tile_size = 32;
static const char	*g_single_img[] = {
	"textures/Tile1.xpm",
	"textures/Wall1.xpm",
	"textures/Exit.xpm",
	NULL
};
static const char	*g_anim_walk_left[] = {
	"textures/Walk-left1.xpm",
	"textures/Walk-left2.xpm",
	"textures/Walk-left3.xpm",
	"textures/Walk-left4.xpm",
	NULL
};
static const char	*g_anim_walk_right[] = {
	"textures/Walk-right1.xpm",
	"textures/Walk-right2.xpm",
	"textures/Walk-right3.xpm",
	"textures/Walk-right4.xpm",
	NULL
};
static const char	*g_anim_walk_up[] = {
	"textures/Walk-up1.xpm",
	"textures/Walk-up2.xpm",
	"textures/Walk-up3.xpm",
	"textures/Walk-up4.xpm",
	NULL
};
static const char	*g_anim_walk_down[] = {
	"textures/Walk-down1.xpm",
	"textures/Walk-down2.xpm",
	"textures/Walk-down3.xpm",
	"textures/Walk-down4.xpm",
	NULL
};
static const char	*g_anim_stab_left[] = {
	"textures/Stab-left1.xpm",
	"textures/Stab-left2.xpm",
	"textures/Stab-left3.xpm",
	"textures/Stab-left4.xpm",
	NULL
};
static const char	*g_anim_stab_right[] = {
	"textures/Stab-right1.xpm",
	"textures/Stab-right2.xpm",
	"textures/Stab-right3.xpm",
	"textures/Stab-right4.xpm",
	NULL
};
static const char	*g_anim_stab_up[] = {
	"textures/Stab-up1.xpm",
	"textures/Stab-up2.xpm",
	"textures/Stab-up3.xpm",
	"textures/Stab-up4.xpm",
	NULL
};
static const char	*g_anim_stab_down[] = {
	"textures/Stab-down1.xpm",
	"textures/Stab-down2.xpm",
	"textures/Stab-down3.xpm",
	"textures/Stab-down4.xpm",
	NULL
};
static const char	*g_anim_idle_left[] = {
	"textures/Idle-left1.xpm",
	"textures/Idle-left2.xpm",
	NULL
};
static const char	*g_anim_idle_right[] = {
	"textures/Idle-right1.xpm",
	"textures/Idle-right2.xpm",
	NULL
};
static const char	*g_anim_idle_up[] = {
	"textures/Idle-up1.xpm",
	"textures/Idle-up2.xpm",
	NULL
};
static const char	*g_anim_idle_down[] = {
	"textures/Idle-down1.xpm",
	"textures/Idle-down2.xpm",
	NULL
};
static const char	*g_anim_zombie_idle[] = {
	"textures/Zombie-idle1.xpm",
	"textures/Zombie-idle2.xpm",
	NULL
};
static const char	*g_anim_death[] = {
	"textures/Zombie-death1.xpm",
	"textures/Zombie-death2.xpm",
	"textures/Zombie-death3.xpm",
	"textures/Zombie-death4.xpm",
	NULL
};

typedef struct s_img
{
	void	*img;
	int		width;
	int		height;
}				t_img;

typedef struct s_animation
{
	t_img	*img_set;
	size_t	imgs_count;
	size_t	current_img;
	size_t	delay;
	size_t	delay_counter;
}				t_anim;

typedef struct s_entity
{
	size_t	x;
	size_t	y;
	t_anim	anim;
	int		state_val;
}				t_entity;

typedef struct s_mlx
{
	void		*mlx;
	void		*win;
	char		**map;
	t_img		*imgs_sets[15];
	size_t		imgs_sets_sizes[15];
	t_list		*zombies;
	t_entity	player;
	size_t		walk_count;
	size_t		kills_left;
}				t_mlx;

int			main(int argc, char *argv[]);
char		*ft_strjoin_free(char *s1, char *s2);
int			ft_perror(void);
int			ft_printf_error(char *error_message);
size_t		ft_arraylen(char **array);
void		free_array(char **array);
void		is_map_valid(char **map, char **map_copy);
int			are_chars_valid(char **map, size_t *start_coord);
void		init_img_sets(t_mlx *mlx);
void		init_map(t_mlx *mlx);
void		finish_game(int error, t_mlx *mlx);
void		draw_img(t_img img, float x, float y, t_mlx *mlx);
int			run_map(char **map);
int			update_graphics(t_mlx *mlx);
void		update_iddle(t_entity *entity, t_anim *anim, t_mlx *mlx);
void		update_walk(t_entity *ent, t_anim *anim, int state, t_mlx *mlx);
void		update_attack(t_entity *ent, t_anim *anim, int state, t_mlx *mlx);
void		update_dying(t_entity *entity, t_anim *anim, t_mlx *mlx);
void		draw_img(t_img img, float x, float y, t_mlx *mlx);
void		draw_background(size_t x, size_t y, t_mlx *mlx);
void		draw_walking(t_entity *entity, float x, float y, t_mlx *mlx);
void		walk(t_entity *entity, int x, int y, t_mlx *mlx);
void		attack(t_entity *entity, int x, int y, t_mlx *mlx);
void		stay_idle(t_entity *entity, int x, int y, t_mlx *mlx);
void		die(t_entity *entity, t_mlx *mlx);
t_entity	*get_zombie(size_t x, size_t y, t_mlx *mlx);

#endif
