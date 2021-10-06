/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhenry <mhenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 14:18:07 by mhenry            #+#    #+#             */
/*   Updated: 2021/10/06 14:18:12 by mhenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int		set_to_zero(size_t size, void *ptr)
{
	void	**deref;

	deref = (void **)ptr;
	*deref = ft_calloc(1, size);
	if (!(*deref))
		return (1);
	return (0);
}


void	set_player_pos(t_env *env)
{
	size_t i;
	size_t j;

	i = 0;
	while (env->conf->map[i])
	{
		j = 0;
		while (env->conf->map[i][j])
		{
			if (env->conf->map[i][j] == 'P')
			{
				env->hero_pos[0] = j;
				env->hero_pos[1] = i;
			}
			j++;
		}
		i++;
	}
}

void	set_conf(t_env *env)
{
	env->conf->res_h = env->conf->map_h * 50;
	env->conf->res_w = env->conf->map_w * 50;
	set_player_pos(env);
	env->conf->path_he = "textures/Hero1.xpm";
	env->conf->path_ex = "textures/Exit.xpm";
	env->conf->path_wa = "textures/Wall.xpm";
	env->conf->path_it = "textures/Treasure.xpm";
	env->conf->path_end = "textures/End.xpm";
}