/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 18:39:53 by brunogue          #+#    #+#             */
/*   Updated: 2024/11/01 14:42:17 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_digit_count(int n)
{
	int	count;

	count = 0;
	if (n <= 0)
		count = 1;
	while (n != 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	int		length;
	long	num;
	char	*new_str;
	int		is_negative;

	num = n;
	length = get_digit_count(n);
	is_negative = (n < 0);
	new_str = malloc((length + 1) * sizeof(char));
	if (new_str == NULL)
		return (NULL);
	new_str[length] = '\0';
	if (is_negative)
		num = -num;
	while (length > 0)
	{
		new_str[--length] = (num % 10) + '0';
		num = num / 10;
	}
	if (is_negative)
		new_str[0] = '-';
	return (new_str);
}
