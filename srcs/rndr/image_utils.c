/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhenry <mhenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 00:03:02 by mhenry            #+#    #+#             */
/*   Updated: 2021/10/07 00:45:49 by mhenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	next_hero(t_env *env)
{
	if (env->hero_frame < 3)
		env->hero_frame++;
	else
		env->hero_frame = 0;
	if (env->hero_frame == 0)
		env->cur_hero = env->tex + 0;
	if (env->hero_frame == 1)
		env->cur_hero = env->tex + 4;
	if (env->hero_frame == 2)
		env->cur_hero = env->tex + 5;
	if (env->hero_frame == 3)
		env->cur_hero = env->tex + 6;
}

void	next_tex(t_env *env, size_t i, size_t j)
{
	if (env->conf->map[i][j] == 'P')
		env->cur_tex = env->cur_hero;
	else if (env->conf->map[i][j] == 'C')
		env->cur_tex = env->tex + 1;
	else if (env->conf->map[i][j] == '1')
		env->cur_tex = env->tex + 2;
	else if (env->conf->map[i][j] == 'E')
		env->cur_tex = env->tex + 3;
	else if (env->conf->map[i][j] == 'Q')
		env->cur_tex = env->tex + 3;
	else
		env->cur_tex = NULL;
}
