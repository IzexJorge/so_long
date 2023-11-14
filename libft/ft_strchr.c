/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 19:53:21 by jescuder          #+#    #+#             */
/*   Updated: 2022/09/25 21:49:09 by jescuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	c1;
	int		i;

	c1 = c;
	i = 0;
	while (s[i])
	{
		if (s[i] == c1)
			return ((char *) s + i);
		i++;
	}
	if (!c1)
		return ((char *) s + i);
	return (0);
}
