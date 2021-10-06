/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhenry <mhenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 13:24:39 by mhenry            #+#    #+#             */
/*   Updated: 2021/10/06 13:25:21 by mhenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	display_move_count(t_env *env)
{
	char *str;

	str = ft_itoa(env->move_count);
	if (!str)
		ft_error("failed allocation\n", env);
	write(1, "\r", 1);
	write(1, str, ft_strlen(str));
	free(str);
}