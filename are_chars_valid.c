
int	is_char_valid(char c, int *char_counters)
{
	char	*valid_chars;
	int		is_valid;
	int		z;

	valid_chars = "PEC01";
	z = -1;
	while (++z <= 4)
	{
		if (c == valid_chars[z])
		{
			if (z <= 2)
				char_counters[z]++;
			return (1);
		}
	}
	return (0);
}

int	are_chars_valid(char *container, int *start_coord)
{
	int		char_counters[3];
	int		i;

	ft_bzero(char_counters, sizeof(char_counters));
	i = -1;
	while (container[++i])
	{
		if (container[i] == 'P')
		{
			start_coord[0] == i;
			start_coord[1] == j;
		}
		else if (!is_char_valid(container[i], char_counters))
		{
			free(container);
			return (0);
		}
	}
	free(container);
	if (!char_counters[0] || !char_counters[1] || !char_counters[2])
		return (0);
	if (char_counters[0] > 1 || char_counters[1] > 1)
		return (0);
	return (1);
}
