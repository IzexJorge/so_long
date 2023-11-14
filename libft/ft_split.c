/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 22:07:56 by jescuder          #+#    #+#             */
/*   Updated: 2022/11/03 19:19:32 by jescuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_all(char **array, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		free(array[i]);
	}
	free(array);
}

static char	**fill_array(char const *s, char c, char **array, int n)
{
	int		i;
	int		n2;

	i = -1;
	n2 = 0;
	while (s[++i])
	{
		if (s[i] == c)
			n2 = 0;
		else
		{
			n2++;
			if (s[i + 1] == c || s[i + 1] == 0)
			{
				array[n] = ft_substr(s, i - (n2 - 1), n2);
				if (!array[n])
				{
					free_all(array, n);
					return (0);
				}
				n++;
			}
		}
	}
	return (array);
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	int		n;
	int		i;

	if (!s)
		return (0);
	n = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c))
			n++;
		i++;
	}
	array = (char **) malloc(sizeof(char *) * (n + 1));
	if (!array)
		return (0);
	array[n] = 0;
	return (fill_array(s, c, array, 0));
}
