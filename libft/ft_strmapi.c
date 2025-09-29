/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 16:51:41 by brunogue          #+#    #+#             */
/*   Updated: 2024/11/01 14:44:54 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	length;
	unsigned int	i;
	char			*new_str;

	length = 0;
	i = 0;
	if (s == NULL || f == NULL)
		return (NULL);
	while (s[length])
		length++;
	new_str = (char *)malloc(sizeof(char) * (length + 1));
	if (new_str == NULL)
		return (NULL);
	while (i < length)
	{
		new_str[i] = f(i, s[i]);
		i++;
	}
	new_str[length] = '\0';
	return (new_str);
}
