
#include "so_long.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*p;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (0);
	p = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!p)
		return (0);
	i = 0;
	while (s1[i])
	{
		p[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		p[i + j] = s2[j];
		j++;
	}
	p[i + j] = 0;
	free(s1);
	return (p);
}

int	ft_perror(void)
{
	perror("Error");
	return (1);
}

int	ft_printf_error(char *error_message)
{
	ft_printf("Error: %s\n", error_message);
	return (1);
}

size_t	ft_arraylen(char **array)
{
	size_t	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}
