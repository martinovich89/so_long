/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhenry <mhenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 16:11:44 by mhenry            #+#    #+#             */
/*   Updated: 2021/10/06 16:47:38 by mhenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	ft_putnbr_fd(int n, int fd)
{
	long long	ln;

	ln = (long long)n;
	if (ln < 0)
	{
		write(fd, "-", 1);
		ln *= -1;
	}
	if (ln > 9)
		ft_putnbr_fd((ln / 10), fd);
	ft_putchar_fd(ln % 10 + '0', fd);
}
