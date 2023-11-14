/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 18:32:55 by jescuder          #+#    #+#             */
/*   Updated: 2022/11/03 19:05:58 by jescuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		len;
	int		start;
	int		end;

	if (!s1 || !set)
		return (0);
	len = ft_strlen(s1);
	start = 0;
	while (start < len && ft_strchr(set, (int) s1[start]))
		start++;
	end = len - 1;
	while (end > start && ft_strchr(set, (int) s1[end]))
		end--;
	return (ft_substr(s1, start, end - start + 1));
}
