/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 18:20:21 by jescuder          #+#    #+#             */
/*   Updated: 2022/09/25 16:55:55 by jescuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, size_t n)
{
	size_t			i;
	unsigned char	*str2;
	unsigned char	c2;

	str2 = (unsigned char *) str;
	c2 = (char) c;
	i = 0;
	while (i < n)
	{
		str2[i] = c2;
		i++;
	}
	return (str);
}
