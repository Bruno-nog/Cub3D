/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_unsi.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 20:09:40 by brunogue          #+#    #+#             */
/*   Updated: 2025/05/27 20:09:56 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_put_unsi(unsigned int n)
{
	int	len;

	len = 0;
	if (n > 9)
		len += ft_put_unsi((n / 10));
	len += ft_putchar((n % 10) + '0');
	return (len);
}
