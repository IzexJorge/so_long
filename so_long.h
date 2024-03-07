
#ifndef SO_LONG_H
# define SO_LONG_H

//Asegurarme de que se puede hacer esto en este proyecto.
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 30
# endif

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include "libft/libft.h"
# include "printf/ft_printf.h"
# include <mlx.h>

//Asegurarme de llamar a ft_printf y no a printf. Y de las demás funciones ft.
//Cuidado con las funciones que he cambiado respecto a libft.
//Cuidado con las funciones de libft. Podrían estar mal a pesar de estar corregidas.

//Comprobar que puedo y debo usar static const aquí.
//Controlar el caso de que no tenga permisos para acceder a los archivos de imágenes.
static const size_t	g_tile_size = 32;
static const char	*g_single_img_paths[] = {
	"textures/Ground1.xpm",
	"textures/Wall1.xpm",
	"textures/Idle-down.xpm",
	"textures/Zombie-idle-down.xpm",
	"textures/Exit.xpm",
};
static const char	*g_anim_left_paths[] = {
	"textures/Ground1.xpm",
	"textures/Wall1.xpm",
	"textures/Idle-down.xpm",
	"textures/Zombie-idle-down.xpm",
	"textures/Exit.xpm",
};
static const char	*g_anim_right_paths[] = {
	"textures/Ground1.xpm",
	"textures/Wall1.xpm",
	"textures/Idle-down.xpm",
	"textures/Zombie-idle-down.xpm",
	"textures/Exit.xpm",
};
static const char	*g_anim_up_paths[] = {
	"textures/Ground1.xpm",
	"textures/Wall1.xpm",
	"textures/Idle-down.xpm",
	"textures/Zombie-idle-down.xpm",
	"textures/Exit.xpm",
};
static const char	*g_anim_down_paths[] = {
	"textures/Ground1.xpm",
	"textures/Wall1.xpm",
	"textures/Idle-down.xpm",
	"textures/Zombie-idle-down.xpm",
	"textures/Exit.xpm",
};
static const char	*g_anim_attack_paths[] = {
	"textures/Ground1.xpm",
	"textures/Wall1.xpm",
	"textures/Idle-down.xpm",
	"textures/Zombie-idle-down.xpm",
	"textures/Exit.xpm",
};
static const char	*g_anim_die_paths[] = {
	"textures/Ground1.xpm",
	"textures/Wall1.xpm",
	"textures/Idle-down.xpm",
	"textures/Zombie-idle-down.xpm",
	"textures/Exit.xpm",
};

int		main(int argc, char *argv[]);
char	*ft_strjoin_free(char *s1, char *s2);
int		ft_perror(void);
int		ft_printf_error(char *error_message);
size_t	ft_arraylen(char **array);
void	free_array(char **array);
void	is_map_valid(char **map, char **map_copy);
int		are_chars_valid(char **map, size_t *start_coord);
// typedef struct	s_img {
// 	void	*img;
// 	char	*addr;
// 	int		bits_per_pixel;
// 	int		line_length;
// 	int		endian;
// }				t_img;

//	Tal vez sustituir por s_zombie
// typedef struct s_renderable
// {
// 	size_t	x;
// 	size_t	y;
// 	//Tal vez función update
// 	//La de los cuerpos de zombies puede ser simplemente que
// 	//si el jugador está en su casilla se refresque.
// }				t_renderable;
//	Comprobar si hace falta width y height
typedef struct s_img
{
	void	*img;
	int		width;
	int		height;
}				t_img;

// Tal vez sea más eficiente cambiar x e y en lugar de eliminar y crear otra.
// Para ello hay que refrescar la casilla anterior.
// Hay que ver cómo mantener los cuerpos de los zombies vencidos.
// Probablemente sustituir en map el carácter C por otro y checkear map cuando
// el personaje se mueva a una casilla nueva.
typedef struct s_animation
{
	t_img	*img_set;
	size_t	imgs_count;
	int		current_img;
	//Tal vez usar un delay global.
	int		delay;
    int		delay_counter;
	//Sólo hacen falta coordenadas y función update si Entity no tiene animation.
	void	(*update)(t_list **, struct s_animation *);
	size_t	x;
	size_t	y;
}				t_animation;
typedef struct	s_entity
{
	size_t		x;
	size_t		y;
	int			dead;
	t_animation	animation;
	int			is_animated;
}				t_entity;
typedef struct s_mlx
{
	void		*mlx;
	void		*win;
	char		**map;
	t_img		*imgs_sets[7];
	t_list		*zombies;
	t_entity	player;
	size_t		move_count;
}				t_mlx;
// Poner en un .c
// void list_remove(t_list **head, void *content, int (*compare_func)(void *, void *)) {
//     t_list *current = *head;
//     t_list *prev = 0;

//     while (current != 0) {
//         if (compare_func(current->content, content) == 0) {
//             if (prev == 0) {
//                 *head = current->next;
//             } else {
//                 prev->next = current->next;
//             }
//             free(current);
//             return;
//         }
//         prev = current;
//         current = current->next;
//     }
// }
// // Poner en un .c
// int compare_animation(void *anim1, void *anim2) {
//     return ((t_animation *)anim1 == (t_animation *)anim2);
// }
void	init_img_sets(t_mlx *mlx);
void	init_map(t_mlx *mlx);
void	finish_game(t_mlx *mlx);
void	draw_img(t_img img, size_t x, size_t y, t_mlx *mlx);
int		run_map(char **map);

#endif

//	Incluir en la carpeta del proyecto del so_long las carpetas libft y printf tal cual las entregué.
//	El makefile del so_long llama a los de libft y printf.