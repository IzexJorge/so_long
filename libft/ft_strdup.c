/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 22:24:14 by jescuder          #+#    #+#             */
/*   Updated: 2022/09/27 18:00:05 by jescuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*p;
	int		len;

	len = ft_strlen(s);
	p = malloc(sizeof(char) * (len + 1));
	if (!p)
		return (0);
	ft_strlcpy(p, s, len + 1);
	return (p);
}
