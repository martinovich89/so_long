/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhenry <mhenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 23:48:34 by martin            #+#    #+#             */
/*   Updated: 2021/10/01 15:17:39 by mhenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_puterr(char *str)
{
	write(2, str, ft_strlen(str));
}

void	ft_error(char *str, t_env *env)
{
	write(2, "Error\n", 6);
	ft_puterr(str);
	ft_clear_env(env);
	exit(1);
}
