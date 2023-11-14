/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 21:34:41 by jescuder          #+#    #+#             */
/*   Updated: 2022/09/30 22:38:56 by jescuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	write_nb(long numl, int fd)
{
	char	c;

	if (numl)
	{
		write_nb(numl / 10, fd);
		c = numl % 10 + '0';
		write(fd, &c, 1);
	}
}

void	ft_putnbr_fd(int num, int fd)
{
	long	numl;

	numl = num;
	if (!numl)
		write(fd, "0", 1);
	else
	{
		if (numl < 0)
		{
			write(fd, "-", 1);
			numl *= -1;
		}
		write_nb(numl, fd);
	}
}
