
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
static const char	*g_single_img[] = {
	"textures/Ground1.xpm",
	"textures/Wall1.xpm",
	"textures/Exit.xpm",
	NULL
};
static const char	*g_anim_move_left[] = {
	"textures/Ground1.xpm",
	"textures/Wall1.xpm",
	"textures/Idle-down.xpm",
	"textures/Zombie-idle-down.xpm",
	"textures/Exit.xpm",
	"textures/Ground1.xpm",
	NULL
};
static const char	*g_anim_move_right[] = {
	"textures/Ground1.xpm",
	"textures/Wall1.xpm",
	"textures/Idle-down.xpm",
	"textures/Zombie-idle-down.xpm",
	"textures/Exit.xpm",
	NULL
};
static const char	*g_anim_move_up[] = {
	"textures/Ground1.xpm",
	"textures/Wall1.xpm",
	"textures/Idle-down.xpm",
	"textures/Zombie-idle-down.xpm",
	"textures/Exit.xpm",
	NULL
};
static const char	*g_anim_move_down[] = {
	"textures/Ground1.xpm",
	"textures/Wall1.xpm",
	"textures/Idle-down.xpm",
	"textures/Zombie-idle-down.xpm",
	"textures/Exit.xpm",
	NULL
};
static const char	*g_anim_idle_down[] = {
	"textures/Idle-down.xpm",
	"textures/Idle-down2.xpm",
	NULL
};
static const char	*g_anim_zombie_idle_down[] = {
	"textures/Zombie-idle-down.xpm",
	"textures/Zombie-idle-down2.xpm",
	NULL
};
static const char	*g_anim_attack[] = {
	"textures/Ground1.xpm",
	"textures/Wall1.xpm",
	"textures/Idle-down.xpm",
	"textures/Zombie-idle-down.xpm",
	"textures/Exit.xpm",
	NULL
};
static const char	*g_anim_death[] = {
	"textures/Zombie-death1.xpm",
	"textures/Zombie-death2.xpm",
	"textures/Zombie-death3.xpm",
	"textures/Zombie-death4.xpm",
	NULL
};

// static const char	*img_paths[] = {
// 	{
// 		"textures/Ground1.xpm",
// 		"textures/Wall1.xpm",
// 		"textures/Idle-down.xpm",
// 		"textures/Zombie-idle-down.xpm",
// 		"textures/Exit.xpm",
// 	},
// 	{
// 		"textures/Ground1.xpm",
// 		"textures/Wall1.xpm",
// 		"textures/Idle-down.xpm",
// 		"textures/Zombie-idle-down.xpm",
// 		"textures/Exit.xpm",
// 	},
// };

// struct MyStruct {
//     int data;
// };

// static const struct MyStruct myArray[] = {{1}, {2}, {3}, {4}, {5}};

int		main(int argc, char *argv[]);
char	*ft_strjoin_free(char *s1, char *s2);
int		ft_perror(void);
int		ft_printf_error(char *error_message);
size_t	ft_arraylen(char **array);
size_t	ft_arraylen2(void *array, size_t element_size);
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
	size_t	current_img;
	//Que cada tipo de animación(movimiento, ataque, muerte) tenga un delay distinto para que las
	// transiciones no se sientan artificiales por estar sincronizadas.
	size_t		delay;
    size_t		delay_counter;
	//Sólo hacen falta coordenadas y función update si Entity no tiene animation.
	//O tal vez sea necesario para que al terminar de atacar el zombie empiece la animación de
	// morirse y cuando acabe ésta el personaje empiece a moverse.
	void	(*update)(t_list **, struct s_animation *);
	size_t	x;
	size_t	y;
}				t_animation;
typedef struct	s_entity
{
	size_t		x;
	size_t		y;
	t_animation	animation;
	//0 - Idle
	//1 - Moving left
	//2 - Moving right
	//3 - Moving up
	//4 - Moving down
	//5 - Attacking
	//6 - Dead
	int			state_value;
}				t_entity;
typedef struct s_mlx
{
	void		*mlx;
	void		*win;
	char		**map;
	t_img		*imgs_sets[9];
	size_t		imgs_sets_sizes[9];
	//t_img		**imgs_sets;
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
void	draw_img_tile(t_img img, size_t x, size_t y, t_mlx *mlx);
int		run_map(char **map);

#endif

//	Incluir en la carpeta del proyecto del so_long las carpetas libft y printf tal cual las entregué.
//	El makefile del so_long llama a los de libft y printf.