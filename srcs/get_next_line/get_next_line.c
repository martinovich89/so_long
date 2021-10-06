/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhenry <mhenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 02:14:19 by mhenry            #+#    #+#             */
/*   Updated: 2021/04/14 02:14:20 by mhenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

t_element	*ft_getcontent(int fd, t_element **stat)
{
	t_element	*lst;
	t_element	*last_element;

	lst = *stat;
	last_element = lst;
	if (loop(&lst, fd, &last_element))
		return (lst);
	lst = malloc(sizeof(*lst));
	if (!lst)
		return (NULL);
	lst->fd = fd;
	lst->next = NULL;
	lst->data = ft_substr("", 0, 0);
	if (!lst->data)
		return (NULL);
	lst->data = ft_read(lst);
	if (!lst->data)
		return (NULL);
	if (last_element)
		last_element->next = lst;
	else
		*stat = lst;
	return (lst);
}

char	*ft_read(t_element *curr)
{
	char	buf[BUFFER_SIZE + 1];
	char	*tmp;

	curr->ret = read(curr->fd, buf, BUFFER_SIZE);
	while (curr->ret > 0)
	{
		buf[curr->ret] = '\0';
		tmp = curr->data;
		curr->data = ft_strjoin(curr->data, buf);
		if (!curr->data)
			return (NULL);
		free(tmp);
		tmp = NULL;
		if (ft_strchr(buf, '\n'))
			break ;
		curr->ret = read(curr->fd, buf, BUFFER_SIZE);
	}
	if (curr->ret < 0)
		return (NULL);
	return (curr->data);
}

int	ft_cpytoline(t_element *curr, char **line)
{
	char	*tmp;
	size_t	i;
	size_t	j;

	i = 0;
	tmp = curr->data;
	while (curr->data[i] && curr->data[i] != '\n')
		i++;
	*line = ft_substr(curr->data, 0, i);
	if (!*line)
		return (0);
	j = ft_strlen(curr->data);
	curr->data = ft_substr(curr->data, i + 1, j - (i + 1));
	if (!curr->data)
		return (0);
	free(tmp);
	tmp = NULL;
	return (1);
}

int	ft_free_elem(t_element *curr, t_element **stat, int ret)
{
	t_element	*lst;

	lst = *stat;
	if (curr == *stat)
	{
		if ((*stat)->next)
			*stat = (*stat)->next;
		else
			*stat = NULL;
	}
	else
	{
		while (lst)
		{
			if (lst->next == curr)
				lst->next = curr->next;
			lst = lst->next;
		}
	}
	free(curr->data);
	curr->data = NULL;
	free(curr);
	curr = NULL;
	return (ret);
}

int	get_next_line(int fd, char **line)
{
	static t_element	*lst;
	t_element			*curr;

	if (gnl_args_check(lst, line, fd) == -1)
		return (-1);
	curr = ft_getcontent(fd, &lst);
	if (!curr)
		return (-1);
	if (!(ft_strchr(curr->data, '\n')) && curr->ret > 0)
	{
		curr->data = ft_read(curr);
		if (!curr->data)
			return (ft_free_elem(curr, &lst, -1));
	}
	if (!(ft_cpytoline(curr, line)))
		return (ft_free_elem(curr, &lst, -1));
	if (curr->ret > 0)
		return (1);
	else
		return (ft_free_elem(curr, &lst, 0));
}
