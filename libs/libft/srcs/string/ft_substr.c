/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhenry <mhenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 14:38:08 by mhenry            #+#    #+#             */
/*   Updated: 2021/10/06 17:20:00 by mhenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*tab;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	tab = malloc(sizeof(char) * (len + 1));
	if (!tab)
		return (NULL);
	while (len-- > 0 && start < ft_strlen(s))
	{
		tab[i] = s[start];
		i++;
		start++;
	}
	tab[i] = 0;
	return (tab);
}
