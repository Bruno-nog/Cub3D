/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 19:56:36 by brunogue          #+#    #+#             */
/*   Updated: 2025/05/27 20:16:01 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	playsholder_type(char p, va_list list)
{
	int	size;

	size = 0;
	if (p == '%')
		size += ft_putchar('%');
	if (p == 'c')
		size += ft_putchar(va_arg(list, int));
	if (p == 's')
		size += ft_putstr(va_arg(list, char *));
	if (p == 'p')
		size += ft_pnt(va_arg(list, unsigned long));
	if (p == 'i' || p == 'd')
		size += ft_putnbr(va_arg(list, int));
	if (p == 'u')
		size += ft_put_unsi(va_arg(list, unsigned int));
	if (p == 'x' || p == 'X')
		size += ft_hex(va_arg(list, unsigned int), p);
	return (size);
}

int	ft_printf(const char *format, ...)
{
	va_list	list;
	int		value;
	int		index;

	if (!format)
		return (-1);
	va_start(list, format);
	index = 0;
	value = 0;
	while (format[index])
	{
		if (format[index] == '%')
		{
			value += playsholder_type(format[index + 1], list);
			index += 2;
		}
		else
		{
			value += ft_putchar(format[index]);
			index++;
		}
	}
	va_end(list);
	return (value);
}
