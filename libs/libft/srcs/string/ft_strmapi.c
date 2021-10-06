/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhenry <mhenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 15:48:45 by mhenry            #+#    #+#             */
/*   Updated: 2021/10/06 17:06:57 by mhenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*tab;
	unsigned int	i;

	if (!s)
		return (NULL);
	i = 0;
	tab = malloc(sizeof(char) * (ft_strlen((char *)s) + 1));
	if (!tab)
		return (NULL);
	while (s[i])
	{
		tab[i] = (*f)(i, ((char *)s)[i]);
		i++;
	}
	tab[i] = 0;
	return (tab);
}
