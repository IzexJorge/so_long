/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 19:00:17 by jescuder          #+#    #+#             */
/*   Updated: 2022/09/30 19:50:50 by jescuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*get_str(long numl, int n, int n2, int is_negative)
{
	char	*str;

	str = malloc(sizeof(char) * (n + 1));
	if (!str)
		return (0);
	if (is_negative)
	{
		str[0] = '-';
		n2++;
	}
	str[n] = 0;
	while (--n >= n2)
	{
		str[n] = numl % 10 + '0';
		numl /= 10;
	}
	return (str);
}

char	*ft_itoa(int num)
{
	long	numl;
	int		n;
	int		is_negative;
	int		n2;

	numl = num;
	n = 0;
	is_negative = 0;
	if (numl < 0)
	{
		numl *= -1;
		is_negative = 1;
		n++;
	}
	n2 = numl;
	if (!n2)
		n = 1;
	while (n2)
	{
		n2 /= 10;
		n++;
	}
	return (get_str(numl, n, n2, is_negative));
}
