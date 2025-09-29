/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 15:55:00 by brunogue          #+#    #+#             */
/*   Updated: 2025/07/20 16:33:19 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_str;
	int		s1_len;
	int		s2_len;
	int		i;
	int		j;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	new_str = (char *)malloc(s1_len + s2_len + 1);
	if (new_str == NULL)
		return (NULL);
	i = -1;
	while (++i < s1_len)
		new_str[i] = s1[i];
	j = -1;
	while (++j < s2_len)
		new_str[i++] = s2[j];
	new_str[i] = '\0';
	return (new_str);
}
