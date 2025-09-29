/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 20:16:11 by brunogue          #+#    #+#             */
/*   Updated: 2025/05/27 20:17:56 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr(int n)
{
	long	num;
	int		result;

	num = (long)n;
	result = 0;
	if (num < 0)
	{
		result += ft_putchar('-');
		num = -num;
	}
	if (num > 9)
	{
		result += ft_putnbr(num / 10);
	}
	result += ft_putchar((num % 10) + '0');
	return (result);
}
