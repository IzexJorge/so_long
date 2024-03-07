/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 21:43:21 by jescuder          #+#    #+#             */
/*   Updated: 2024/03/08 00:13:03 by jescuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// Sólo imprime los caracteres, para probar.
int		print_map(char **map)
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

int		enough_space(void *mlx, int map_x, int map_y, int tile_s)
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

//Tal vez haya que destruir las imagenes con destroy_image.
//Añadir argumento para errores. Quizá también otro opcional para mensaje de error custom.
void	finish_game(t_mlx *mlx)
{
	ft_printf("finish game");
	mlx_destroy_window(mlx->mlx, mlx->win);
	free(mlx->mlx);
	free_array(mlx->map);
	(void)mlx;
	exit(0);
}

//Comprobar por qué la ausencia estos free no hacen saltar el sanitizer. Especialmente el de map.
int		on_destroy(t_mlx *mlx)
{
	ft_printf("on_destroy");
	free(mlx->win);
	free(mlx->mlx);
	free_array(mlx->map);
	(void)mlx;
	exit(0);
}

void	kill_zombie(t_mlx *mlx)
{
	(void)mlx;
}

void	move_player(t_mlx *mlx)
{
	(void)mlx;
}

//Comprobar necesidad de throttle
void	check_move_player(size_t x, size_t y, t_mlx *mlx)
{
	size_t next_player_x;
	size_t next_player_y;
	char element;

	//Return si el player se está moviendo.
	next_player_x = mlx->player.x + x;
	next_player_y = mlx->player.y + y;
	element = mlx->map[next_player_x][next_player_x];
	if (element == '1')
		return ;
	else if (element == 'C')
		kill_zombie(mlx);
	else if (element == 'E')//&& no quedan coleccionables
		finish_game(mlx);
	move_player(mlx);
}

int		on_keydown(int keycode, t_mlx *mlx)
{
	if (keycode == 2 || keycode == 124)//Derecha
		check_move_player(1, 0, mlx);
	else if (keycode == 0 || keycode == 123)//Izquierda
		check_move_player(-1, 0, mlx);
	else if (keycode == 1 || keycode == 125)//Abajo
		check_move_player(0, 1, mlx);
	else if (keycode == 13 || keycode == 126)//Arriba
		check_move_player(0, -1, mlx);
	else if (keycode == 53)//Escape
		finish_game(mlx);
	return (0);
}

//Probablemente
void	draw_img(t_img img, size_t x, size_t y, t_mlx *mlx)
{
	mlx_put_image_to_window(mlx->mlx, mlx->win, img.img, x * g_tile_size, y * g_tile_size);
}

//Cada animation podría tener su propia función update.
//Pensar si cada entity tiene una animation(o un array de ellos) como field, o las genero aparte.
int		update_graphics(t_mlx *mlx)
{
	//Para renderizar una animación, incrementar delay_counter y si > delay, draw_img current_img.
	//Se hay movimiento, modificar X o Y con (1 o -1) * g_tile_size / imgs_count.

	//Renderizar cada zombie vivo.
	//NO renderizar cadáveres en función de la posición del jugador debido a los desplazamientos.

	//OPCIÓN 1
	//Usar flag moving_direction en mlx o en Entity. 0 Para parado y 1-4 para direcciones.
	//Si player en movimiento, renderizar cadáveres de zombie en ambas tiles si los hay y
	//luego renderizar al jugador.


	//OPCIÓN 2
	//Cada animación tiene su función.
	//No parece haber motivo para hacer esto.
	

	return (0);
}

int		run_map(char **map)
{
	t_mlx	mlx;

	print_map(map);//Para probar

	mlx.mlx = mlx_init();
	if (!mlx.mlx)
		return (0);
	mlx.win = mlx_new_window(mlx.mlx, 1920, 1080, "Hello world!");//No hardcoded
	if (!mlx.win)
	{
		free(mlx.mlx);
		return (0);
	}
	mlx.map = map;
	mlx.zombies = NULL;
	mlx.move_count = 0;
	init_img_sets(&mlx);
	init_map(&mlx);
	//Tal vez liberar map aquí, ya que no hace falta más. Quizá incluso no tenerlo como field de mlx.

	mlx_hook(mlx.win, 2, 0, on_keydown, &mlx);
	mlx_hook(mlx.win, 17, 0, on_destroy, &mlx);

	mlx_loop_hook(mlx.mlx, update_graphics, &mlx);
	mlx_loop(mlx.mlx);

	return (1);
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