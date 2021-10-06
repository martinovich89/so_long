/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhenry <mhenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 14:04:28 by mhenry            #+#    #+#             */
/*   Updated: 2021/10/06 14:27:15 by mhenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	move_left(t_env *env, int *left)
{
	env->end_level = (
		env->conf->map[env->hero_pos[1]][env->hero_pos[0] - 1] == 'E');
	if (env->conf->map[env->hero_pos[1]][env->hero_pos[0] - 1] != '1')
	{
		env->conf->map[env->hero_pos[1]][env->hero_pos[0]] = '0';
		env->hero_pos[0]--;
		env->conf->map[env->hero_pos[1]][env->hero_pos[0]] = 'P' + (
			env->conf->map[env->hero_pos[1]][env->hero_pos[0]] == 'E');
		env->move_count++;
		display_move_count(env);
		if (env->conf->map[env->hero_pos[1]][env->hero_pos[0]] == 'C')
		{
			env->conf->map[env->hero_pos[1]][env->hero_pos[0]] = '0';
			env->collectibles++;
		}
	}
	*left = 0;
}

void	move_right(t_env *env, int *right)
{
	env->end_level = (
		env->conf->map[env->hero_pos[1]][env->hero_pos[0] + 1] == 'E');
	if (env->conf->map[env->hero_pos[1]][env->hero_pos[0] + 1] != '1')
	{
		env->conf->map[env->hero_pos[1]][env->hero_pos[0]] = '0';
		env->hero_pos[0]++;
		env->conf->map[env->hero_pos[1]][env->hero_pos[0]] = 'P' + (
			env->conf->map[env->hero_pos[1]][env->hero_pos[0]] == 'E');
		env->move_count++;
		display_move_count(env);
		if (env->conf->map[env->hero_pos[1]][env->hero_pos[0]] == 'C')
		{
			env->conf->map[env->hero_pos[1]][env->hero_pos[0]] = '0';
			env->collectibles++;
		}
	}
	*right = 0;
}

void	move_down(t_env *env, int *down)
{
	env->end_level = (
		env->conf->map[env->hero_pos[1] + 1][env->hero_pos[0]] == 'E');
	if (env->conf->map[env->hero_pos[1] + 1][env->hero_pos[0]] != '1')
	{
		env->conf->map[env->hero_pos[1]][env->hero_pos[0]] = '0';
		env->hero_pos[1]++;
		env->conf->map[env->hero_pos[1]][env->hero_pos[0]] = 'P' + (
			env->conf->map[env->hero_pos[1]][env->hero_pos[0]] == 'E');
		env->move_count++;
		display_move_count(env);
		if (env->conf->map[env->hero_pos[1]][env->hero_pos[0]] == 'C')
		{
			env->conf->map[env->hero_pos[1]][env->hero_pos[0]] = '0';
			env->collectibles++;
		}
	}
	*down = 0;
}

void	move_up(t_env *env, int *up)
{
	env->end_level = (
		env->conf->map[env->hero_pos[1] - 1][env->hero_pos[0]] == 'E');
	if (env->conf->map[env->hero_pos[1] - 1][env->hero_pos[0]] != '1')
	{
		env->conf->map[env->hero_pos[1]][env->hero_pos[0]] = '0';
		env->hero_pos[1]--;
		env->conf->map[env->hero_pos[1]][env->hero_pos[0]] = 'P' + (
			env->conf->map[env->hero_pos[1]][env->hero_pos[0]] == 'E');
		env->move_count++;
		display_move_count(env);
		if (env->conf->map[env->hero_pos[1]][env->hero_pos[0]] == 'C')
		{
			env->conf->map[env->hero_pos[1]][env->hero_pos[0]] = '0';
			env->collectibles++;
		}
	}
	*up = 0;
}

void	update_hero_pos(t_env *env)
{
	if (!env->end_level)
	{
		if (env->left == 1)
			move_left(env, &env->left);
		if (env->right == 1)
			move_right(env, &env->right);
		if (env->down == 1)
			move_down(env, &env->down);
		if (env->up == 1)
			move_up(env, &env->up);
	}
}