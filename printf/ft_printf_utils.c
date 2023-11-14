/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 20:38:17 by jescuder          #+#    #+#             */
/*   Updated: 2023/09/24 21:56:18 by jescuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putstr(char *s)
{
	int	i;

	if (!s)
	{
		ft_putstr("(null)");
		return (6);
	}
	i = 0;
	while (s[i])
	{
		ft_putchar(*(s + i));
		i++;
	}
	return (i);
}

int	ft_putnbr(int num)
{
	long	numl;
	int		n_chars;

	numl = num;
	n_chars = 0;
	if (numl < 0)
	{
		n_chars += ft_putchar('-');
		numl *= -1;
	}
	if (numl >= 10)
	{
		n_chars += ft_putnbr(numl / 10);
		numl %= 10;
	}
	n_chars += ft_putchar(numl + '0');
	return (n_chars);
}

int	ft_putnbr_base(size_t num, size_t base, int char_ascii)
{
	int	n_chars;

	n_chars = 0;
	if (num >= base)
	{
		n_chars += ft_putnbr_base(num / base, base, char_ascii);
		num %= base;
	}
	if (num >= 10)
		n_chars += ft_putchar(num - 10 + char_ascii);
	else
		n_chars += ft_putchar(num + '0');
	return (n_chars);
}
