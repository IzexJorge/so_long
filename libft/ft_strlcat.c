/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 17:12:30 by jescuder          #+#    #+#             */
/*   Updated: 2022/11/03 18:04:36 by jescuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	len;

	if (!size)
		return (ft_strlen(src));
	len = ft_strlen(dest);
	if (size <= len)
		return (ft_strlen(src) + size);
	i = 0;
	while (src[i] && i < size - len - 1)
	{
		dest[i + len] = src[i];
		i++;
	}
	dest[i + len] = 0;
	return (ft_strlen(src) + len);
}
