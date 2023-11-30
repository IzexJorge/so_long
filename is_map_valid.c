
#include "so_long.h"

size_t	is_rectangle(char **map)
{
	size_t	y;
	size_t	last_col_index;

	last_col_index = ft_strlen(map[0]) - 1;
	y = -1;
	while (map[++y])
		if (last_col_index != ft_strlen(map[y]) - 1)
			return (0);
	ft_printf("It is a rectangle with %d columns.\n", last_col_index + 1);//QUITAR
	return (last_col_index);
}

//Puede que no haga falta si añado un condicional de borde a adyacent_tiles.
int	is_border_valid(char **map, size_t last_col_index)
{
	size_t	last_row_index;
	size_t	y;
	char	*row;
	size_t	x;

	last_row_index = ft_arraylen(map) - 1;
	y = -1;
	while (map[++y])
	{
		row = map[y];
		x = -1;
		if (y == 0 || y == last_row_index)
		{
			while (row[++x])
				if (row[x] != '1')
					return (0);
		}
		else
		{
			while (row[++x])
				if ((x == 0 || x == last_col_index) && row[x] != '1')
					return (0);
		}
	}
	ft_printf("Border is valid.\n");//QUITAR
	return (1);
}

void	adyacent_tiles(char **map, size_t y, size_t x)
{
	char	c;

	c = map[y][x];
	if (c == '1')
		return ;
	map[y][x] = '1';
	if (c == 'E')
		return ;
	adyacent_tiles(map, y + 1, x);
	adyacent_tiles(map, y - 1, x);
	adyacent_tiles(map, y, x + 1);
	adyacent_tiles(map, y, x - 1);
}

int	is_path_valid(char **map_copy, size_t *start_coord)
{
	size_t	y;

	adyacent_tiles(map_copy, start_coord[0], start_coord[1]);
	y = -1;
	while (map_copy[++y])
	{
		if (ft_strchr(map_copy[y], 'E') || ft_strchr(map_copy[y], 'C'))
		{
			free(map_copy);
			return (0);
		}
	}
	free(map_copy);
	ft_printf("Path is valid.\n");//QUITAR
	return (1);
}

int	is_map_valid(char **map, char **map_copy)
{
	int		return_value;
	size_t	start_coord[2];
	size_t	last_col_index;

	return_value = 1;
	if (!are_chars_valid(map, start_coord))
		return_value = 0;
	else
	{
		last_col_index = is_rectangle(map);
		if (!last_col_index)
		{
			ft_printf("It is NOT a rectangle.\n");//QUITAR Y Llaves
			return_value = 0;
		}
		else if (!is_border_valid(map, last_col_index))
			return_value = 0;
		else if (!is_path_valid(map_copy, start_coord))
			return_value = 0;
	}
	if (return_value == 0)
		free(map);
	return (return_value);
}
