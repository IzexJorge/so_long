/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 17:41:46 by jescuder          #+#    #+#             */
/*   Updated: 2022/09/26 17:50:11 by jescuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	char	*s1c;
	char	*s2c;
	size_t	i;

	s1c = (char *) s1;
	s2c = (char *) s2;
	i = 0;
	while (i < n)
	{
		if (s1c[i] != s2c[i])
			return ((unsigned char) s1c[i] - (unsigned char) s2c[i]);
		i++;
	}
	return (0);
}
