/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 21:59:59 by jescuder          #+#    #+#             */
/*   Updated: 2023/01/11 22:30:00 by jescuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*p;
	size_t	max_value;

	max_value = (size_t) - 1;
	if (size > 0 && count > max_value / size)
		return (0);
	p = malloc(count * size);
	if (p)
		ft_bzero(p, count * size);
	return (p);
}
