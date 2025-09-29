/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 17:40:29 by brunogue          #+#    #+#             */
/*   Updated: 2025/02/01 13:35:15 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_gnl_list	*ft_last_node(t_gnl_list **lst)
{
	t_gnl_list	*temp;

	temp = *lst;
	if (temp == NULL)
		return (temp);
	while (temp->next != NULL)
		temp = temp->next;
	return (temp);
}

int	ft_found_newline(t_gnl_list *lst)
{
	int	i;

	if (!lst)
		return (0);
	while (lst)
	{
		i = 0;
		while (lst->content[i] && i < BUFFER_SIZE)
		{
			if (lst->content[i] == '\n' || lst->content[i] == '\0')
				return (1);
			++i;
		}
		lst = lst->next;
	}
	return (0);
}

int	ft_line_size(t_gnl_list *temp)
{
	int	i;
	int	k;

	k = 0;
	i = 0;
	while (temp)
	{
		i = 0;
		while (temp->content[i])
		{
			if (temp->content[i] == '\n')
				return (++k);
			++i;
			++k;
		}
		temp = temp->next;
	}
	return (k);
}

void	ft_copy_to_line(t_gnl_list *lst, char *line)
{
	int	i;
	int	x;

	if (!lst)
		return ;
	x = 0;
	while (lst)
	{
		i = 0;
		while (lst->content[i])
		{
			if (lst->content[i] == '\n')
			{
				line[x++] = '\n';
				line[x] = '\0';
				return ;
			}
			line[x++] = lst->content[i++];
		}
		lst = lst->next;
	}
	line[x] = '\0';
}

void	ft_del(t_gnl_list **lst)
{
	t_gnl_list	*temp;

	if (!lst || BUFFER_SIZE == 0)
	{
		if (!lst)
			*lst = NULL;
		return ;
	}
	while (*lst)
	{
		temp = (*lst)->next;
		free((*lst)->content);
		free(*lst);
		*lst = temp;
	}
	*lst = NULL;
}
