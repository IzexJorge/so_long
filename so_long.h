

#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

//Asegurarme de que se puede hacer esto en este proyecto.
#ifndef BUFFER_SIZE
#define BUFFER_SIZE 30
#endif

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft/libft.h"
#include "printf/ft_printf.h"


//Asegurarme de llamar a ft_printf y no a printf. Y de las demás funciones ft.
//Cuidado con las funciones que he cambiado respecto a libft.
//Cuidado con las funciones de libft. Podrían estar mal a pesar de estar corregidas.

int		main(int argc, char *argv[]);
char	*ft_strjoin_free(char *s1, char *s2);
int		ft_perror(void);
int		ft_printf_error(char *error_message);
size_t	ft_arraylen(char **array);
int		is_map_valid(char **map, char **map_copy);
int		are_chars_valid(char **map, size_t *start_coord);
int		draw_map(char **map);

#endif

//Incluir en la carpeta del proyecto del so_long las carpetas libft y printf tal cual las entregué.
//El makefile del so_long llama a los de libft y printf.