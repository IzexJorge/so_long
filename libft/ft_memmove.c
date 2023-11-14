/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 20:18:56 by jescuder          #+#    #+#             */
/*   Updated: 2022/09/25 17:17:10 by jescuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*dst2;
	const unsigned char	*src2;

	if (!dst && !src)
		return (NULL);
	dst2 = (unsigned char *) dst;
	src2 = (unsigned char *) src;
	i = 0;
	if (src > dst)
	{
		while (i < n)
		{
			dst2[i] = src2[i];
			i++;
		}
	}
	else if (src < dst)
	{
		while (n-- > 0)
			dst2[n] = src2[n];
	}
	return (dst);
}
