/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uint_tabdel.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhenry <mhenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 23:39:57 by martin            #+#    #+#             */
/*   Updated: 2021/10/06 17:28:33 by mhenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_uint_tabdel(unsigned int **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
	{
		ft_uint_strdel(tab[i]);
		i++;
	}
	if (tab)
		free(tab);
	tab = NULL;
}
