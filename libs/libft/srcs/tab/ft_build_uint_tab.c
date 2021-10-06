/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_build_uint_tab.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhenry <mhenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 23:39:17 by martin            #+#    #+#             */
/*   Updated: 2021/10/06 17:25:14 by mhenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	**ft_build_uint_tab(int w, int h)
{
	unsigned int	**tab;
	int				i;
	size_t			j;

	j = h + 1;
	i = 0;
	tab = ft_calloc(j, sizeof(unsigned int *));
	if (!tab)
		return (NULL);
	while (i < h)
	{
		tab[i] = malloc(sizeof(unsigned int) * w);
		if (!tab[i])
			return (NULL);
		i++;
	}
	return (tab);
}
