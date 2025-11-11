/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 12:03:25 by brunogue          #+#    #+#             */
/*   Updated: 2025/11/11 17:08:08 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdbool.h>

static bool	verify_type_file(char *av)
{
	char	*cub;
	size_t	len;

	len = ft_strlen(&av[1]);
	cub = ".cub";
	if (len < 4)
		return (false);
	if (ft_strncmp(av, cub, len - 4))
	{
		return (true);
	}
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
