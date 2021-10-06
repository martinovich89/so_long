/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_skip_space.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhenry <mhenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 13:13:44 by mhenry            #+#    #+#             */
/*   Updated: 2021/10/06 16:53:20 by mhenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_skip_space(const char *s)
{
	int	i;

	i = 0;
	while (s[i] == ' ' || (s[i] > 8 && s[i] < 14))
		i++;
	return (i);
}
