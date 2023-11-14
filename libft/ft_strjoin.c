/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 00:33:48 by jescuder          #+#    #+#             */
/*   Updated: 2023/01/12 17:21:57 by jescuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len1;
	size_t	len;
	char	*p;

	if (!s1 || !s2)
		return (0);
	len1 = ft_strlen(s1);
	len = len1 + ft_strlen(s2);
	p = malloc(sizeof(char) * (len + 1));
	if (!p)
		return (0);
	ft_strlcpy(p, s1, len1 + 1);
	ft_strlcat(p, s2, len + 1);
	return (p);
}
