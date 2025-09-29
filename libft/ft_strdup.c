/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 18:26:31 by brunogue          #+#    #+#             */
/*   Updated: 2025/07/27 18:38:11 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		i;
	int		c;
	char	*new_str;

	c = 0;
	i = 0;
	while (s[i] != '\0')
	{
		c++;
		i++;
	}
	new_str = (char *)malloc(c + 1);
	if (new_str == NULL)
		return (NULL);
	i = 0;
	while (i < c)
	{
		new_str[i] = s[i];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}
