/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhenry <mhenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 13:07:56 by mhenry            #+#    #+#             */
/*   Updated: 2021/10/26 15:16:23 by mhenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_textures3(t_env *env)
{
	env->tex[4].img = mlx_xpm_file_to_image(env->mlx, env->conf->path_he2,
			&env->tex[4].w, &env->tex[4].h);
	if (!env->tex[4].img)
		ft_error("failed to allocate tex[4].img\n", env);
	env->tex[4].addr = mlx_get_data_addr(env->tex[4].img, &env->tex[4].bpp,
			&env->tex[4].line_length, &env->tex[4].endian);
	if (!env->tex[4].addr)
		ft_error("failed to allocate tex[4].addr\n", env);
	env->tex[5].img = mlx_xpm_file_to_image(env->mlx, env->conf->path_he3,
			&env->tex[5].w, &env->tex[5].h);
	if (!env->tex[5].img)
		ft_error("failed to allocate tex[5].img\n", env);
	env->tex[5].addr = mlx_get_data_addr(env->tex[5].img, &env->tex[5].bpp,
			&env->tex[5].line_length, &env->tex[5].endian);
	if (!env->tex[5].addr)
		ft_error("failed to allocate tex[5].addr\n", env);
	env->tex[6].img = mlx_xpm_file_to_image(env->mlx, env->conf->path_he4,
			&env->tex[6].w, &env->tex[6].h);
	if (!env->tex[6].img)
		ft_error("failed to allocate tex[6].img\n", env);
	env->tex[6].addr = mlx_get_data_addr(env->tex[6].img, &env->tex[6].bpp,
			&env->tex[6].line_length, &env->tex[6].endian);
	if (!env->tex[6].addr)
		ft_error("failed to allocate tex[6].addr\n", env);
}

void	init_textures2(t_env *env)
{
	env->tex[2].img = mlx_xpm_file_to_image(env->mlx, env->conf->path_wa,
			&env->tex[2].w, &env->tex[2].h);
	if (!env->tex[2].img)
		ft_error("failed to allocate tex[2].img\n", env);
	env->tex[2].addr = mlx_get_data_addr(env->tex[2].img, &env->tex[2].bpp,
			&env->tex[2].line_length, &env->tex[2].endian);
	if (!env->tex[2].addr)
		ft_error("failed to allocate tex[2].addr\n", env);
	env->tex[3].img = mlx_xpm_file_to_image(env->mlx, env->conf->path_ex,
			&env->tex[3].w, &env->tex[3].h);
	if (!env->tex[3].img)
		ft_error("failed to allocate tex[3].img\n", env);
	env->tex[3].addr = mlx_get_data_addr(env->tex[3].img, &env->tex[3].bpp,
			&env->tex[3].line_length, &env->tex[3].endian);
	if (!env->tex[3].addr)
		ft_error("failed to allocate tex[3].addr\n", env);
	env->end.img = mlx_xpm_file_to_image(env->mlx, env->conf->path_end,
			&env->end.w, &env->end.h);
	if (!env->end.img)
		ft_error("failed to allocate end.img\n", env);
	env->end.addr = mlx_get_data_addr(env->end.img, &env->end.bpp,
			&env->end.line_length, &env->end.endian);
	if (!env->end.addr)
		ft_error("failed to allocate end.addr\n", env);
}

void	init_textures1(t_env *env)
{
	env->tex[0].img = mlx_xpm_file_to_image(env->mlx, env->conf->path_he1,
			&env->tex[0].w, &env->tex[0].h);
	if (!env->tex[0].img)
		ft_error("failed to allocate tex[0].img\n", env);
	env->tex[0].addr = mlx_get_data_addr(env->tex[0].img, &env->tex[0].bpp,
			&env->tex[0].line_length, &env->tex[0].endian);
	if (!env->tex[0].addr)
		ft_error("failed to allocate tex[0].addr\n", env);
	env->tex[1].img = mlx_xpm_file_to_image(env->mlx, env->conf->path_it,
			&env->tex[1].w, &env->tex[1].h);
	if (!env->tex[1].img)
		ft_error("failed to allocate tex[1].img\n", env);
	env->tex[1].addr = mlx_get_data_addr(env->tex[1].img, &env->tex[1].bpp,
			&env->tex[1].line_length, &env->tex[1].endian);
	if (!env->tex[1].addr)
		ft_error("failed to allocate tex[1].addr\n", env);
}

void	my_mlx_init(t_env *env)
{
	env->mlx = mlx_init();
	if (!env->mlx)
		ft_error("failed to allocate mlx\n", env);
	env->win = mlx_new_window(env->mlx,
			env->conf->res_w, env->conf->res_h, "so_long");
	if (!env->win)
		ft_error("failed to allocate win\n", env);
	env->img.img = mlx_new_image(
			env->mlx, env->conf->res_w, env->conf->res_h);
	if (!env->img.img)
		ft_error("failed to allocate img.img\n", env);
	env->img.addr = mlx_get_data_addr(env->img.img, &env->img.bpp,
			&env->img.line_length, &env->img.endian);
	if (!env->img.addr)
		ft_error("failed to allocate img.addr\n", env);
	init_textures1(env);
	init_textures2(env);
	init_textures3(env);
	if (ft_build_arr((void ***)&env->sheet, sizeof(unsigned int),
			env->conf->res_w, env->conf->res_h))
		ft_error("failed sheet allocation\n", env);
	if (!env->sheet)
		ft_error("failed to allocate rndr->sheet\n", env);
	env->cur_hero = env->tex + 0;
}
