/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhenry <mhenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 14:38:54 by mhenry            #+#    #+#             */
/*   Updated: 2021/10/06 16:46:05 by mhenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

static int	ft_nbrlen(long long n)
{
	int	count;

	count = 1;
	if (n < 0)
	{
		n *= -1;
		count++;
	}
	while (n > 9)
	{
		n /= 10;
		count++;
	}
	return (count);
}

static char	*ft_salloc(long long n, int size)
{
	char	*tab;

	if (n < 0)
	{
		n *= -1;
		tab = malloc(sizeof(char) * (size + 1));
		if (!tab)
			return (NULL);
		tab[0] = '-';
	}
	else if (n == 0)
	{
		tab = malloc(sizeof(char) + 1);
		if (!tab)
			return (NULL);
		tab[0] = '0';
	}
	else
	{
		tab = malloc(sizeof(char) * (size + 1));
		if (!tab)
			return (NULL);
	}
	return (tab);
}

char	*ft_itoa(int n)
{
	int			i;
	char		*s;
	long long	ln;

	ln = (long long)n;
	s = ft_salloc(ln, ft_nbrlen(ln));
	if (!s)
		return (NULL);
	i = ft_nbrlen(ln);
	s[i] = 0;
	i--;
	if (ln < 0)
		ln *= -1;
	while (ln >= 1)
	{
		s[i] = ln % 10 + '0';
		ln /= 10;
		i--;
	}
	return (s);
}
