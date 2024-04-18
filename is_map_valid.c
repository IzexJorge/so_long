/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_map_valid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 21:48:58 by jescuder          #+#    #+#             */
/*   Updated: 2024/04/18 21:49:30 by jescuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static size_t	is_rectangle(char **map)
{
	size_t	y;
	size_t	last_col_index;

	last_col_index = ft_strlen(map[0]) - 1;
	y = -1;
	while (map[++y])
		if (last_col_index != ft_strlen(map[y]) - 1)
			return (0);
	return (last_col_index);
}

static int	is_border_valid(char **map, size_t last_col_index)
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
	return (1);
}

static void	adyacent_tiles(char **map, size_t y, size_t x)
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

static int	is_path_valid(char **map_copy, size_t *start_coord)
{
	size_t	y;

	adyacent_tiles(map_copy, start_coord[0], start_coord[1]);
	y = -1;
	while (map_copy[++y])
	{
		if (ft_strchr(map_copy[y], 'E') || ft_strchr(map_copy[y], 'C'))
			return (0);
	}
	return (1);
}

void	is_map_valid(char **map, char **map_copy)
{
	int		is_valid;
	size_t	start_coord[2];
	size_t	last_col_index;

	is_valid = 1;
	if (!are_chars_valid(map, start_coord))
		is_valid = 0;
	else
	{
		last_col_index = is_rectangle(map);
		if (!last_col_index)
			is_valid = 0;
		else if (!is_border_valid(map, last_col_index))
			is_valid = 0;
		else if (!is_path_valid(map_copy, start_coord))
			is_valid = 0;
	}
	free_array(map_copy);
	if (!is_valid)
	{
		free_array(map);
		ft_printf_error("Invalid map.");
	}
}
