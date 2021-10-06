/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhenry <mhenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 00:03:13 by mhenry            #+#    #+#             */
/*   Updated: 2021/04/15 00:03:15 by mhenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_ptralloc(void **ptr, size_t size, size_t count)
{
	*ptr = malloc(size * (count + 1));
	if (!*ptr)
		return (1);
	return (0);
}

int	gnl_args_check(t_element *lst, char **line, int fd)
{
	if (fd < 0 || BUFFER_SIZE <= 0 || !line)
	{
		if (lst && lst->data)
		{
			free(lst->data);
			free(lst);
		}
		return (-1);
	}
	return (0);
}

t_element	*loop(t_element **lst, int fd, t_element **last)
{
	while (*lst)
	{
		if ((*lst)->fd == fd)
			return (*lst);
		*last = *lst;
		*lst = (*lst)->next;
	}
	return (NULL);
}
