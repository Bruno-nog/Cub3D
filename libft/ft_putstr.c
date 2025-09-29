/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 18:43:26 by brunogue          #+#    #+#             */
/*   Updated: 2025/05/27 20:07:18 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr(char *s)
{
	int	len;

	len = 0;
	if (!s)
		return (len += ft_putstr("(null)"));
	while (s[len] != '\0')
	{
		ft_putchar(s[len]);
		len++;
	}
	return (len);
}
