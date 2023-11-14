/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 20:18:25 by jescuder          #+#    #+#             */
/*   Updated: 2023/09/24 22:04:47 by jescuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_pointer(size_t num, int char_ascii)
{
	int	n_chars;

	n_chars = 0;
	n_chars += ft_putstr("0x");
	n_chars += ft_putnbr_base(num, 16, char_ascii);
	return (n_chars);
}

int	print_arg(va_list ap, char c)
{
	int		n_chars;

	if (c == 'c')
		n_chars = ft_putchar(va_arg(ap, int));
	else if (c == 's')
		n_chars = ft_putstr(va_arg(ap, char *));
	else if (c == 'p')
		n_chars = print_pointer(va_arg(ap, size_t), 97);
	else if (c == 'd' || c == 'i')
		n_chars = ft_putnbr(va_arg(ap, int));
	else if (c == 'u')
		n_chars = ft_putnbr_base(va_arg(ap, unsigned int), 10, 97);
	else if (c == 'x')
		n_chars = ft_putnbr_base(va_arg(ap, unsigned int), 16, 97);
	else if (c == 'X')
		n_chars = ft_putnbr_base(va_arg(ap, unsigned int), 16, 65);
	else if (c == '%')
		n_chars = ft_putchar(c);
	else
		n_chars = 0;
	return (n_chars);
}

int	ft_printf(char const *format, ...)
{
	va_list	ap;
	int		n_chars;

	va_start(ap, format);
	n_chars = 0;
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			n_chars += print_arg(ap, *format);
		}
		else
			n_chars += ft_putchar(*format);
		format++;
	}
	va_end(ap);
	return (n_chars);
}
