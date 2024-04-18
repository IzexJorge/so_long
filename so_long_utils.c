/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 21:40:54 by jescuder          #+#    #+#             */
/*   Updated: 2024/04/18 21:42:28 by jescuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	exit(1);
}

int	ft_printf_error(char *error_message)
{
	ft_printf("Error: %s\n", error_message);
	exit(1);
}

size_t	ft_arraylen(char **array)
{
	size_t	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

void	free_array(char **array)
{
	int	i;

	i = -1;
	while (array[++i])
	{
		free(array[i]);
	}
	free(array);
}
