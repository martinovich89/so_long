/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhenry <mhenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 13:10:24 by mhenry            #+#    #+#             */
/*   Updated: 2021/10/06 17:07:39 by mhenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strndup(char const *s1, size_t n)
{
	char	*tab;
	size_t	i;

	i = 0;
	tab = malloc(sizeof(char) * (n + 1));
	if (!tab)
		return (NULL);
	while (i < n && s1[i])
	{
		tab[i] = s1[i];
		i++;
	}
	tab[i] = 0;
	return (tab);
}
