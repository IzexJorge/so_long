
#include "so_long.h"

static int	is_char_valid(char c, size_t *char_count)
{
	char	*valid_chars;
	size_t	z;

	valid_chars = "PEC01";
	z = -1;
	while (++z <= 4)
	{
		if (valid_chars[z] == c)
		{
			if (z <= 2)
				char_count[z]++;
			return (1);
		}
	}
	return (0);
}

static int	is_count_valid(size_t *char_count)
{
	if (!char_count[0] || !char_count[1] || !char_count[2])
		return (0);
	if (char_count[0] > 1 || char_count[1] > 1)
		return (0);
	return (1);
}

int	are_chars_valid(char **map, size_t *start_coord)
{
	size_t	char_count[3];
	size_t	y;
	char	*row;
	size_t	x;

	ft_bzero(char_count, sizeof(char_count));
	y = -1;
	while (map[++y])
	{
		row = map[y];
		x = -1;
		while (row[++x])
		{
			if (row[x] == 'P')
			{
				start_coord[0] = y;
				start_coord[1] = x;
			}
			if (!is_char_valid(row[x], char_count))
				return (0);
		}
	}
	if (!is_count_valid(char_count))
		return (0);
	return (1);
}
