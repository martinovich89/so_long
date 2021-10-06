/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhenry <mhenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 00:16:45 by martin            #+#    #+#             */
/*   Updated: 2021/10/01 13:21:27 by mhenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int		close_window(t_env *env)
{
	if (env->move_count)
		write(1, "\n", 1);
	ft_clear_env(env);
	exit(0);
}

int		key_press(int keycode, t_env *env)
{
	if (keycode == 113)
		env->left = 1;
	if (keycode == 100)
		env->right = 1;
	if (keycode == 122)
		env->up = 1;
	if (keycode == 115)
		env->down = 1;
	return (0);
}

int		key_release(int keycode, t_env *env)
{
	if (keycode == 65307)
		close_window(env);
	if (keycode == 119)
		env->up = 0;
	if (keycode == 97)
		env->left = 0;
	if (keycode == 100)
		env->right = 0;
	if (keycode == 115)
		env->down = 0;
	return (0);
}
