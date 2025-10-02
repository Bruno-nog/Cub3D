/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 12:03:25 by brunogue          #+#    #+#             */
/*   Updated: 2025/10/02 14:42:33 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdbool.h>
#include <string.h>

bool	main_parser(char *av)
{
	int		i;
	char	*correct_file;
	size_t	argument_len;

	argument_len = strlen(&av[1]);
	correct_file = ".cub";
	i = 0;
	if (ft_strnstr(&av[1], correct_file, argument_len))
	{
		printf("Its a cub");
		return (true);
	}
	printf("Its not a cub");
	return (false);
}
