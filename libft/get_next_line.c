/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 17:35:48 by brunogue          #+#    #+#             */
/*   Updated: 2025/02/01 13:41:12 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_add_end(t_gnl_list **lst, char *buf)
{
	t_gnl_list	*new_node;
	t_gnl_list	*last_node;

	if (!buf[0])
		return (free(buf));
	new_node = malloc(sizeof(t_gnl_list));
	if (!new_node)
	{
		free(buf);
		return (ft_del(lst));
	}
	last_node = ft_last_node(lst);
	if (!last_node)
		*lst = new_node;
	else
		last_node->next = new_node;
	new_node->content = buf;
	new_node->next = NULL;
}

void	ft_gnlclear(t_gnl_list **lst)
{
	t_gnl_list	*last_node;
	int			i;
	int			k;
	char		*buf;

	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (ft_del(lst));
	last_node = ft_last_node(lst);
	i = 0;
	k = 0;
	while (last_node->content[i] != '\0' && last_node->content[i] != '\n')
		++i;
	while (last_node->content[i] != '\0' && last_node->content[++i])
		buf[k++] = last_node->content[i];
	buf[k] = '\0';
	ft_del(lst);
	ft_add_end(lst, buf);
}

char	*ft_extract_line(t_gnl_list **lst)
{
	t_gnl_list	*temp;
	int			lenght_line;
	char		*line;

	temp = *lst;
	lenght_line = ft_line_size(temp);
	line = (char *)malloc(sizeof(char) * (lenght_line + 1));
	ft_copy_to_line(temp, line);
	line[lenght_line] = '\0';
	return (line);
}

void	ft_gnl_new_node(t_gnl_list **lst, int fd)
{
	int		char_read;
	char	*temp_buf;

	while (!ft_found_newline(*lst))
	{
		temp_buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (temp_buf == NULL)
			return (ft_del(lst));
		char_read = read(fd, temp_buf, BUFFER_SIZE);
		if (char_read == -1)
		{
			free(temp_buf);
			ft_del(lst);
			return ;
		}
		if (char_read == 0)
		{
			free(temp_buf);
			return ;
		}
		temp_buf[char_read] = '\0';
		ft_add_end(lst, temp_buf);
	}
}

char	*get_next_line(int fd)
{
	static t_gnl_list	*lst = NULL;
	char				*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	ft_gnl_new_node(&lst, fd);
	if (lst == NULL)
		return (NULL);
	line = ft_extract_line(&lst);
	if (!line)
	{
		ft_del(&lst);
		return (NULL);
	}
	ft_gnlclear(&lst);
	return (line);
}
