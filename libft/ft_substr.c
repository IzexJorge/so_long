/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 23:06:45 by jescuder          #+#    #+#             */
/*   Updated: 2022/11/03 19:00:24 by jescuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t n)
{
	const char	*str;
	size_t		len;
	char		*p;

	if (!s)
		return (0);
	if (start >= ft_strlen(s))
		start = ft_strlen(s);
	str = s + start;
	len = ft_strlen(str);
	if (n < len)
		len = n;
	p = malloc(sizeof(char) * (len + 1));
	if (!p)
		return (0);
	ft_strlcpy(p, str, len + 1);
	return (p);
}
