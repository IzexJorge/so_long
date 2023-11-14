/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 18:19:52 by jescuder          #+#    #+#             */
/*   Updated: 2022/11/03 20:56:45 by jescuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t n)
{
	size_t	i;
	size_t	j;
	size_t	is_correct;

	if (!needle[0])
		return ((char *) haystack);
	i = 0;
	while (i < n && haystack[i])
	{
		j = 0;
		is_correct = 1;
		while (needle[j] && is_correct && i + j < n)
		{
			is_correct = haystack[i + j] == needle[j];
			j++;
		}
		if (is_correct && !needle[j])
			return ((char *) haystack + i);
		i++;
	}
	return (0);
}
