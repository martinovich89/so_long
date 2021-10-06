/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhenry <mhenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 13:21:46 by mhenry            #+#    #+#             */
/*   Updated: 2021/10/06 14:27:30 by mhenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_clear_conf(t_env *env)
{
	if (env->conf->map)
		ft_arrdel((void ***)&env->conf->map);
	if (env->conf->file)
		ft_memdel((void **)&env->conf->file);
	if (env->conf)
		ft_memdel((void **)&env->conf);
}

void	ft_clear_tex(t_env *env)
{
	size_t i;

	i = 0;
	while (i < 4)
	{
		if (env->tex[i].img)
		{
			mlx_destroy_image(env->mlx, env->tex[i].img);
			env->tex[i].img = NULL;
		}
		i++;
	}
}

void	ft_clear_env(t_env *env)
{
	if (env)
	{
		if (env->sheet)
			ft_arrdel((void ***)&env->sheet);
		if (env->conf)
			ft_clear_conf(env);
		if (env->tex[0].addr)
			ft_clear_tex(env);
		if (env->mlx && env->end.addr)
			mlx_destroy_image(env->mlx, env->end.img);
		if (env->mlx && env->win && env->img.img)
			mlx_destroy_image(env->mlx, env->img.img);
		if (env->mlx && env->win)
			mlx_destroy_window(env->mlx, env->win);
		if (env->mlx)
		{
			mlx_destroy_display(env->mlx);
			mlx_loop_end(env->mlx);
			free(env->mlx);
		}
		free(env);
	}
}