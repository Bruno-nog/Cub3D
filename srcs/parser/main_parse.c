/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 12:03:25 by brunogue          #+#    #+#             */
/*   Updated: 2025/10/17 14:19:53 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdbool.h>

static bool	verify_type_file(char *av)
{
	int		i;
	char	*correct_file;
	size_t	argument_len;

	argument_len = ft_strlen(&av[1]);
	correct_file = ".cub";
	i = 0;
	if (ft_strnstr(&av[1], correct_file, argument_len))
		return (true);
	return (false);
}

bool	main_parser(char *av)
{
	if (!verify_type_file(&av[1]))
	{
		ft_putstr("Error: Invalid file");
		return (false);
	}
	return (true);
}
