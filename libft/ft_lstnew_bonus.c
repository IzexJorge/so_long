/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 19:26:27 by jescuder          #+#    #+#             */
/*   Updated: 2022/10/01 20:11:55 by jescuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	list;
	t_list	*p;

	list.content = content;
	list.next = 0;
	p = malloc(sizeof(t_list));
	if (!p)
		return (0);
	*p = list;
	return (p);
}
