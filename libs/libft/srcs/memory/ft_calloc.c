/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhenry <mhenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 13:53:14 by mhenry            #+#    #+#             */
/*   Updated: 2021/10/01 15:29:27 by mhenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char		*tab;

	tab = (unsigned char *)malloc(size * count);
	if (!tab)
		return (NULL);
	ft_bzero(tab, count * size);
	return ((void *)tab);
}
