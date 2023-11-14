/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 21:10:20 by jescuder          #+#    #+#             */
/*   Updated: 2022/09/25 21:50:34 by jescuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	c1;
	int		i;
	char	*p;

	p = 0;
	c1 = c;
	i = 0;
	while (s[i])
	{
		if (s[i] == c1)
			p = (char *) s + i;
		i++;
	}
	if (!c1)
		p = (char *) s + i;
	return (p);
}
