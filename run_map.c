/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 21:43:21 by jescuder          #+#    #+#             */
/*   Updated: 2023/12/15 00:07:51 by jescuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// Sólo imprime los caracteres, para probar.
int	print_map(char **map)
{
	size_t	i;
	char	*row;
	size_t	j;

	i = -1;
	while (map[++i])
	{
		row = map[i];
		j = -1;
		while (row[++j])
			ft_putchar_fd(row[j], 1);
		ft_putchar_fd('\n', 1);
	}
	return (1);
}

int	enough_space(void *mlx, int map_x, int map_y, int tile_s)
{
	int	screen_x;
	int	screen_y;

	(void)mlx;
	screen_x = 1;
	screen_y = 2;
	//mlx_get_screen_size(mlx, &screen_x, &screen_y);
	if ((screen_x > map_x * tile_s) && (screen_y > map_y * tile_s))
		return (1);
	else
		return (0);
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;
	char	*addr;
	int		line_length;
	int		bits_per_pixel;

	addr = img->addr;
	line_length = img->line_length;
	bits_per_pixel = img->bits_per_pixel;
	dst = addr + y * line_length + x * (bits_per_pixel / 8);
	*(unsigned int *)dst = color;
}

void	move_player(int axis, int direction, t_var *var)
{
	(void)axis;
	(void)direction;
	(void)var;
}

int	on_keydown(int keycode, t_var *var)
{
	if (keycode == 2)//Derecha
		move_player(0, 1, var);
	else if (keycode == 0)//Izquierda
		move_player(0, -1, var);
	else if (keycode == 1)//Abajo
		move_player(1, 1, var);
	else if (keycode == 13)//Arriba
		move_player(1, -1, var);
	else if (keycode == 53)
	{
		mlx_destroy_window(var->mlx, var->win);
		exit(0);
	}
	ft_printf("%d", keycode);
	return (0);
}

int	on_destroy()
{
	exit(0);
}

int	run_map(char **map)
{
	t_var	var;

	print_map(map);//Para probar

	var.mlx = mlx_init();
	var.win = mlx_new_window(var.mlx, 1920, 1080, "Hello world!");//No hardcoded
	//var.img.img = mlx_new_image(var.mlx, 1920, 1080);
	//var.img.addr = mlx_get_data_addr(var.img.img, &var.img.bits_per_pixel, &var.img.line_length,
	//							&var.img.endian);
	//my_mlx_pixel_put(&img, 5, 5, 0x0000FF00);
	
	mlx_hook(var.win, 2, 0, on_keydown, &var);
	mlx_hook(var.win, 17, 0, on_destroy, 0);
	mlx_put_image_to_window(var.mlx, var.win, var.img.img, 0, 0);
	mlx_loop(var.mlx);

	return (0);
}

//Matriz de imágenes correspondientes a cada tile.
//Posición actual del personaje
//Posición de la salida.
//Posiciones de los coleccionables no obtenidos.
//Contador de movimientos
//Contador de coleccionables obtenidos.

//Los inputs de movimiento llaman a una función check_path
//que comprueba si se puede mover a esa tile.
//En caso de poderse, check_path llama a otra función move_player
//que mueve el sprite el personaje.
//También modifica la posición del personaje
//y elimina la posición del coleccionable obtenido en su caso.
//También cambia los contadores de movimientos y coleccionables.
//También cierra el juego en caso de llegar a la salida y
//de que tengamos todos los coleccionables.