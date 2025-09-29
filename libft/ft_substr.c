/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 11:59:20 by brunogue          #+#    #+#             */
/*   Updated: 2025/07/04 16:22:55 by pvitor-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub_str;
	size_t	s_len;

	if (s == NULL)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
	{
		sub_str = (char *)malloc(1);
		if (sub_str == NULL)
			return (NULL);
		sub_str[0] = '\0';
		return (sub_str);
	}
	if (len > s_len - start)
		len = s_len - start;
	sub_str = (char *)malloc(len + 1);
	if (sub_str == NULL)
		return (NULL);
	ft_strlcpy(sub_str, s + start, len + 1);
	return (sub_str);
}
*/

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*dest;
	size_t	len_s;
	size_t	index;

	index = 0;
	len_s = ft_strlen(s);
	if (start > len_s)
		return (ft_strdup(""));
	if (len > len_s - start)
		len = len_s - start;
	dest = (char *)malloc(len + 1);
	if (dest == NULL)
		return (NULL);
	while (index < len)
		dest[index++] = s[start++];
	dest[index] = '\0';
	return (dest);
}
