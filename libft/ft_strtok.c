/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 20:31:22 by brunogue          #+#    #+#             */
/*   Updated: 2025/02/24 20:47:58 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*find_token_start(char *str, const char *delim)
{
	size_t	i;

	while (*str)
	{
		i = 0;
		while (delim[i])
		{
			if (*str == delim[i])
				break ;
			i++;
		}
		if (delim[i] == '\0')
			return (str);
		str++;
	}
	return (NULL);
}

static char	*find_token_end(char *start, const char *delim)
{
	size_t	i;

	while (*start)
	{
		i = 0;
		while (delim[i])
		{
			if (*start == delim[i])
				return (start);
			i++;
		}
		start++;
	}
	return (start);
}

char	*ft_strtok(char *str, const char *delim)
{
	static char	*static_str;
	char		*start;
	char		*end;

	if (str != NULL)
		static_str = str;
	if (static_str == NULL)
		return (NULL);
	start = find_token_start(static_str, delim);
	if (start == NULL)
		return (NULL);
	end = find_token_end(start, delim);
	if (*end != '\0')
	{
		*end = '\0';
		static_str = end + 1;
	}
	else
		static_str = NULL;
	return (start);
}
