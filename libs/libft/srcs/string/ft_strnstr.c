/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhenry <mhenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 13:01:11 by mhenry            #+#    #+#             */
/*   Updated: 2021/10/06 17:13:11 by mhenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <string.h>

char	*ft_strnstr(const char *str, const char *tofind, size_t len)
{
	size_t	i;
	size_t	j;

	if (!*tofind)
		return ((char *)str);
	i = 0;
	j = 0;
	while (str[i] && i + j < len)
	{
		while (str[i + j] == tofind[j] && tofind[j] && (i + j) < len)
			j++;
		if (tofind[j] == 0)
			return ((char *)&str[i]);
		j = 0;
		i++;
	}
	return (NULL);
}
