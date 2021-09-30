/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 23:39:37 by martin            #+#    #+#             */
/*   Updated: 2021/09/29 16:24:57 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_tabdel(char ***tab)
{
	int len;
	int i;

	len = ft_tablen(*tab);
	i = 0;
	while (*tab[i])
	{
		ft_strdel(*tab[i]);
		i++;
	}
	if (*tab)
		free(*tab);
	len++;
	*tab = NULL;
}
